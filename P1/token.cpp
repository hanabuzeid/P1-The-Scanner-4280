#include "token.h"

void Language::setValues() {
	token_names.push_back("Identfier");
	token_names.push_back("Keyword");
	token_names.push_back("Integer");
	token_names.push_back("Operator");
	token_names.push_back("End Of File");

	keywords.push_back("label");
	keywords.push_back("goto");
	keywords.push_back("loop");
	keywords.push_back("void");
	keywords.push_back("declare");
	keywords.push_back("return");
	keywords.push_back("in");
	keywords.push_back("out");
	keywords.push_back("program");
	keywords.push_back("iffy");
	keywords.push_back("then");
	keywords.push_back("assign");
	keywords.push_back("data");
	
	operators.push_back('=');
	operators.push_back('<');
	operators.push_back('>');
	operators.push_back(':');
	operators.push_back('+');
	operators.push_back('-');
	operators.push_back('*');
	operators.push_back('/');
	operators.push_back('%');
	operators.push_back('.');
	operators.push_back(',');
	operators.push_back(';');
	operators.push_back('(');	
	operators.push_back(')');	
	operators.push_back('{');
	operators.push_back('}');
	operators.push_back('[');
	operators.push_back(']');

	ns_operators.push_back(":=");
	ns_operators.push_back("==");
}

/* 
* ** Thsi function populate the operator map with the choosen lexical.
*/
void Language::initOperatorMap()
{
	operator_map.insert(make_pair(":=", "colonEqualTk"));
	operator_map.insert(make_pair("==", "equalEqualTk"));
	operator_map.insert(make_pair("=", "equalTk"));
	operator_map.insert(make_pair("<", "lessThanTk"));
	operator_map.insert(make_pair(">", "greaterThanTk"));
	operator_map.insert(make_pair(":", "colonTk"));
	operator_map.insert(make_pair("+", "plusTk"));
	operator_map.insert(make_pair("-", "minusTk"));
	operator_map.insert(make_pair("*", "multiplyTk"));
	operator_map.insert(make_pair("/", "divideTk"));
	operator_map.insert(make_pair("%", "modulusTk"));
	operator_map.insert(make_pair(".", "dotTk"));
	operator_map.insert(make_pair(",", "commaTk"));
	operator_map.insert(make_pair(";", "semiColonTk"));
	operator_map.insert(make_pair("(", "leftParenTk"));
	operator_map.insert(make_pair(")", "rightParenTk"));
	operator_map.insert(make_pair("{", "leftCurlyTk"));
	operator_map.insert(make_pair("}", "rightCurlyTk"));
	operator_map.insert(make_pair("[", "leftBracketTk"));
	operator_map.insert(make_pair("]", "rightBracketTk"));
}


/*
* ** This function populate the keyword map with the choosen lexical.
*/
void Language::initKeywordMap()
{
	keyword_map.insert(make_pair("label", "labelTk"));
	keyword_map.insert(make_pair("goto", "gotoTk"));
	keyword_map.insert(make_pair("loop", "loopTk"));
	keyword_map.insert(make_pair("void", "voidTk"));
	keyword_map.insert(make_pair("declare", "declareTk"));
	keyword_map.insert(make_pair("return", "returnTk"));
	keyword_map.insert(make_pair("in", "inTk"));
	keyword_map.insert(make_pair("out", "outTk"));
	keyword_map.insert(make_pair("program", "programTk"));
	keyword_map.insert(make_pair("iffy", "iffyTk"));
	keyword_map.insert(make_pair("then", "thenTk"));
	keyword_map.insert(make_pair("assign", "assignTk"));
	keyword_map.insert(make_pair("data", "dataTk"));
}


/*
* ** This function display the line number of the token, followed by the category of the token (Identifier,
* ** Integer, Operator, etc), followed by the specific token name (IDtk, THENtk, etc),
* ** followed by the token description (token_instance of the token).
*/
void Language::tokenToString(Token tk)
{
	cout << "Line # : " << tk.line_number << '\n';
	cout << "Token name : " << token_names[tk.id] << '\n';
	cout << "Token instance : " << tk.token_instance << "\n\n";
}


/*
* ** Thsi function return true (1) or false (-1) if the input char is an operator.
*/
int Language::isOperator(char ch)
{
	//Return 1 when input character is an operator
	for (unsigned int i = 0; i < operators.size(); i++) {
		if (ch == operators[i]) {
			return 1;
		}
	}

	//Return -1 when input character is not an operator
	return -1;
}


/*
* ** This function return true (1) or false (-1) if the input char is a non-single operator.
*/
int Language::isNonSingleOperator(string str)
{
	//Return 1 when input string is a non-single operator
	for (unsigned int i = 0; i < ns_operators.size(); i++) {
		if (str.compare(ns_operators[i]) == 0) {
			return 1;
		}
	}

	//Return -1 when input character is not a non-single operator
	return -1;
}


/*
* ** Thsi function return single or non-single operator key (assuming it already been verify it's an operator).
*/
int Language::getOperator(Token &tk)
{
	//Check single character operator
	for (unsigned int i = 0; i < operators.size(); i++) {
		string op(1, operators[i]);
		if (tk.token_instance.compare(op) == 0) {
			tk.token_instance = operator_map[tk.token_instance];
			return i;
		}
	}

	//Check non-single character operator
	for (unsigned int i = 0; i < ns_operators.size(); i++) {
		if (tk.token_instance.compare(ns_operators[i]) == 0) {
			tk.token_instance = operator_map[tk.token_instance];
			return i;
		}
	}

	//Return -1 when input token is not a keyword
	return -1;
}


/*
* This function return keyword key if it's a keyword.
*/
int Language::getKeyword(Token &tk)
{
	//Return keyword key when input token is a keyword
	for (unsigned int i = 0; i < keywords.size(); i++) {
		if (tk.token_instance.compare(keywords[i]) == 0) {
			tk.token_instance = keyword_map[tk.token_instance];
			return i;
		}
	}

	//Return -1 when input token is not a keyword
	return -1;
}