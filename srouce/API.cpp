#include "API.h"
#include "Parser.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//string 转int
int API::String2Int(string str)
{
	int number = atoi(str.c_str());
	return number;
}
//int 转string
string API::Int2String(int number)
{
	stringstream ss;
	string str;
	ss << number;
	ss >> str;
	return str;
}
//string 转float
float API::String2Float(string str)
{
	float number = atof(str.c_str());
}
//stringn 转char *
char* API::String2CharPlus(string str)
{
	char * Char = str.data();

}
//查询变量是否存在
bool API::API_VariableFind(string variablename)
{
	bool Find = false;
	for (auto i = API::Instance().Pra_Variable.begin(); i != API::Instance().Pra_Variable.end(); i++)
	{
		if (variablename == i->variable_name)
		{
			Find = true;
			break;
		}
	}
	return Find;
}
//欢迎界面
void API::API_Welcome()
{
	string command;
	cout << "       Welcome to Soo       " << endl;
	cout << "            by:Leviathan1995" << endl;
	cout << "File or Input: f or i       " << endl;
	cout << "Please select:              " << endl;
	cin >> command;
	if (command == "f")
		API_ReadFile();
	else
		API_ShellInput();
}

//从文件中读取程序
void API::API_ReadFile()
{
	int LineNumber = 0;
	Token token;
	ifstream Infile("code.txt");
	string Line;
	while (getline(Infile, Line))
	{
		LineNumber++;
		Lexer::Lexer_Instance().Lexer_Readline(Line, LineNumber);
	}
	Queue = Lexer::Lexer_Instance().Lexer_ReturnQueue();
	API::Instance().API_Parser(Queue);
}

//进行语法分析
void API::API_Parser(queue<Token> Queue)
{
	Parser::Parser_Instance().Parsering(Queue);
}