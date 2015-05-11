#include "Parser.h"
#include "Error.h"
#include "Global.h"
#include "API.h"
#include "SymbolTable.h"
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
//Token 是否合法的预判
void Parser::Token_Judge(string token, string module, string function, string error)
{
	if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == token)
		Lexer::Lexer_Instance().Lexer_Read();
	else
	{
		Error error(Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetLinenumber,module, function, error);
		error.ThrowError();
	}
}
//声明符是否为关键字
bool Parser::Is_Keyword(Token token)
{
	string StrToken = token.Token_GetText();
	if (StrToken != "int"&&StrToken != "char"&&StrToken != "float"&&StrToken != "string"&&StrToken != "void"&&StrToken != "return"&&
		StrToken != "break"&&StrToken != "continue"&&StrToken != "struct")
		return true;
	else
		return false;
}
//声明符是否合法
bool Parser::D_Legal(Token token)
{
	string StrToken = token.Token_GetText();
	char First = StrToken[0];
	if (First >= '0'&&First <= '9')
		return true;
	else
		return false;
}
//声明符合法判断
bool Parser::Declaration_Legal(Token token)
{
	bool is_Keyword, d_Legal;
	if (Is_Keyword(token))
		is_Keyword = true; //是关键字
	else
		is_Keyword = false; //不是关键字
	if (D_Legal(token))
		d_Legal = true; //是合法的
	else
		d_Legal = false;//不是合法的
	if (!is_Keyword&&d_Legal)
		return true;
	else
		return false;
}


//解析声明 ，功能：声明与函数定义
void Parser::External_Dec(External state)
{
	Symbol_System::Symbol_SystemInstance().Symbol_CreateTree();//构建符号表系统树形结构,即创建根结点
	Symbol_System::Symbol_SystemInstance().SymbolPointer = Symbol_System::Symbol_SystemInstance().SymbolTreeRoot;//将根结点赋给实时结点
	Symbol symboldata;
	if (!Type_Sign(symboldata)) //类型判断
	{
		Error error(Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetLinenumber, "Type", "declaration", "no such type");
		error.ThrowError();
	}
	if (symboldata.DType == T_Struct)
		Symbol_System::Symbol_SystemInstance().Symbol_Add(symboldata); //如果是结构即已经判断完毕，直接加入符号表的树形结构
	if (symboldata.Type==T_Struct&& Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == ";")
	{
		Lexer::Lexer_Instance().Lexer_Read();
		return;
	}
	while (1) //逐个分析声明或函数定义
	{
		Declarator(symboldata); //声明标识符
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
		else if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == ";") //声明结束
		{
			
		}
		else //定义变量
		{
			if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == "=")
			{
				Lexer::Lexer_Instance().Lexer_Read();//读取“=”
				Init(); //变量初值
			}
		}
	}
}
//解析类型符号
bool Parser::Type_Sign(Symbol & symboldata)
{
	bool Type_Find = false;
	switch (API::Instance().Token2Type(Lexer::Lexer_Instance().Lexer_Read()))  //读取类型
	{
	case Char:
		symboldata.Type = T_Char;
		Type_Find = true;
	case Int:
		symboldata.Type = T_Int;
		Type_Find = true;
	case Float:
		symboldata.Type = T_Float;
		Type_Find = true;
	case Void:
		symboldata.Type = T_Void;
		Type_Find = true;
	case String:
		symboldata.Type = T_String;
		Type_Find = true;
	case Struct:
		Struct_Specifier(symboldata);  //结构体类型解析
		symboldata.Type = T_Struct;
		Type_Find = true;
	default:
		break;
	}
	return Type_Find;
}
//Struct结构体类型解析
void Parser::Struct_Specifier(Symbol & symboldata)
{
	Token token = Lexer::Lexer_Instance().Lexer_Read();// 读取结构体名字
	if (!Declaration_Legal(token)) //结构体名字合法性判断
	{
		Error error(Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetLinenumber, "Struct", "Struct  declaration", "Struct name is not legal");
		error.ThrowError();
	}
	symboldata.Name = token.Token_GetText(); //获取结构体名字
	if (Struct_Search(token) == NULL) //如果没有找到这个名字的结构体
	{
		symboldata.Type = T_Struct;

	}
	if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == "{")
	{
		Struct_DeclarationList(symboldata); //结构体声明符表
	}
}
//Struct结构体声明符表
void Parser::Struct_DeclarationList(Symbol &symboldata)
{
	while (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() != "}")
	{
		Struct_Declaration(symboldata);
	}
	Lexer::Lexer_Instance().Lexer_Read();//读取“｝”
}
//Struct结构体声明
void Parser::Struct_Declaration(Symbol & symboldata)
{
	Symbol StructAttribtues;
	Type_Sign(StructAttribtues); //数据类型判断
	while (1)
	{
		Declarator(StructAttribtues);
		if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == ";")
			break;
		Token_Judge(",", "Struct", "Struct_Declaration", "need input a ','");
	}
	symboldata.Symbol_struct->Struct_Number.push_back(StructAttribtues);
}
//Struct结构体是否已经存在，并进行查找 
Symbol* Parser::Struct_Search(Token token)
{
	
}
//变量初值
void Parser::Init()
{
	Assign_Expression();
}
//声明 标识符
void Parser::Declarator(Symbol & symboldata)
{
	Token token;
	if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_IsId)
	{
		token=Lexer::Lexer_Instance().Lexer_Read(); //读取这个标识符
	}
	else
	{
		Error error(Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetLinenumber, "Ident", "declaration", "need input a ID");
		error.ThrowError();
	}
	if (!Declaration_Legal(token)) //名字合法性判断
	{
		Error error(Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetLinenumber, "Declarator", "  declaration", "Declarator name is not legal");
		error.ThrowError();
	}
	symboldata.Name = token.Token_GetText();//符号表获取标识符
	Declarator_Postfix(symboldata); //声明符后缀
}
//声明符后缀 ，即判断函数 、数组声明
void Parser::Declarator_Postfix(Symbol & symboldata)
{
	if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == "(")	//函数
	{
		Lexer::Lexer_Instance().Lexer_Read(); //读取”（“
		Symbol_Function  symbol_function;
		Func_ParameterList(symbol_function); //函数参数列表解析
		symboldata.Symbol_function = &symbol_function;
	}
	else if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == "[") //数组
	{
		int Length;
		Lexer::Lexer_Instance().Lexer_Read(); //读取"["
		if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_IsNumber())
		{
			Length=Lexer::Lexer_Instance().Lexer_Read().Token_GetNumber(); //读取 数组大小
		}
		Token_Judge("]", "Declarator_Postfix", "Array", "need input a ']'");
		Symbol_Array symbol_array;
		symbol_array.Length = Length;
		symboldata.Symbol_array = &symbol_array;
	}
}
//函数参数列表解析
void Parser::Func_ParameterList(Symbol_Function &symbol_funciton)
{
	while (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() != ")")
	{
		Symbol Func_Parameter;//函数参数
		if (!Type_Sign(Func_Parameter))
		{
			Error error(Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetLinenumber, "Ident", "declaration", "no such type");
			error.ThrowError();
		}
		Declarator(Func_Parameter); //确定 标识符
		Symbol_FuncParam symbol_funcparam;
		symbol_funcparam.name = Func_Parameter.Name;
		symbol_funcparam.type = Func_Parameter.DType;
		symbol_funciton.Func_ParamList.push_back(symbol_funcparam);
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
		Statement_Expression();//表达式
		break;
	}
}
//If语句
void Parser::Statement_If()
{
	Lexer::Lexer_Instance().Lexer_Read();//读取 关键字 “IF”
	Token_Judge("(", "If", "If_Statement", "need input a '('");
	Statement_Expression();  //判断表达式
	Token_Judge(")", "If", "If_Statement", "need input a ')'");
	Statement();//语句块
	if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == "else")
	{
		Lexer::Lexer_Instance().Lexer_Read();//读取 else
		Statement();
	}
}
//while语句
void Parser::Statement_While()
{
	Lexer::Lexer_Instance().Lexer_Read();//读取 关键字 “While”
	Token_Judge("(", "While", "While_Statement", "need input a '('");
	Statement_Expression();  //判断表达式
	Token_Judge(")", "While", "While_Statement", "need input a ')'");
	Statement();//语句块
}
//For语句
void Parser::Statement_For()
{
	Lexer::Lexer_Instance().Lexer_Read();//读取关键字 “for”
	Token_Judge("(", "For", "For_Statement", "need input a '('");
	Statement_Expression();//判断表达式
	Token_Judge(";", "For", "For_Statement", "need input a ';'");
	Statement_Expression();//判断表达式
	Token_Judge(";", "For", "For_Statement", "need input a ';'");
	Statement_Expression();//判断表达式
	Token_Judge(")", "For", "For_Statement", "need input a ')'");
	Statement();//语句块
}
//Return  语句
void Parser::Statement_Return()
{
	Lexer::Lexer_Instance().Lexer_Read(); //读取 "return "
	if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == ";")
		Lexer::Lexer_Instance().Lexer_Read(); //读取 “;"
	else
	{ 
		Statement_Expression();  //形如return ***;
		Token_Judge(";", "Return", "Return_Statement", "need input a ';'");
	}
}
//Break 语句
void Parser::Statement_Break()
{
	Lexer::Lexer_Instance().Lexer_Read();//读取 “Break"
	Token_Judge(";", "Break", "Break_Statement", "need input a ';'");
}
//continue 语句
void Parser::Statement_Continue()
{
	Lexer::Lexer_Instance().Lexer_Read();//读取 continue 
	Token_Judge(";", "Continue", "Continue_Statement", "need input a ';'");
}
//Expreesion 表达式
void Parser::Statement_Expression()
{
	while (1)
	{
		Assign_Expression();
		if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == ",")
			break;
	}
}
/*
	根据运算符优先级进行编写对应的函数嵌套
*/
//赋值表达式
void Parser::Assign_Expression()
{
	Equal_Expression();
	if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == "=")
	{
		Lexer::Lexer_Instance().Lexer_Read(); //读取 ”=“
		Assign_Expression();
	}
}
//相等表达式
void Parser::Equal_Expression()
{
	Relation_Expression();
	while (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == "==" || Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == "!=")
	{
		Lexer::Lexer_Instance().Lexer_Read();
		Relation_Expression();
	}
}
//关系表达式
void Parser::Relation_Expression()
{
	Add_Expression();
	while (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == "<" || Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == ">"
		|| Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == "<=" || Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == ">=")
	{
		Lexer::Lexer_Instance().Lexer_Read();
		Add_Expression();
	}
}
//加减类表达式
void Parser::Add_Expression()
{
	Multilpi_Expression();
	while (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == "+" || Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == "-")
	{
		Lexer::Lexer_Instance().Lexer_Read();
		Multilpi_Expression();
	}
}
//乘除类表达式
void Parser::Multilpi_Expression()
{
	Unary_Expression();
	while (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == "*" || Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == "/")
	{
		Lexer::Lexer_Instance().Lexer_Read();
		Unary_Expression();
	}
}
//一元运算表达式
void Parser::Unary_Expression()
{
	switch (API::Instance().Token2Operator(Lexer::Lexer_Instance().Lexer_Peek(0)))
	{
	case Plus:
		Lexer::Lexer_Instance().Lexer_Read();
		Unary_Expression();
		break;
	case Minus:
		Lexer::Lexer_Instance().Lexer_Read();
		Unary_Expression();
		break;
	default:
		Postfix_Expression();
		break;
	}
}
//表达式的后缀
void Parser::Postfix_Expression()
{
	Variable_Expression();
	while (1)
	{
		if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == "(") //函数
			ArgumentList();
		else if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == "[")
		{
			Lexer::Lexer_Instance().Lexer_Read();
			Statement_Expression();
			Token_Judge("]", "Postfix", "Postfix_Expression", "need input a ']'");
		}
	}
}
//变量个体
void Parser::Variable_Expression()
{
	switch (API::Instance().Token2Type(Lexer::Lexer_Instance().Lexer_Peek(0)))
	{
	case Int:
	case Char:
	case Float:
	case String:
		break;
	default:
	{
			   Error error(Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetLinenumber, "Variable", "Variable_Expression", "no such type variable");
			   error.ThrowError();
			   break;
	}
	}
}
//函数实参数表达式
void Parser::ArgumentList()
{
	Lexer::Lexer_Instance().Lexer_Read();//读取 "("
	if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() != ")")
	{
		for (;;)
		{
			Assign_Expression();
			if (Lexer::Lexer_Instance().Lexer_Peek(0).Token_GetText() == ")")
				break;
			Token_Judge(",", "ArgumentList", "Parameter list ", "need input a ','");
		}
	}
	Token_Judge(")", "ArgumentList", "Parameter list ", "need input a ')'");
}
