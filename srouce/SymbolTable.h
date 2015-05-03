#pragma once
#ifndef _SYMBOLTABLE_H
#define _SYMBOLTABLE_H
#include <iostream>
#include <stack>
#include "Lexer.h"
#include "Global.h"
using namespace std;
/*
	符号表系统
	在编译程序中符号表用来存放程序中出现的有关标识符的属性信息
*/

/*
	符号存储结构
*/
struct Symbol
{
	int Number;//符号的单词编码
	int Register;//符号关联的寄存器
	int Correlation_value;//符号关联值
	Data_Type Type;//符号数据类型
	Symbol * Next;//关联的其它符号
	Symbol * Prev_token;//指向前一定义的同名符号
};
//符号表系统
class Symbol_System
{
public:
	stack<Token> Global_Stack;//全局符号栈
	stack<Token> Local_Stack;//局部符号栈
	Symbol *Symbol_DirectPush(stack< Token> * stack,int number,Data_Type * type,int correlation_value);//将符号压入符号栈
	Symbol *Symbol_Push(int number, Data_Type* type, int memory_type, int correlation_value);//将符号压入符号栈，动态判断全局或局部
	Symbol *Symbol_FunctionPush(int number, Data_Type * type); //将函数符号放入全局符号表中
	Symbol *Symbol_VariablePush(Data_Type * type, int Register, int number, int address);//把变量放入符号表中

};
#endif 