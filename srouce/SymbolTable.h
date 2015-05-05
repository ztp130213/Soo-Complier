#pragma once
#ifndef _SYMBOLTABLE_H
#define _SYMBOLTABLE_H
#include <iostream>
#include <vector>
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
	Symbol_Type Type;//符号数据类型
	Symbol * Next;//关联的其它符号
	Symbol * Prev_token;//指向前一定义的同名符号
};

/*
	数据类型结构
*/
struct Symbol_Type
{
	int TypeCode;//数据类型
	struct Symbol * Ref; //引用符号
};

//符号表系统
class Symbol_System
{
public:
	stack<Symbol> Global_Stack;//全局符号栈
	stack<Symbol> Local_Stack;//局部符号栈
	Symbol* Symbol_DirectPush(stack<Symbol> *stack,int number,Symbol_Type  type,int correlation_value);//将符号压入符号栈
	Symbol *Symbol_Push(int number, Symbol_Type  type, int memory_type, int correlation_value);//将符号压入符号栈，动态判断全局或局部
	Symbol *Symbol_FunctionPush(int number, Symbol_Type  type); //将函数符号放入全局符号表中
	Symbol *Symbol_VariablePush(Symbol_Type  type, int memory_type, int number, int address);//把变量放入符号表中
	Symbol *Symbol_Search(int number);		//标识符查找 

};
/*
	单词表系统
*/
#define Maxkey 1024 //哈希表容量

//单词存储结构定义
struct TKWord
{
	int TKCode;//单词编码
	struct TKWord * Next;//指向哈希冲突的同义词
	char *StrTK;//单词字符串
	struct Symbol * symbol_struct;//指向单词所表示的结构定义
	struct Symbol * symbol_ID;//指向单词所表示的标识符
};
TKWord * TK_HasTable[Maxkey]; //单词哈希表
vector<TKWord> TKArrayTable;//单词表
#endif 