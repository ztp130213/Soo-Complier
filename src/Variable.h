/*
		语法分析——变量
*/
#ifndef _VARIABLE_H_
#define _VARIABLE_H_
#include "LexerHead.h"
#include <string>
using namespace std;

/*
		变量
*/
//变量类型
typedef enum
{
	Boolean_value = 1,
	Int_value,
	Double_value,
	String_value,
	NULL_value
}Value_type;
//变量的结构体
struct Variable_
{
	Value_type type; //变量的类型
	union
	{
		bool boolean_value;
		int int_vlaue;
		double double_value;
		string *string_value; //字符串值
	}u;
};
//全局变量链表
struct Variable_tag
{
	string name; //变量的名字
	Variable_ value;//变量的值
	Variable_tag *next;//下一个变量
};
//变量查找，已知存在，查找具体变量
Variable_tag *Search(string text, Variable_tag *First);
//判断是不是变量
bool isVariable(string Text, Variable_tag *First);
//得出当前词法字符流的值,已确定是变量
int Get_Variable_number(Variable_tag *First);
//变量不存在链表中，即添加
void Add_Variable(Variable_tag * &First);
//判断表达中的是变量还是数值并返回
int Judeg_Variable(Variable_tag *First);
//重载函数 Judeg_Variable,传入变量的字符值，寻找变量的值
int Judeg_Variable(Variable_tag *First, string search);
#endif