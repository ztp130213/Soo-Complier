#pragma once
#ifndef _PARSER_H
#define _PARSER_H
#include <queue>
#include "Lexer.h"
#include "Global.h"
using namespace std;
/*
		语法分析
*/
class Parser
{
public:
	static Parser & Parser_Instance();
	void Parsering(queue<Token> Queue);	//进行语法分析
	void Parser_Dec();					//变量声明
	void Parser_Def();					//变量定义
	void Parser_If();					//if else语句
};
inline Parser & Parser::Parser_Instance()
{
	Parser parser;
	return parser;
}
#endif