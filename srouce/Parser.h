#pragma once
#ifndef _PARSER_H
#define _PARSER_H
/*
		语法分析
*/
class Parser
{
public:
	static Parser & Instance();
	void Parsering();			//进行语法分析
};
inline Parser & Instance()
{
	Parser parser;
	return parser;
}
#endif