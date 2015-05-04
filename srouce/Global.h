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
//存储类型
enum Memory_Type
{
	M_Global = 0x00f0,	//包括整型，字符，字符串，全局变量，函数定义
	M_Local=0x00f1,		//栈中变量
	M_LLocal=0x000f2,	//寄存器溢出存放栈
	M_Cmp=0x00f3,		//使用标志寄存器
	M_Valmask=0x00ff,	//存储类型掩码
	M_Lval=0x0100,		//左值
	M_Symbol=0x0200,	//符号
	M_Strut=0x20000000, //结构体符号
	M_Member=0x40000000,//结构成员变量
	M_Params=0x80000000,//函数参数
};
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
	T_Array=0x0010,//数组
};
#endif