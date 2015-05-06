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
	Void,
	Struct,
};
//函数解析状态
enum External
{
	Global,		//表示函数外部解析状态
	Local,		//表示函数内部解析状态
};

//语句类型
enum Ex_Statement
{
	Statement_Start, //“｛”
	If_Statement,
	While_Statement,
	For_Statement,
	Continue_Statement,
	Break_Statement,
	Return_Statement
};
//运算符号
enum Operator
{
	Plus,//+
	Minus,//-
};
//标志符号种类
enum TypeCode
{
	T_Int=0, //整型
	T_Char=1,//字符型
	T_Float=2,//浮点型
	T_Void=3,//空类型
	T_Ptr=4,//指针
	T_Func=5,//函数
	T_Struct=6,//结构体
	T_String=7,//字符串
	T_Array=8,//数组
};
#endif