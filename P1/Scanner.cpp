#include "Scanner.h"

/* ====================================================================================================
* ** This function invoke initOperatorMap() and initKeywordMap() when this object is create.
*/
Scanner::Scanner() : SCANNER_DELIMITER(' ')
{
	this->current_scanner_pointer = 0;
	this->isCommenting = false;
	this->lastCommentPosition = "";
	int aux[4][6] = {
		{IDENTIFIER, INTEGER, INITIAL_STATE, STATE_EOF, OPERATOR, UNKNOWN_ERROR},
		{OPERATOR_FINAL_STATE, OPERATOR_FINAL_STATE, OPERATOR_FINAL_STATE, OPERATOR_FINAL_STATE, OPERATOR_FINAL_STATE, UNKNOWN_ERROR},
		{IDENTIFIER, IDENTIFIER, IDENTIFIER_FINAL_STATE, IDENTIFIER_FINAL_STATE, IDENTIFIER_FINAL_STATE, UNKNOWN_ERROR},
		{INTEGER_ERROR, INTEGER, INTEGER_FINAL_STATE, INTEGER_FINAL_STATE, INTEGER_FINAL_STATE, UNKNOWN_ERROR}};
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			this->FSA_TABLE[i][j] = aux[i][j];
		}
	}
	setValues();
	initOperatorMap();
	initKeywordMap();
}

/*
* ** This function return the category column number when a match is found.
*/
int Scanner::getCharacterType(char ch)
{
	// If alphabet
	if (isalpha(ch))
		return 0;

	// If digit
	else if (isdigit(ch))
		return 1;

	// If space
	else if (isspace(ch))
		return 2;

	// If operator
	else if (isOperator(ch) != -1)
		return 4;

	// Return 5 if type not found
	else
		return 5;
}

/* 
* ** This function print the appropriate error message base on the error stage.
*/
void Scanner::printError(int current_line, int state, char ch)
{
	cout << "ERROR at (" << current_line << ":" << current_scanner_pointer << ") -> {" << ch << "]: ";
	if (state == INTEGER_ERROR)
	{
		cout << "all integer token must contain only digits.\n";
		cout << "ERROR code: " << INTEGER_ERROR << '\n';
	}
	else if (state == UNKNOWN_ERROR)
	{
		cout << "unknown token\n";
		cout << "ERROR code: " << UNKNOWN_ERROR << '\n';
	}
}

/*
* ** This function check for comment delimiter and ignore all the input if found one. Once an ending tag
* ** is found, restore scanner back to normal operation.
*/
char Scanner::checkComment(int current_line, char ch)
{
	if (ch == COMMENT_DELIMITER)
	{
		isCommenting = !isCommenting;

		if (isCommenting)
		{
			ostringstream temp;
			temp << current_line << ":" << current_scanner_pointer;
			lastCommentPosition = temp.str();
		}
		return SCANNER_DELIMITER;
	}

	if (isCommenting)
	{
		return SCANNER_DELIMITER;
	}
	else
	{
		return ch;
	}
}

/*
* ** This function check if comment tag still open, if it, then display a warning message.
*/
void Scanner::isCommentMode()
{
	if (isCommenting)
	{
		cout << "WARNING at (" << lastCommentPosition << ") -> comment tag never close" << endl;
	}
}

/*
* ** This function main function that identify the token using the state transition table, and if the
* ** table does not return an error state.
*/
int Scanner::scan(int current_line, string &input, Token &tk)
{
	//Set current line number for the current token
	tk.line_number = current_line;

	//Init variable for tracking
	int current_state = 0;
	int next_state = 0;
	int next_category = 0;
	string read_token_instance;
	char next_char;

	while (current_scanner_pointer <= input.length())
	{
		if (current_scanner_pointer < input.length())
		{
			next_char = checkComment(current_line, input.at(current_scanner_pointer));
		}
		else
		{
			next_char = SCANNER_DELIMITER;
		}

		//Look at FSA Table and obtain the next state
		next_category = getCharacterType(next_char);
		next_state = FSA_TABLE[current_state][next_category];

		// If this is an error state
		if (next_state < 0)
		{
			printError(current_line, next_state, next_char);
			exit(EXIT_FAILURE); //the scanner scanning when encounting error
		}
		//If this is the final state.
		else if (next_state > FINAL_STATE)
		{
			tk.token_instance = read_token_instance;

			// Checking for appropriarte final state

			switch (next_state)
			{
			case IDENTIFIER_FINAL_STATE:
				if (getKeyword(tk) != -1)
				{
					tk.id = keywordTk;
					tk.token_instance.append(" " + read_token_instance);
				}
				else
				{
					tk.id = idTk;
					tk.token_instance.assign("idTk " + read_token_instance);
				}
				break;

			case INTEGER_FINAL_STATE:
				tk.id = intTk;
				tk.token_instance.assign("intTk " + read_token_instance);
				break;

			case OPERATOR_FINAL_STATE:
				tk.id = opTk;

				//Check to see if it non-single operator
				if (current_scanner_pointer < input.length())
				{
					string ns_operator = read_token_instance + input.at(current_scanner_pointer);
					if (isNonSingleOperator(ns_operator) != -1)
					{
						read_token_instance = ns_operator;
						current_scanner_pointer++;
					}
				}

				tk.token_instance.assign(read_token_instance);
				getOperator(tk);
				tk.token_instance.append(" " + read_token_instance);
				break;
			}

			//Increment scanner pointer when open comment tag is found
			if (isCommenting)
			{
				current_scanner_pointer++;
			}
			return 0;
		}

		current_state = next_state;
		current_scanner_pointer++;

		//If not white space, update reading token_instance of the token
		if (!isspace(next_char))
		{
			read_token_instance.push_back(next_char);
		}
	}

	current_scanner_pointer = 0;
	return -1;
}