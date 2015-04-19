#pragma once
#ifndef _PARSER_H
#define _PARSER_H
#include <queue>
#include "Lexer.h"
using namespace std;
/*
		语法分析
*/
class Parser
{
public:
	static Parser & Instance();
	void Parsering(queue<Token> Queue);	//进行语法分析
	void Parser_Dec();					//变量声明或定义
	void Parser_If();					//if else语句
};
inline Parser & Parser::Instance()
{
	Parser parser;
	return parser;
}
#endif