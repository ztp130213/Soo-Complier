#include "SymbolTable.h"
#include "Error.h"
using namespace std;
//符号表的树结构根节点
void Symbol_System::Symbol_CreateTree()
{

	this->SymbolTreeRoot->SymbolData.Name = "SymbolSystem_Root";
	this->SymbolTreeRoot->Child = NULL;
	this->SymbolTreeRoot->Root = NULL;
}
//将符号加入树形结构符号表系统
void Symbol_System::Symbol_Add(string symbolname, TypeCode type, Data_Type dtype)
{
	SymbolTable_Node *symbolnode;
	symbolnode->SymbolData.Name = symbolname;
	symbolnode->SymbolData.Type = type;
	symbolnode->SymbolData.DType = dtype;
	if (this->SymbolPointer->Child == NULL)
	{
		this->SymbolPointer->Child = symbolnode;
		symbolnode->Root = this->SymbolPointer;
	}
	else
	{
		SymbolTable_Node Pointer = *this->SymbolPointer;
		while (this->SymbolPointer->Child->SymbolData.Link != NULL)
		{
			this->SymbolPointer = this->SymbolPointer->Child->SymbolData.Link;
		}
		symbolnode->Root = &Pointer;
		this->SymbolPointer->SymbolData.Link = symbolnode;
		this->SymbolPointer = &Pointer; //还原实时指针
	}
}
//将符号从树形结构符号表系统删除
void Symbol_System::Symbol_Delete(string symbolname, TypeCode type, Data_Type dtype)
{

}