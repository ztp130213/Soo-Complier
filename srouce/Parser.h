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
	static Parser & Parser_Instance();	//语法分析实例化
	void Parsering(queue<Token> Queue);	//进行语法分析
	void External_Dec(External state);  //解析外部声明
	bool Type_Sign();					//判断是否为类型符号
	void Declarator();					//声明符
	void Funbody();						//函数体
	void Init();						//初值符
	void Declarator_Postfix();			//声明符号后缀
	void ParameterList();				//参数列表
	void Compound_Statement();          //复合语句
	void Statement();					//语句
	void Statement_If();				//If语句
	void Statement_While();				//While语句
	void Statement_For();				//For语句
	void Statement_Return();			//Return语句
	void Statement_Continue();			//Continue语句
	void Statement_Break();				//Break语句
};
inline Parser & Parser::Parser_Instance()
{
	Parser parser;
	return parser;
}
#endif