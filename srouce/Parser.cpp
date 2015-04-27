#include "Parser.h"
#include "AST.h"
#include "Error.h"
#include "Global.h"
#include "API.h"
using namespace std;
void Parser::Parsering(queue<Token> Queue)
{
	Token token;
	while (Lexer::Lexer_Instance().Lexer_Read() != StopEOF)
	{
		External_Dec(Global);
	}
}
//解析外部声明
void Parser::External_Dec(External state)
{
	if (!Type_Sign())
	{
		Error error(Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetLinenumber, "Type", "declaration", "no such type");
		error.ThrowError();
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
//变量声明或定义区
void Parser::Parser_Var()
{
	Token token = Lexer::Lexer_Instance().Lexer_Read();//读取"Var"
	token = Lexer::Lexer_Instance().Lexer_Read();	//读取":"
	if (token.Token_GetText() != ":")
	{
		Error error(token.Token_GetLinenumber, "Variable", "Parser_Var", "need a '：'");
		error.ThrowError();
	}
	while (API::Instance().String2CharPlus(Lexer::Lexer_Instance().Lexer_Read().Token_GetText()) != "Program")
	{
		if (token.Token_GetText() == "dec") //声明变量语句
			Parser_Dec();
		if (token.Token_GetText() == "def") //定义变量语句
			Parser_Def();
		if (token.Token_GetText() == "\\n") //如果是换行符号
			continue;
	}
}
//变量声明
void Parser::Parser_Dec()
{
	Variable NewVariable;
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
	AST::AST_Instance().AST_Variabledec(NewVariable);
}
//变量定义
void Parser::Parser_Def()
{
	Lexer::Lexer_Instance().Lexer_Read(); //读取def
	Variable variable;
	Token token = Lexer::Lexer_Instance().Lexer_Read();
	string variablename = token.Token_GetText(); //获取变量名
	for (auto i = API::Instance().Pra_Variable.begin(); i != API::Instance().Pra_Variable.end(); i++)
	{
		if (variablename == i->variable_name)
		{
			variable = *i;
			break;
		}
	}
	if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() != "=")
	{
		Error error(token.Token_GetLinenumber, "Variable", "declaration", "need a '='");
		error.ThrowError();
	}
	else
		Lexer::Lexer_Instance().Lexer_Read(); //读取“=”
	if (API::Instance().API_VariableFind(variablename)) //查找这个变量,if存在
	{
		variable = API::Instance().API_ReturnVar(variablename);
		switch (variable.variable_type)
		{
		case Int:
			variable.Values.Intvalue = API::Instance().String2Int(Lexer::Lexer_Instance().Lexer_Read().Token_GetText());
			break;
		case Float:
			variable.Values.Floatvalue = API::Instance().String2Float(Lexer::Lexer_Instance().Lexer_Read().Token_GetText());
			break;
		case Char:
			variable.Values.Charvalue = API::Instance().String2Int(Lexer::Lexer_Instance().Lexer_Read().Token_GetText[0]);
			break;
		case String:
			variable.Values.Strvalue = API::Instance().String2CharPlus(Lexer::Lexer_Instance().Lexer_Read().Token_GetText());
			break;

		}
	}
	else  //变量不存在
	{
		Error error(token.Token_GetLinenumber, "Variable", "declaration", "no such variable");
		error.ThrowError();
	}
	AST::AST_Instance().AST_Variabledef(variable); //构建语法分析树
}
//程序区段
void Parser::Parser_Pra()
{

}