#include <iostream>
#include <string.h>
#include <vector>

class token {
public:
	std::string type;
	std::string text;
	int position;

	token(std::string token_type, std::string token_text, int token_position) {
		type = token_type;
		text = token_text;
		position = token_position;
	}
};

class tokentype {
	friend class Lexer;
	protected:
	std::vector<std::string> first_keys = { "for",      "while",    "if",     "else",  "break",
											"continue", "print",    "int",    "float", "bool",
											"char",     "string",   "double", "long",  "short",
											"signed",	"unsigned", "++",     "--",    "=",
											"+=",       "-=",       "<",      ">",     "(",
											")",        "{",        "}",      ";",     " ",
											"\n",       "*",        "/",      "+",     "-" };

	std::vector<std::string> second_key_type = { "<FOR>",      "<WHILE>",     "<IF>",        "<ELSE>",	  "<BREAK>",
												"<CONTINUE>", "<PRINT>",     "<INT>",       "<FLOAT>",	  "<BOOL>",
												"<CHAR>",	  "<STRING>",    "<DOUBLE>",	"<VAR_TYPE>",  "<VAR_TYPE>",
												"<VAR_TYPE>",  "<VAR_TYPE>", "<INCREMENT>", "<DECREMENT>", "<OPERATOR>",
												"<OPERATOR>", "<OPERATOR>",  "<LT>",        "<GT>",        "<LB>",
												"<RB>",       "<LCB>",       "<RCB>",       "<SEMICOLON>", "<SPACE>",
												"<NEW_LINE>", "<OPERATOR>",  "<OPERATOR>",  "<OPERATOR>",  "<OPERATOR>" };


	std::vector<std::string> first_regexs = { R"(\/\*(\*(?!\/)|[^*])*\*\/)", R"(//(.+))",
											 R"(\"(.*?)\")",				R"('(.)')",
											 R"([+-]?[0-9]{1,})" };

	std::vector<std::string> first_regexs_type = { "<COMMENT>",  "<COMMENT>",
												  "<STR_LINE>", "<CHAR_SYMBOL>",
												  "<NUMBER>" };


	std::vector<std::string> second_regexs = { R"([a-zA-Z_][a-zA-Z0-9_]*)" };
	std::vector<std::string> second_regexs_type = { "<ID>" };
};
