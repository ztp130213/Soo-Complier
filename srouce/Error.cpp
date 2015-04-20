#include "Error.h"
#include <string>
#include <strstream>
using namespace std;
Error::Error()
{

}
Error::Error(int line, string module, string function, string error_dec)
{
	Line = line;
	Module = module;
	Function = function;
	Error_Dec = error_dec;
}
string Error::ThrowError()
{
	strstream Streamline;
	string Sline;
	Streamline << Line;
	Streamline >> Sline;
	string OutputError = Sline + Module + Function + Error_Dec;
	return OutputError;
}