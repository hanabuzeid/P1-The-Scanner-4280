#ifndef TOKEN_H
#define TOKEN_H
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <initializer_list>
using namespace std;

/* Enumeration */
enum token_id
{
	idTk,
	keywordTk,
	intTk,
	opTk,
	eofTk
};

/* Token Structure */
class Token
{
public:
	token_id id;
	int line_number;
	string token_instance;
};

/* Language Class */
class Language
{
public:
	//Operator & Keyword Mapping
	map<string, string> operator_map;
	map<string, string> keyword_map;

	//Token Categories
	vector<string> token_names; /* = {
		"Identfier", "Keyword", "Integer", "Operator", "End Of File"
	};*/
								//	token_names.push_back("Identfier");

	//Keywords
	vector<string> keywords; /* = {
		"label", "goto", "loop", "void", "declare",
		"return", "in", "out", "program", "iffy",
		"then", "assign", "data"
	};*/

	//Delimiter
	char COMMENT_DELIMITER;

	//Operator (single and non-single)
	vector<char> operators;		 /* = { '=', '<', '>', ':', '+', '-', '*', '/', '%', '.', ',', ';', '(', ')', '{', '}', '[', ']' };*/
	vector<string> ns_operators; /* = { ":=", "==" };*/
	Language() : COMMENT_DELIMITER('#') {}
	void setValues();
	void initOperatorMap();
	void initKeywordMap();
	int isOperator(char ch);
	int isNonSingleOperator(string str);
	int getOperator(Token &tk);
	int getKeyword(Token &tk);
	void tokenToString(Token tk);
};
#endif