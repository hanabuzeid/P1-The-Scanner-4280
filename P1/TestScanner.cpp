#include "token.h"
#include "Scanner.h"
#include "TestScanner.h"

/*
* ** This function a simple function to test out the scanner.
*/
int TestScanner(string file_name)
{
	//Init Scanner Object
	Scanner scanner;

	//Check if the file is open and associated with the stream object
	ifstream file(file_name.c_str());
	unsigned int current_line = 1;
	Token token;
	if (file.is_open())
	{
		string input;
		while (getline(file, input))
		{
			while (scanner.scan(current_line, input, token) == 0)
				scanner.tokenToString(token);

			current_line++; //Increment the currnet line in the file when finish reading the current input
		}

		//Check for any open comment tag
		scanner.isCommentMode();
	}
	else
	{
		cout << "[ERROR] Can't open file!" << endl;
		return -1;
	}

	//Once all lines of the files has been traverse, print the EOF token
	if (file.eof())
	{
		if (current_line > 1)
		{
			current_line--;
		}

		//Display EOF token
		token.line_number = current_line;
		token.id = eofTk;
		token.token_instance = "EOF";
		scanner.tokenToString(token);
	}

	//Close the reading file
	file.close();
	return 0;
}