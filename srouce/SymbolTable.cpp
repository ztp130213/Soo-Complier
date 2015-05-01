#include "SymbolTable.h"
#include "Error.h"
//栈的初始化
Stack::Stack()
{
	this->Base = new void *;
	if (!this->Base)
	{
		Error error("SymbolTable", "Stack", "Stack base Pointer Memory allocation failure");
		error.ThrowError();
	}
	this->Top = this->Base;
	this->StackSize = 0;
}
//栈的初始化
Stack::Stack(int size)
{
	this->Base = new void *;
	if (!this->Base)
	{
		Error error("SymbolTable", "Stack", "Stack base Pointer Memory allocation failure");
		error.ThrowError();
	}
	this->Top = this->Base;
	this->StackSize = size;
}
//压栈,并返回栈顶元素
void * Stack::Stack_Push(void * value)
{
	if (this->StackSize + 1 <=this->StackSize)
	{

	}
}