#include <iostream>
#include <string>  
#include <cstring> 
#include <cstdio>  
#include <fstream> 
#include "TestScanner.h"
using namespace std;


/*
* ** Driver function
*/

int main(int argc, char *argv[])
{
	/* Input/output Files */
	string input_file;
	string output_file;

	/* Processing program given arguments */
	switch (argc)
	{
	case 1:
	{
		cout << "Input from keyboard: \n";
		string in;
		ofstream temp_file;
		int line_no = 1;
		//Set file name for temporary file
		input_file = "input.txt";
		temp_file.open(input_file.c_str());

		//Writing user input into a temporary file and close the file when done
		cout << "Enter string (Just press enter to finish the program)\n";
		do
		{
			cout << "Line " << line_no << " : ";
			getline(cin, in);
			temp_file << in << endl;
			line_no++;
		} while (!in.empty());

		//Close file when done
		cout << "Input finished...\n\n";
		temp_file.close();
		output_file = "output";
		break;
	}

	/*
	* ** If given file name doesn't contains extension, it added an implicit extension .sp2020
	*/

	case 2:
	{
		cout << "Input from file.\n\n";

		//Construct output file name
		input_file = argv[1];
		size_t extension_index = input_file.find(".");
		if (extension_index == string::npos)
		{
			output_file = input_file;
			input_file.append(".sp2020");
		}
		else
			output_file = input_file.substr(0, extension_index);
		break;
	}

	/*
	* ** If given prgram arguments invalid
	*/
	default:
	{
		cout << "Too many arguments!\n";
		cout << "Usage: " << argv[0] << " [file]\n";
		return 1;
	}
	}

	/* Invoking Test Program */
	TestScanner(input_file);

	return 0;
}