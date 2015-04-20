#pragma once
#ifndef _AST_H
#define _AST_H
#include "Global.h"
#include "Lexer.h"
/*
	抽象语法分析树
*/
class AST
{
public:
	static AST & AST_Instance();
	void AST_Variabledec(Variabledec variable);	//变量声明
	void AST_Variabledef();
	void AST_Assign();							//赋值语句
	void AST_If_Else();							//if_else 类型语句
	void AST_Arithmetic();						//算术运算
	void AST_while();							//while语句
	queue<Tree> ASyntax_Tree;					//抽象语法分析树
};
inline AST & AST::AST_Instance()
{
	AST ast;
	return ast;
}

#endif