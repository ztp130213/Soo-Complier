#pragma once
#ifndef _GLOBAL_H
#define _GLOBAL_H
using namespace std;
//变量支持的类型
enum Variable_Type
{
	Int,
	Char,
	Float,
	String
};
//语句类型
enum Ex_Statement
{

};
//变量结构体
typedef struct Variabledec
{
	Variable_Type variable_type;//变量类型
	string variable_name;		//变量名字
	union 
	{
		int Intvalue;
		char Charvalue;
		float Floatvalues;
		char * Strvalues;
	}Values;
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