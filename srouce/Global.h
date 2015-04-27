#pragma once
#ifndef _GLOBAL_H
#define _GLOBAL_H
using namespace std;
//支持的数据类型
enum Data_Type
{
	Int,
	Char,
	Float,
	String,
	Void
};
//函数解析状态
enum External
{
	Global,		//表示函数外部解析状态
	Local,		//表示函数内部解析状态
};

/*
*/
//语句类型
enum Ex_Statement
{

};
//变量结构体
typedef struct Variable
{
	Variable_Type variable_type;//变量类型
	string variable_name;		//变量名字
	union 
	{
		int Intvalue;
		char Charvalue;
		float Floatvalue;
		char * Strvalue;
	}Values;
};
//树节点
struct Tree_Node
{
	string token;//结点的值
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