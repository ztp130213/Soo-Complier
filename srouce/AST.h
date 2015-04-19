#pragma once
#ifndef _AST_H
#define _AST_H
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
#endif