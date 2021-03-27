==============================================================================
							Scanner Implementation
==============================================================================

Note: This program is implemented using FSA table and driver.

-------------------------------------------------------------------------------
Impementation:
	- Implement a token as a triplet {tokenID, tokenInstance, lineNumber} (*if 	 option with line numbers)
	- Implement the scanner in a separate file with basename “scanner”
	- For testing purposes, the scanner will be tested using a testing driver  	 implemented in file with basename “testScanner”. You need to implement   	your own tester and include as a part of the project.
	- This tester will ask the scanner for one token at a time and display the 	 token to the screen, one per line, including information (descriptive)   	on what token class, what token instance, and what line, if applicable. 
-------------------------------------------------------------------------------

Invocation:
    scanner [file]
	- To read from stdin or file file.sp2020

-------------------------------------------------------------------------------

Lexical Definitions
	1. Your language is case sensitive
	2. Each scanner error should display “SCANNER ERROR:” followed by details 	 such as the line number (if you keep track of line number)
	3. Alphabet:
		- All English letters (upper and lower), digits, plus extra 	characters  	below and WS
		- No other characters allowed and they should generate errors
	4. Identifiers:
		- They must begin with an UPPER case or lower case letter and...
		- Continue with any number of letters and digits
		- Assume that no identifier is longer than 8 characters in testing
	5. Keywords (reserved, a good idea to have individual tokens)
		- label | goto | loop | void | declare | return | in | out | program |	iffy | then | assign | data
	6. Operators and delimiters group (all single character except for := and ==) [19 totals]
		- Comparison (Relational) Operators     := == : < >
			-> colonEqual, equalEqual, colon, lessThan, greaterThan,
		- Arithmetic Operators     + - * / %
			-> plus, minus, multiply, divide, modulus
		- Delimiter     . , ; ( ) { } [ ]
			-> dot, comma, semicolon, leftParen, rightParen, leftCurly, rightCurly, leftBracket, rightBracket
	7. Integers
		- Any sequence of decimal digits with no sign and no decimal point
		- You may assume no number longer than 8 characters in testing
	8. Comments start with # and end with #

-------------------------------------------------------------------------------

Documentation
	- In main.cpp, after verifying the file exists and can be opened, the	main() function calls testScanner(), which in turn calls Scanner::scan() for each line in the input file.
	- The FSA table is defined in the scanner.h file. The driver function, testScanner(), is implemented in testScanner.cpp.
	- The checkComment() function check for comment delimiter and ignore all the input if found one. Once an ending tag is found, restore scanner back to normal operation. The Scanner::checkComment() function is implemented in scanner.cpp,
	- The Scanner::scan() will identify the token using the state transition table, and if the table does not return an error state, the scanner() will return the token to testScanner(). Then, testScanner() will display the line number, token name, and token description of the token.
	- For each line of input from the file (or redirected file or keyboard), the testScanner() will do the above until the EOF is reached.

-------------------------------------------------------------------------------

HOW TO RUN
	- In your command prompt, type: make
	- Then in your command prompt, type: make clean
	- Another make to finalize the scanner
	- This will generate .o file and executable file
	- To use the program, type: ./scanner [file] (or the name of your a.out), or type it out to see your result

-------------------------------------------------------------------------------

Examples of invocations

	./scanner
    /scanner < P1_test1.sp2020
    ./scanner P1_test2.sp2020
    ./scanner P1_test3