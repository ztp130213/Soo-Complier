#pragma once
#ifndef once
#define _ERROR_H
#include <string>
using namespace std;
class Error
{
public:
	Error & Error_Instance();
	string Module;	 //发生错误的模块
	string Function; //发生错误的函数
	string Error_Dec;//错误的描述
	int Line;		 //发生错误的行数
	Error();
	Error(int line,string module, string function, string error_dec);
	string ThrowError();
};
inline Error & Error_Instance()
{
	Error error;
	return error;
}
#endif