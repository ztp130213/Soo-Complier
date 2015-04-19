#include "Parser.h"
void Parser::Parsering(queue<Token> Queue)
{
	Token token;
	token = Lexer::Instance().Lexer_Read();
	while (Lexer::Instance().Lexer_Read() != StopEOF)
	{

	}
}