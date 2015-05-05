#pragma once 
#ifndef _API_H
#define _API_H
#include "Lexer.h"
#include "Global.h"
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
	float String2Float(string str);
	char * String2CharPlus(string str);
	Data_Type Token2Type(Token token);  //token 转 数据类型
	Ex_Statement Token2Statement(Token token);//token 转 语句类型
	Operator Token2Operator(Token token); //token 转 运算符
	int Elf_Hash(char * key);			//哈希函数，计算哈希地址
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
