#pragma once 
#ifndef _API_H
#define _API_H
#include "Lexer.h"
class API
{
public:
	static API & Instance();
	void API_Welcome();
	void API_ReadFile();    //从文件中读取程序
	void API_ShellInput();	//控制台输入程序
	void API_Parser();		//语法分析
};
inline API &API::Instance()
{
	API API_Instance;
	return API_Instance;
}
#endif