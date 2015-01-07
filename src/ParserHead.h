/*
		语法分析
*/
#ifndef PARSERHEAD_H_
#define PARSERHEAD_H_
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
/*
	表达式
*/
//所有的表达式类型的枚举
typedef enum {
	BOOLEAN_EXPRESSION = 1, //bool型常量
	INT_EXPRESSION,   //int型常量
	DOUBLE_EXPRESSION,//double型常量
	STRING_EXPRESSION,//字符串型常量
	IDENTIFIER_EXPRESSION,//变量
	ASSIGN_EXPRESSION,//赋值表达式
	ADD_EXPRESSION,//相加表达式
	SUB_EXPRESSION,//减法表达式
	MUL_EXPRESSION,//乘法表达式
	DIV_EXPRESSION,//除法表达式
	MOD_EXPRESSION,//求余表达式
	EQ_EXPRESSION,//==
	NE_EXPRESSION,//!=
	GT_EXPRESSION,//>
	GE_EXPRESSION,//>=
	LT_EXPRESSION,//<
	LE_EXPRESSION,//<=
	LOGICAL_AND_EXPRESSION,//&&
	LOGICAL_OR_EXPRESSION,//||
	FUNCTION_CALL_EXPRESSION,//函数调用表达式
	MINUS_EXPRESSION,
	NULL_EXPRESSION,
	EXPRESSION_TYPE_COUNT_PLUS_1,
	//BOOLEAN_EXPRESSION	Bool_expression; //bool型常量
	//ADD_EXPRESSION		Add_expreesion; //相加表达式
	//SUB_EXPRESSION	Sub_expreesion;//减法表达式
	//MUL_EXPRESSION	Mul_expreesion;	//乘法表达式
	//DIV_EXPRESSION	Div_expreesion;//除法表达式
	//MOD_EXPRESSION  Mod_expreesion;//求余表达式
	//FUNCTION_CALL_EXPRESSION,//函数调用表达式
} ExpressionType;
//语句表达式树的结点的类型枚举
typedef enum
{
	Variable = 1,//节点是变量
	Number,//节点是数字
	Sign,//节点是符号
}Statementtype;

//算术表达式的树结构
struct Binary_Tree
{
	char data;
	Binary_Tree *left;
	Binary_Tree *right;
};
/*
		判断条件表达式
*/
//判断条件表达式语句结构体
struct Expression_tag {
	ExpressionType type;
	int line_number;
	union {
		bool             boolean_value;
		int                     int_value;
		double                  double_value;
		char                    *string_value;
		//ASSIGN_EXPRESSION      assign_expression;
		/*
		char                    *identifier;
		BinaryExpression        binary_expression;
		Expression              *minus_expression;
		FunctionCallExpression  function_call_expression;
		*/
	} u;
};
//判断表达式的语法分析树的结点类型
typedef enum
{
	charSign = 1,
	judge_Number,
	Bool
}Tree_Judge_Type;
//构建判断表达式的语法分析树
struct Tree_Judge
{
	Tree_Judge_Type type;
	union
	{
		char* sign;		//节点是运算符
		int data;	//节点是数值
		bool bool_output;//左右子树的比较结果
	}u;
	Tree_Judge *left;
	Tree_Judge *right;
};
/*
		语句块Block
*/
//语句块字符流链表
struct Block_Token
{
	Token This;
	Block_Token *next;
};
//语句结构体
struct StatementLink
{
	ExpressionType type;//语句类型
	Block_Token * head;//链表

};
//语句块结构体
struct Block
{
	StatementLink *statementlist;
	StatementLink *next;
};

//赋值表达式的树形结构
struct Assign_Tree
{
	Binary_Tree * right;
	Variable_ left;
};
/*
		关键字
*/
//关键字语句类型
typedef enum
{
	WHILE_STATEMENT
}KeyStatementType;
//while语句的结构
struct WhileStatement
{
	Expression_tag *condition;//条件表达式
	Block* block; //可执行块
};
//关键字语句结构体
struct Statement_tag
{
	KeyStatementType type;
	union
	{
		WhileStatement while_s;
	}u;
};
#endif