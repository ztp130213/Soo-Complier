#include "Parser.h"
#include "AST.h"
#include "Error.h"
#include "Global.h"
using namespace std;
void Parser::Parsering(queue<Token> Queue)
{
	Token token;
	while (Lexer::Lexer_Instance().Lexer_Read() != StopEOF)
	{
		token = Lexer::Lexer_Instance().Lexer_Peek(0);
		if (token.Token_GetText() == "dec") //声明或定义语句
			Parser_Dec();
		if (token.Token_GetText() == "if")  //if else 语句块
			Parser_If();

	}
}
//声明或定义语句
void Parser::Parser_Dec()
{
	Variabledec NewVariable;
	Lexer::Lexer_Instance().Lexer_Read(); //读取dec
	Token token = Lexer::Lexer_Instance().Lexer_Read();
	string Type =token.Token_GetText();//读取类型
	if (Type == "int")
		NewVariable.variable_type == Int;
	else if (Type == "char")
		NewVariable.variable_type == Char;
	else if (Type == "float")
		NewVariable.variable_type == Float;
	else if (Type == "string")
		NewVariable.variable_type == String;
	else
	{
		Error error(token.Token_GetLinenumber, "Variable", "declaration", "no such type");
		error.ThrowError();
	}
	string name = Lexer::Lexer_Instance().Lexer_Read().Token_GetText();
	NewVariable.variable_name = name;
	if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == "=") //为定义变量语句
	{
		Lexer::Lexer_Instance().Lexer_Read();//读取"="
		switch (NewVariable.variable_type)
		{
		case Int:
			NewVariable.Values.Intvalue = Lexer::Lexer_Instance().Lexer_Read().Token_GetText();
		default:
			break;
		}
	}
		
}