#pragma once
#ifndef _PARSER_H
#define _PARSER_H
#include <queue>
#include <string>
#include "Lexer.h"
#include "Global.h"
#include "SymbolTable.h"
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
	bool Type_Sign(Symbol_Type *symboltype);//判断是否为类型符号
	void Declarator();					//声明符
	void Funbody();						//函数体
	bool Is_Keyword(Token token);		//声明符是否为关键字
	bool D_Legal(Token token);			//字符序列是否合法
	bool Declaration_Legal(Token token);//声明符合法判断
	void Init();						//初值符
	void Declarator_Postfix();			//声明符号后缀
	void Struct_Specifier(Symbol_Type *symboltype);//结构体类型解析
	void Struct_DeclarationList();		//结构声明符表
	void Struct_Declaration();			//结构体声明
	Symbol* Struct_Search(Token token);	//结构体定义查找
	void ParameterList();				//形式参数列表
	void ArgumentList();				//实参表达式列表
	void Compound_Statement();          //复合语句
	void Statement();					//语句
	void Statement_If();				//If语句
	void Statement_While();				//While语句
	void Statement_For();				//For语句
	void Statement_Return();			//Return语句
	void Statement_Continue();			//Continue语句
	void Statement_Break();				//Break语句
	void Statement_Expression();		//表达式
	void Token_Judge(string token,string module,string function,string error);		//Token 判断
	void Assign_Expression();			//赋值表达式
	void Equal_Expression();			//相等表达式
	void Relation_Expression();			//关系表达式
	void Add_Expression();				//加减类表达式
	void Multilpi_Expression();			//乘除类表达式
	void Unary_Expression();			//一元运算表达式
	void Postfix_Expression();			//后缀表达式
	void Variable_Expression();			//变量个体
};
inline Parser & Parser::Parser_Instance()
{
	Parser parser;
	return parser;
}
#endif