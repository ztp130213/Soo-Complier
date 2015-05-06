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
//数组数据类型
struct Symbol_Array
{
	int Length;//数组维度
};
//函数形式参数
struct Symbol_FuncParam
{
	Data_Type type;//参数类型
	string name; //参数名字
};
//函数数据类型
struct Symbol_Function
{
	Data_Type Func_Type;//函数返回类型
	int Func_Address;//函数入口地址
	vector<Symbol_FuncParam> Func_ParamList;//函数的形式参数
};
//标识符结构
struct Symbol
{
	string Name;//标识符名字
	TypeCode Type;//标识符种类
	Data_Type DType;//数据类型
	int Address;//符号地址，即在其所处的域的“运行空间”中的位置
	Symbol_Array * Symbol_array;//标识符表示的种类为数组
	Symbol_Function * Symbol_function;//标识符表示的种类为函数

	Symbol * Next_token;//指向下一定义的同名符号
};
//符号表系统
class Symbol_System
{
public:
	static Symbol_System & Symbol_SystemInstance();//实例化
	stack<Symbol> Symbol_Stack;	//全局符号栈
	stack<int> Index_Stack;		//索引符号栈
	void Symbol_Push(char *name, TypeCode type,Data_Type dtype,int level);//将符号压入符号栈
	Symbol *Symbol_FunctionPush(int number, Symbol_Type  type); //将函数符号放入全局符号表中
	Symbol *Symbol_VariablePush(Symbol_Type  type, int memory_type, int number, int address);//把变量放入符号表中
	Symbol *Symbol_Search(int number);		//标识符查找 

};
//符号系统的实例化
Symbol_System & Symbol_System::Symbol_SystemInstance()
{
	Symbol_System sybol;
	return sybol;
}
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