#ifndef _KEYWORD_H_
#define _KEYWORD_H_
#include "Expression.h"
#include "Block.h"
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