#include <string.h>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <regex>
#include <unordered_map>
#include "find.h"
#include "token.h"

class Lexer {
	public:
		Lexer(std::string new_line) {
			line = new_line;
		}

		std::vector<token> creat_tokelist() {
			reg_refactor(1);
			key_refactor();
			reg_refactor(2);

			return tokenlist;
		}

		void show_line() {
			for (int i = 0; i < line.size(); i++) {
				std::cout << line[i];
			}
			std::cout << std::endl;
		}

	private:
		std::string line;
		std::vector<token> tokenlist;
		tokentype mytokentype = tokentype();

		void key_refactor() {
			for (int i = 0; i < mytokentype.first_keys.size(); i++) {
				std::string key = mytokentype.first_keys[i];
				std::string key_type = mytokentype.second_key_type[i];

				int key_length = key.length();


				while (find(line, key).is_find) {
					int place = find(line, key).index;

					token newtoken(key_type, key, place);
					tokenlist.push_back(newtoken);

					for (int i = place; i < place + key_length; i++) {
						line.replace(i, 1, "@");
					}
				}
			}
		}

		void reg_refactor(int priority) {
			std::string key;
			std::cmatch result;
			std::string regexp;
			std::string key_type;

			int number_of_regexp = 0;

			if (priority == 1) {
				number_of_regexp = mytokentype.first_regexs.size();
			}
			else if (priority == 2) {
				number_of_regexp = mytokentype.second_regexs.size();
			}

			for (int i = 0; i < number_of_regexp; i++) {
				if (priority == 1) {
					regexp = mytokentype.first_regexs[i];
					key_type = mytokentype.first_regexs_type[i];
				}
				else if (priority == 2) {
					regexp = mytokentype.second_regexs[i];
					key_type = mytokentype.second_regexs_type[i];
				}

				std::regex regular(regexp);

				while (std::regex_search(line.c_str(), result, regular)) {
					key = result[0];

					int key_length = key.length();

					while (find(line, key).is_find) {
						int place = find(line, key).index;

						token newtoken(key_type, key, line.find(key));
						tokenlist.push_back(newtoken);

						for (int i = place; i < place + key_length; i++) {
							line.replace(i, 1, "@");
						}
					}
				}
			}
		}
};

