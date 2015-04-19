#pragma once
#ifndef _AST_H
#define _AST_H
#include "Lexer.h"
/*
	抽象语法分析树
*/
class AST
{
public:
	void AST_Variabledec();//变量声明或定义
	void AST_Assign(); //赋值语句
	void AST_If_Else();//if_else 类型语句
	void AST_Arithmetic();//算术运算
	void AST_while();	//while语句
};
//树节点
struct Tree_Node
{
	Token token;//结点的值
	string Sign;//结点的标志
	Tree_Node * Left;
	Tree_Node * Right;

};
//语法树
struct Tree
{
	Tree_Node Root;
	Tree_Node * Left;
	Tree_Node * Right;
};
#endif