#include "SymbolTable.h"
#include "Error.h"
using namespace std;
//符号表的树结构根节点
void Symbol_System::Symbol_CreateTree()
{

	this->SymbolTreeRoot->SymbolData.Name = "SymbolSystem_Root";
	this->SymbolTreeRoot->Child = new SymbolTable_Node;
	this->SymbolTreeRoot->Child = NULL;
	this->SymbolTreeRoot->Root = NULL;
	this->SymbolPointer = this->SymbolTreeRoot->Child;
	this->SymbolPointer->Root = this->SymbolTreeRoot;
}
//将符号加入树形结构符号表系统
void Symbol_System::Symbol_Add(Symbol symboldata,External state)
{
	if (state == Global) //全局变量
	{
		if (this->SymbolPointer == this->SymbolTreeRoot->Child) //实时节点是根节点的第一个孩子
		{
			SymbolTable_Node symbolnode;
			symbolnode.SymbolData.Name = symboldata.Name;
			symbolnode.SymbolData.Type = symboldata.Type;
			symbolnode.SymbolData.DType = symboldata.DType;
			symbolnode.Root = this->SymbolPointer->Root;
			symbolnode.Child = NULL;
			this->SymbolPointer = &symbolnode;
		}
		else
		{
			SymbolTable_Node symbolnode;
			symbolnode.SymbolData.Name = symboldata.Name;
			symbolnode.SymbolData.Type = symboldata.Type;
			symbolnode.SymbolData.DType = symboldata.DType;
			symbolnode.Root = this->SymbolPointer->Root;
			symbolnode.Child = NULL;
			this->SymbolPointer->SymbolData.Link = new SymbolTable_Node;
			this->SymbolPointer->SymbolData.Link = &symbolnode;
		}
	}
	else //局部变量,SymbolPointer 符号表实时指针不变
	{
		if (this->SymbolPointer->Child == NULL)
		{
			SymbolTable_Node symbolnode;
			symbolnode.SymbolData.Name = symboldata.Name;
			symbolnode.SymbolData.Type = symboldata.Type;
			symbolnode.SymbolData.DType = symboldata.DType;
			symbolnode.Root = this->SymbolPointer;
			this->SymbolPointer->Child = new SymbolTable_Node;
			this->SymbolPointer->Child = &symbolnode;
		}
		else
		{
			SymbolTable_Node symbolnode;
			symbolnode.SymbolData.Name = symboldata.Name;
			symbolnode.SymbolData.Type = symboldata.Type;
			symbolnode.SymbolData.DType = symboldata.DType;
			symbolnode.Root = this->SymbolPointer;
			this->SymbolPointer->Child->SymbolData.Link = new SymbolTable_Node;
			this->SymbolPointer->Child->SymbolData.Link = &symbolnode;
		}
		
	}
}
//将符号从树形结构符号表系统删除
void Symbol_System::Symbol_Delete(string symbolname, TypeCode type, Data_Type dtype)
{

}