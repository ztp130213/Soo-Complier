#pragma once
#ifndef _API_H
#define _API_H
class API
{
public:
	API & Instance();	//API的实例化
	void API_Lexer();	//进行词法分析
	void API_Parser();	//进行语法分析
};
inline API & Instance()
{
	API api;
	return api;
}
#endif