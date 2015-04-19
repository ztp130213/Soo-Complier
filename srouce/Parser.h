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
	void Parsering(queue<Token> Queue);			//进行语法分析
};
inline Parser & Parser::Instance()
{
	Parser parser;
	return parser;
}
#endif