#pragma once
#ifndef _LEXER_H
#define _LEXER_H
#include <iostream>
#include <string>
#include <queue>
#include <boost/regex.hpp>
boost::smatch what;
boost::cmatch mat;
boost::regex expression("\\s*((//.*)|([0-9]+)|(\"(\\\\\"|\\\\\\\\|\\\\n|[^\"])*\")|[A-Z_a-z][A-Z_a-z0-9]*|==|!=|<=|>=|&&|\\|\\||\\p{Punct})?");
using namespace std;

//字符流单元类
class Token
{
public:
	bool Id;		//标识符
	bool Number;	//数字
	int LineNumber;	//Token 所处的行数
	string Text;	//文本
	Token();
	Token(int line);
	Token(int line, string &text, string Id_or_Number);
	int Token_GetLinenumber();
	bool Token_IsNumber();
	bool Token_IsId();
	string Token_GetText();
	int Token_GetNumber();
	bool operator!=(Token & example)
	{
		if (LineNumber != example.LineNumber)
			return false;
		else
			return true;
	}
};
Token StopEOF(-1);

//进行词法分析
class Lexer
{
public:
	static Lexer & Instance(); //实例化词法分析
	queue<Token> Queue; //词法分析的结果
	bool HasMore;
	Lexer();
	Token Lexer_Read();//读取一个字符
	Token Lexer_Peek(int n);//预读下一个字符
	void Lexer_Readline(string &line, int linenumber);//读取一行，进行解析
	queue<Token> Lexer_ReturnQueue();//返回词法分析的结果
};
inline Lexer & Instance()
{
	Lexer Lexer_out;
	return Lexer_out;
}
#endif