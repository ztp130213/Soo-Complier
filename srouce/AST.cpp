#include "AST.h"
#include "Global.h"
#include <string>
using namespace std;
//变量声明或定义
void AST::AST_Variabledec()
{
	
	//构造语法分析树
	Tree AST_VariabledecTree;
	AST_VariabledecTree.Root.Sign = "Variabledec";
	AST_VariabledecTree.Root.token = NULL;
	AST_VariabledecTree.Left->Sign = "dec";
	AST_VariabledecTree.Left->token = NULL;
	AST_VariabledecTree.Left->Left->Sign = "type";
	AST_VariabledecTree.Left->Left->
}
//算术运算
void AST::AST_Arithmetic()
{

}