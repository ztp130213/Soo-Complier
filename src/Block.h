#ifndef _BLOCK_H_
#define _BLOCK_H_
#include "LexerHead.h"
#include "Expression.h"
/*
语句块Block
*/
//词法分析字符流链表
struct Block_Token
{
	Token This;
	Block_Token *next;
};
//语句结构体
struct StatementLink
{
	Block_Token * head;//链表
};
//语句块结构体
struct Block
{
	bool loading;//是否读取
	ExpressionType type;//语句类型
	StatementLink Thestatementlist;//一条语句
	Block *next;//下一条语句
};
//词法分析字符流链表
struct TokenNode
{
	Token This;
	TokenNode *next;
};
#endif