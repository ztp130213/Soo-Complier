#include "Error.h"
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