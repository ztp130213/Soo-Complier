#pragma once
#ifndef _SYMBOLTABLE_H
#define _SYMBOLTABLE_H
#include <iostream>
#include <vector>
#include <stack>
#include <map>
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
//结构体数据类型
struct Symbol_Struct
{
	vector<Symbol> Struct_Number;//结构体中的数据成员
};
//函数数据类型
struct Symbol_Function
{
	Data_Type Func_Type;//函数返回类型
	int Func_Address;//函数入口地址
	vector<Symbol_FuncParam> Func_ParamList;//函数的形式参数
};

//标识符节点结构
struct Symbol
{
	string Name;//标识符名字
	TypeCode Type;//标识符种类
	Data_Type DType;//数据类型
	int Address;//符号地址，即在其所处的域的“运行空间”中的位置
	Symbol_Array * Symbol_array;//标识符表示的种类为数组
	Symbol_Function * Symbol_function;//标识符表示的种类为函数
	Symbol_Struct * Symbol_struct;//标识符表示的种类为结构体
	SymbolTable_Node * Link;//相同作用域的标识符
};
//符号表树结构
struct SymbolTable_Node
{
	Symbol SymbolData;//节点数据
	SymbolTable_Node * Root;	//父节点
	SymbolTable_Node * Child;	//子节点
};
//符号表系统类
class Symbol_System
{
public:
	static Symbol_System & Symbol_SystemInstance();	//实例化
	static SymbolTable_Node * SymbolPointer;//进行词法分析时符号表的实时指针
	SymbolTable_Node * SymbolTreeRoot;					//符号表的树结构根节点
	void Symbol_CreateTree();							//构建符号表系统树形结构
	void Symbol_Add(string name, TypeCode type,Data_Type dtype);//将符号加入树形结构符号表系统
	void Symbol_Delete(string symbolname, TypeCode type, Data_Type dtype);//将符号从树形结构符号表系统删除
	Symbol *Symbol_Search(int number);		//标识符查找，并返回查找到的符号节点，如果不存在返回NULL

};
//符号系统的实例化
Symbol_System & Symbol_System::Symbol_SystemInstance()
{
	Symbol_System sybol;
	return sybol;
}

#endif 