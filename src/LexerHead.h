#ifndef _LEXERHEAD_H_
#define _LEXERHEAD_H_
#include <iostream>
#include <string>
#include <queue>
#include <fstream>
#include <stack>
#include <boost/regex.hpp>
using namespace std;
boost::smatch what;
boost::cmatch mat;
boost::regex expression("\\s*((//.*)|([0-9]+)|(\"(\\\\\"|\\\\\\\\|\\\\n|[^\"])*\")|[A-Z_a-z][A-Z_a-z0-9]*|==|!=|<=|>=|&&|\\|\\||\\p{Punct})?");
//Token类
class Token
{
public:
	bool ID;
	bool NUM;
	int linenumber;
	string text;
	Token()//无参构造函数
	{
		linenumber = 0;
	}
	Token(int line)
	{
		linenumber = line;
	}
	Token(int line, string id, string ID_or_NUM)//使用的构造函数
	{
		linenumber = line;
		text = id;
		if (ID_or_NUM == "ID")
		{
			ID = true;
			NUM = false;
		}
		else
		{
			NUM = true;
			ID = false;
		}
	}
	int getlinenumber(){ return linenumber; }//获得代码所在的行数
	// bool isIdenfifier(){ return false; }
	bool isnumber(){ return NUM; }
	bool isstring(){ return ID; }
	string gettext(){ return text; }
	int getnumber()//如果Token为数字，获得其数值
	{
		int n = atoi(text.c_str());
		return n;
	}
};
Token StopEOF(-1);

queue<Token> Queue;
//词法分析
class Lexer
{
public:
	bool hasmore;
	Lexer() //构造函数
	{
		hasmore = true;
	}
	Token  read() //读取队列第一个
	{
		if (!Queue.empty())
		{
			Token front;
			front = Queue.front();
			Queue.pop();
			return front;
		}
		else
			return StopEOF;
	}
	Token peek(int n) //预读
	{
		queue<Token > Queue_peek;
		for (int i = 0; i < n; i++)
		{
			Queue_peek.push(Queue.front());
			Queue.pop();
		}
		Token peek_token = Queue.front();
		int size = Queue.size();
		for (int i = 0; i <size; i++)
		{
			Queue_peek.push(Queue.front());
			Queue.pop();
		}
		size = Queue_peek.size();
		for (int i = 0; i <size; i++)
		{
			Queue.push(Queue_peek.front());
			Queue_peek.pop();
		}
		return peek_token;
	}
	void readline(string line, int linenumber)
	{
		int pos = 0;
		int endpos = line.length();
		string::const_iterator start = line.begin();
		string::const_iterator end = line.end();
		while (regex_search(start, end, what, expression) && pos < endpos)
		{
			string m = what[0];
			if (m.length() != 0)  //不是空格
			{
				if (what[2].matched == false) //不是注释
				{
					if (what[3].matched != false) //数字
					{
						string msg(what[3].first, what[3].second);
						start = what[3].second;
						pos = pos + msg.length();
						Token num(linenumber, msg, "NUM");
						Queue.push(num);

					}
					else if (what[4].matched != false) //str Token 符号 但是识别不了
					{
						string msg(what[4].first, what[4].second);
						cout << msg.c_str() << endl;
						start = what[4].second;
						pos = pos + msg.length();
					}
					else //ID Token
					{
						string msg(what[0].first, what[0].second);
						start = what[0].second;
						pos = pos + msg.length();
						start = what[0].second;
						Token id(linenumber, msg, "ID");
						Queue.push(id);
					}
				}
			}
		}
		Token newline(linenumber, "\\n", "ID");
		Queue.push(newline);
	}
};
Lexer Lexer_out;//词法分析的结果
#endif