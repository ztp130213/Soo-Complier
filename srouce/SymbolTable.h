#pragma once
#ifndef _SYMBOLTABLE_H
#define _SYMBOLTABLE_H
#include <iostream>
using namespace std;
/*
	实现一个动态栈
*/
class Stack
{
public:
	Stack(); //栈的初始化
	Stack(int size);//栈的初始化
	~Stack();//栈的销毁
	void * Base; //栈底指针
	void * Top;  //栈顶指针
	int StackSize;//栈的大小
	void * Stack_Push( void * value);//压栈，并返回栈顶元素
	void * Stack_Pop(); //弹出栈顶元素
	void * Stack_Top();//返回栈顶元素
	bool * Stack_Empty();//栈是否为空
};
#endif 