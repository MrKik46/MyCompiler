#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <regex>
#include "workWithFile.h"
#include "lexer.h"
#include "parser.h"
#include "tokenSort.h"
#include "errorSort.h"


int main() {
	
	WorkWithFile CodeToAnalysis;
	std::string code_str = CodeToAnalysis.get_lines();
		
	Lexer MyLexer = Lexer(code_str);
	std::vector<token> tokenlist = MyLexer.creat_tokelist();
	tokenlist = sortTokenList(tokenlist);

	Parser MyParser = Parser(tokenlist);
	std::vector<Error> errorlist = MyParser.creat_errorlist();
	errorlist = sortErrorList(errorlist);

	CodeToAnalysis.log_errors(errorlist);

	return 0;
}

