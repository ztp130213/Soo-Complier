#include "AST.h"
#include "Global.h"
#include <string>
#include "API.h"
using namespace std;
//变量声明
void AST::AST_Variabledec(Variable variable)
{
	
	//构造语法分析树
	Tree AST_VariabledecTree;
	AST_VariabledecTree.Root.Sign = "Variabledec";
	AST_VariabledecTree.Root.token = "";
	AST_VariabledecTree.Left->Sign = "Type";
	AST_VariabledecTree.Left->token = variable.variable_type;
	AST_VariabledecTree.Right->Sign = "Name";
	AST_VariabledecTree.Right->token = variable.variable_name;
	ASyntax_Tree.push(AST_VariabledecTree);
	API::Instance().Pra_Variable.push_back(variable);
}
//变量定义
void AST::AST_Variabledef(Variable variable)
{
	Tree AST_VariabledefTree;
	AST_VariabledefTree.Root.Sign = "Variabledef";
	AST_VariabledefTree.Root.token = "=";
	AST_VariabledefTree.Left->Sign = "Variablename";
	AST_VariabledefTree.Left->token = variable.variable_name;
	AST_VariabledefTree.Right->Sign = "Value";
	switch (variable.variable_type)
	{
	case Int:
		AST_VariabledefTree.Right->token = variable.Values.Intvalue;
		break;
	case Float:
		AST_VariabledefTree.Right->token = variable.Values.Floatvalue;
		break;
	case Char:
		AST_VariabledefTree.Right->token = variable.Values.Charvalue;
		break;
	case String:
		AST_VariabledefTree.Right->token = variable.Values.Strvalue;
		break;
	default:
		break;
	}
	ASyntax_Tree.push(AST_VariabledefTree);
}
//算术运算
void AST::AST_Arithmetic()
{

}