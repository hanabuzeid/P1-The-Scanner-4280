#ifndef SCANNER_H
#define SCANNER_H
#include <iostream>
#include <string>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <sstream>
#include <cstdio>
#include "token.h"
using namespace std;

/* Scanner Class */
class Scanner : public Language
{
private:
	//Scanner Tracker
	unsigned int current_scanner_pointer;
	bool isCommenting;
	string lastCommentPosition;
	//All possible states in the FSA table
	enum
	{
		UNKNOWN_ERROR = -2,
		INTEGER_ERROR = -1,
		INITIAL_STATE = 0,
		OPERATOR = 1,
		IDENTIFIER = 2,
		INTEGER = 3,
		FINAL_STATE = 1000,
		IDENTIFIER_FINAL_STATE = 1001,
		INTEGER_FINAL_STATE = 1003,
		OPERATOR_FINAL_STATE = 1004,
		STATE_EOF = 1005
	};

	int FSA_TABLE[4][6];

	//Scanner Delimiter
	const char SCANNER_DELIMITER;

	int getCharacterType(char ch);
	void printError(int current_line, int state, char ch);
	char checkComment(int current_line, char ch);

public:
	Scanner();
	int scan(int current_line, string &input, Token &tk);
	void isCommentMode();
};
#endif