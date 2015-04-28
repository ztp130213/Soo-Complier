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

	//
	bool Is_Keyword(Token token);		//是否为关键字
	void Parser_Var();					//变量声明或定义区段
	void Parser_Pra();					//程序区段
	void Parser_Math();					//数学运算式
	void Parser_Keyword();				//关键字解析
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