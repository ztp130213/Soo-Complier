#ifndef _EXPRESSION_H_
#define _EXPRESSION_H_
#include "Variable.h"
//赋值表达式的树形结构
struct Assign_Tree
{
	char Sign;
	int left;
	Variable_tag right;
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
#endif