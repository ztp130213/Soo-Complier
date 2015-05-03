#include "SymbolTable.h"
#include "Error.h"
using namespace std;
//将符号压入符号栈
Symbol * Symbol_DirectPush(stack< Token> * stack, int number, Data_Type * type, int correlation_value)
{

}
//将符号压入符号栈，动态判断全局或局部
Symbol *Symbol_Push(int number, Data_Type* type, int memory_type, int correlation_value)
{

}
//将函数符号放入全局符号表中
Symbol * Symbol_System::Symbol_FunctionPush(int number, Data_Type * type)
{

}
//把变量放入符号表中
Symbol *Symbol_VariablePush(Data_Type * type, int Register, int number, int address)
{

}