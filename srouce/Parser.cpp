#include "Parser.h"

#include "Error.h"
#include "Global.h"
#include "API.h"
using namespace std;
//语法分析
void Parser::Parsering(queue<Token> Queue)
{
	Token token;
	while (Lexer::Lexer_Instance().Lexer_Read() != StopEOF)
	{
		External_Dec(Global);
	}
}
//解析 声明
void Parser::External_Dec(External state)
{
	if (!Type_Sign()) //类型判断
	{
		Error error(Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetLinenumber, "Type", "declaration", "no such type");
		error.ThrowError();
	}
	if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == ";")
	{
		Lexer::Lexer_Instance().Lexer_Read();
		return;
	}
	while (1) //逐个分析声明或函数定义
	{
		Declarator();
		if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == "{") // 函数定义
		{
			if (state == Local)
			{
				Error error(Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetLinenumber, "Dec", "declaration", "not support function nest");
				error.ThrowError();
			}
			Funbody();//函数体
			break;
		}
		else
		{
			if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == "=")
			{
				Lexer::Lexer_Instance().Lexer_Read();//读取“=”
				Init();
			}
		}
	}
}
//声明 标识符
void Parser::Declarator()
{
	if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_IsId)
	{
		Lexer::Lexer_Instance().Lexer_Read(); //读取这个标识符
	}
	else
	{
		Error error(Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetLinenumber, "IDENT", "declaration", "need input a ID");
		error.ThrowError();
	}
	Declarator_Postfix(); //声明符后缀
}
//声明符后缀
void Parser::Declarator_Postfix()
{
	if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == "(")	//函数
	{
		Lexer::Lexer_Instance().Lexer_Read(); //读取”（“
		ParameterList(); //参数列表解析
	}
	else if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == "[") //数组
	{
		Lexer::Lexer_Instance().Lexer_Read(); //读取"["
		if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_IsNumber())
		{
			Lexer::Lexer_Instance().Lexer_Read(); //读取 数组大小
		}
		if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == "]")
			Lexer::Lexer_Instance().Lexer_Read(); //读取"]"
		else
		{
			Error error(Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetLinenumber, "IDENT", "declaration", "need input  a ']'");
			error.ThrowError();
		}

	}
}
//参数列表解析
void Parser::ParameterList()
{
	while (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() != ")")
	{
		if (!Type_Sign())
		{
			Error error(Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetLinenumber, "IDENT", "declaration", "no such type");
			error.ThrowError();
		}
		Declarator(); //确定 标识符
		if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText == ",")
		{
			Lexer::Lexer_Instance().Lexer_Read();//读取”=“
			continue;
		}
	}
	if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText == ")")
		Lexer::Lexer_Instance().Lexer_Read();
}
//函数体
void Parser::Funbody()
{
	Compound_Statement(); //复合语句
}
//复合语句
void Parser::Compound_Statement()
{
	while (!Type_Sign()) 
	{
		Parser::Parser_Instance().External_Dec(Local);//内部声明 或 定义
	}
	while (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() != "}")
	{
		Statement();//语句
	}
	if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText == "}")
		Lexer::Lexer_Instance().Lexer_Read();
}
//语句
void Parser::Statement()
{
	Token token = Lexer::Lexer_Instance().Lexer_Peek(0);
	switch (API::Instance().Token2Statement(token))
	{
	case Statement_Start: //如果 为 “｛” 即复合语句
			Compound_Statement();
	case If_Statement:
			Statement_If();
	case For_Statement:
			Statement_For();
	case While_Statement:
			Statement_While();
	case Return_Statement:
			Statement_Return();
	case Break_Statement:
			Statement_Break();
	case Continue_Statement:
			Statement_Continue();
	default:
		break;
	}
}
//If语句
void Parser::Statement_If()
{
	Lexer::Lexer_Instance().Lexer_Read();//读取 关键字 “IF”
	if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == "(") //IF语句中的判断表达式
		Lexer::Lexer_Instance().Lexer_Read();
	else
	{
		Error error(Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetLinenumber, "IF", "If_Statement", "need input a '('");
		error.ThrowError();
	}
	Expression();  //判断表达式
	if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == ")")
		Lexer::Lexer_Instance().Lexer_Read();
	else
	{
		Error error(Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetLinenumber, "IF", "If_Statement", "need input a ')'");
		error.ThrowError();
	}
	Statement();
	if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == "else")
	{
		Lexer::Lexer_Instance().Lexer_Read();//读取 else
		Statement();
	}

}
//解析类型符号
bool Parser::Type_Sign()
{
	bool Type_Find = false;
	switch (API::Instance().Token2Type(Lexer::Lexer_Instance().Lexer_Read()))
	{
	case Char:
		Type_Find = true;
	case Int:
		Type_Find = true;
	case Float:
		Type_Find = true;  
	case Void:
		Type_Find = true;
	case String:
		Type_Find = true;
	default:
		break;
	}
	return Type_Find;
}
