#include "Lexer.h"
using namespace std;
/*
字符流单元类成员函数
*/
Token::Token()
{
	LineNumber = -1;
}
Token::Token(int line)
{
	LineNumber = line;
}
Token::Token(int line, string &text, string Id_or_Num)
{
	LineNumber = line;
	Text = text;
	if (Id_or_Num == "Id")
	{
		Id = true;
		Number = false;
	}
	else
	{
		Number = true;
		Id = true;
	}
}
int Token::Token_GetLinenumber()
{
	return LineNumber;
}
bool Token::Token_IsNumber()
{
	return Number;
}
bool Token::Token_IsId()
{
	return Id;
}
string Token::Token_GetText()
{
	return Text;
}
int Token::Token_GetNumber()
{
	int number = atoi(Text.c_str());
	return number;
}
/*
语法分析类成员函数
*/
Lexer::Lexer()
{
	HasMore = true;
}
Token Lexer::Lexer_Read()
{
	if (!Queue.empty())
	{
		Token read = Queue.front();
		Queue.pop();
		return read;
	}
	else
		return StopEOF;
}
Token Lexer::Lexer_Peek(int n)
{
	queue<Token > Queue_peek;
	for (int i = 0; i < n; i++)
	{
		Queue_peek.push(Queue.front());
		Queue.pop();
	}
	Token Peek_token = Queue.front();
	int Size = Queue.size();
	for (int i = 0; i <Size; i++)
	{
		Queue_peek.push(Queue.front());
		Queue.pop();
	}
	Size = Queue_peek.size();
	for (int i = 0; i <Size; i++)
	{
		Queue.push(Queue_peek.front());
		Queue_peek.pop();
	}
	return Peek_token;
}
void Lexer::Lexer_Readline(string &line, int linenumber)
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
		//解析一句之后加上 \n 符号
		string newline = "\\n";
		Token Newline(linenumber, newline, "ID");
		Queue.push(Newline);
	}
}