#include <iostream>
#include <string.h>
#include <vector>

class Error {
	public:
		std::string type;
		std::string info;
		int line;
		int token_position;

		Error(std::string error_type, std::string error_info, int error_line, int uncorrect_token_position) {
			type = error_type;
			info = error_info;
			line = error_line;
			token_position = uncorrect_token_position;
		}
};