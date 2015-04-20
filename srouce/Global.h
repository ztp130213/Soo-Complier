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

#endif