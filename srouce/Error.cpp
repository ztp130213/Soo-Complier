#include "Error.h"
#include <string>
#include <strstream>
using namespace std;
Error::Error()
{

}
//一般为语法分析时分析的错误
Error::Error(int line, string module, string function, string error_dec)
{
	Line = line;
	Module = module;
	Function = function;
	Error_Dec = error_dec;
}
//常规错误
Error::Error(string module, string function, string error_dec)
{
	Line = -1;
	Module = module;
	Function = function;
	Error_Dec = error_dec;
}
//错误输出
string Error::ThrowError()
{
	strstream Streamline;
	string Sline;
	Streamline << Line;
	Streamline >> Sline;
	string OutputError = Sline + Module + Function + Error_Dec;
	return OutputError;
}