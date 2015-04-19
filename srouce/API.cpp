#include "API.h"
#include "Parser.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

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
		Lexer::Instance().Lexer_Readline(Line, LineNumber);
	}
	Queue = Lexer::Instance().Lexer_ReturnQueue();
	API::Instance().API_Parser(Queue);
}

//进行语法分析
void API::API_Parser(queue<Token> Queue)
{
	Parser::Instance().Parsering(Queue);
}