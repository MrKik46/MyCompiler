#include <iostream>
#include <string.h>

class find {
public:
	int index = 0;
	bool is_find = false;


	find(std::string line, std::string subline) {
		bool end = false;

		if (subline.size() <= line.size()) {
			for (int i = 0; i < (line.size() - subline.size() + 1) and !end; i++) {
				if (line[i] == subline[0]) {
					index = i;
					is_find = true;

					for (int j = 0; j < subline.size(); j++) {
						if (line[i + j] != subline[j]) {
							is_find = false;
							index = 0;
						}
					}
					if (is_find and subline != " " and subline != "\n" and subline != "\t" and subline != "("
						and subline != ")" and subline != "{" and subline != "}" and subline != "="
						and subline != ">" and subline != "<" and subline != "+" and subline != "-"
						and subline != "++" and subline != "--" and subline != ";"
						and subline != "+=" and subline != "-=") {

						if (i > 0) {
							if ((int(line[i - 1]) > 96 and int(line[i - 1]) < 123) or
								(int(line[i - 1]) > 64 and int(line[i - 1]) < 91) or
								(int(line[i - 1]) > 47 and int(line[i - 1]) < 58) or
								(line[i - 1] == '_')) {
								is_find = false;
								index = 0;
							}
						}
						if ((int(line[index + subline.size()]) > 96 and int(line[index + subline.size()]) < 123) or
							(int(line[index + subline.size()]) > 64 and int(line[index + subline.size()]) < 91) or
							(int(line[index + subline.size()]) > 47 and int(line[index + subline.size()]) < 58) or
							(line[index + subline.size()] == '_')) {
							is_find = false;
							index = 0;
						}
					}

					if (is_find) end = is_find;
				}
			}
		}
	}
};