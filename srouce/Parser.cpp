#include "Parser.h"
#include "AST.h"
void Parser::Parsering(queue<Token> Queue)
{
	Token token;
	while (Lexer::Instance().Lexer_Read() != StopEOF)
	{
		token = Lexer::Instance().Lexer_Read();
		if (token.Token_GetText == "dec") //声明或定义语句
			Parser_Dec();
		if (token.Token_GetText == "if")  //if else 语句块
			Parser_If();

	}
}
//声明或定义语句
void Parser::Parser_Dec()
{
	if (Lexer::)
}