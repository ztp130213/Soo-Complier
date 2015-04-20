#pragma once 
#ifndef _API_H
#define _API_H
#include "Lexer.h"
#include <string>
using namespace std;
class API
{
public:
	/*
		工具方法
	*/
	int String2Int(string str);
	string Int2String(int number);
	/*
		主程类
	*/
	static API & Instance();
	queue<Token> Queue;							//词法分析的结果
	void API_Welcome();							//欢迎程序
	void API_ReadFile();						//从文件中读取程序
	void API_ShellInput();						//控制台输入程序
	void API_Parser(queue<Token> Queue);		//语法分析
};
inline API &API::Instance()
{
	API API_Instance;
	return API_Instance;
}
#endif
