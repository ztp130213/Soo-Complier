#include "AST.h"
#include "Global.h"
#include <string>
using namespace std;
//变量声明或定义
void AST::AST_Variabledec()
{
	Variable_Type variable_type;//变量类型
	string variable_name;		//变量名字
	union variable_values		//如果是声明语句则没有值，如果是定义语句则有值
	{
		int values;
		char values;
		float values;
		char * values;//string 类型
	};
}
//算术运算
void AST::AST_Arithmetic()
{

}