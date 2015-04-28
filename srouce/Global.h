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
	Statement_Start, //“｛”
	If_Statement,
	While_Statement,
	For_Statement,
	Continue_Statement,
	Break_Statement,
	Return_Statement
};

#endif