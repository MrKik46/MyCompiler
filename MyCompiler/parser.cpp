#include "token.h"
#include "error.h"

class Parser {
	public:
		Parser(std::vector<token> tokenlist) {
			mytokenlist = tokenlist;
			tokenListLength = mytokenlist.size();
		}

		std::vector<Error> creat_errorlist() {
			find_curlic_brackets_borders();
			find_cycle_block_borders();
			find_condition_borders();

			semicolon_check();
			correct_token_befor_continue();
			continue_in_cycle();
			continue_not_in_condition();

			return errorlist;
		}

	private:
		std::vector<Error> errorlist;
		std::vector<token> mytokenlist;
		
		std::vector<int> curlic_brackets_borders;
		std::vector<int> cycle_block_borders;
		std::vector<int> condition_borders;

		int tokenListLength;
		bool all_checks_passed = true;

		void find_cycle_block_borders() {
			cycle_block_borders.clear();
			for (int i = 0; i < tokenListLength; i++) {
				if (mytokenlist[i].type == "<FOR>" or mytokenlist[i].type == "<WHILE>" ) {
					bool first_cr_br_passed = false;
					int cr_br_start = 0; 
					int cr_br_end = 0; 
					int cr_br_counter = 0;

					for (int j = i + 1; j < tokenListLength; j++) {
						if (mytokenlist[j].type == "<LCB>") {
							if (!first_cr_br_passed) {
								cr_br_start = j;
								first_cr_br_passed = true;
							}

							cr_br_counter++; 
						}

						if (mytokenlist[j].type == "<RCB>") {
							cr_br_counter--; 
							
							if (cr_br_counter == 0 and first_cr_br_passed) {
								cr_br_end = j;
							
								cycle_block_borders.push_back(cr_br_start);
								cycle_block_borders.push_back(cr_br_end);

								break;
							}
						}
					}
				}
			}
		}

		void find_condition_borders() {
			condition_borders.clear();
			for (int i = 0; i < tokenListLength; i++) {
				if (mytokenlist[i].type == "<FOR>" or mytokenlist[i].type == "<WHILE>" 
					or mytokenlist[i].type == "<IF>" or mytokenlist[i].type == "<ID>") {
					bool first_st_br_passed = false;
					int st_br_start = 0;
					int st_br_end = 0;
					int st_br_counter = 0;

					for (int j = i + 1; j < tokenListLength; j++) {
						if (mytokenlist[j].type == "<LB>") {
							if (!first_st_br_passed) {
								st_br_start = j;
								first_st_br_passed = true;
							}

							st_br_counter++;
						}

						if (mytokenlist[j].type == "<RB>") {
							st_br_counter--;

							if (st_br_counter == 0 and first_st_br_passed) {
								st_br_end = j;

								condition_borders.push_back(st_br_start);
								condition_borders.push_back(st_br_end);
								
								break;
							}
						}
					}
				}
			}
		}

		void find_curlic_brackets_borders() {
			curlic_brackets_borders.clear();
			for (int i = 0; i < tokenListLength; i++) {
				if (mytokenlist[i].type == "<FOR>" or mytokenlist[i].type == "<WHILE>" 
					or mytokenlist[i].type == "<IF>" or mytokenlist[i].type == "<ID>") {
					bool first_cr_br_passed = false;
					int cr_br_start = 0;
					int cr_br_end = 0;
					int cr_br_counter = 0;

					for (int j = i + 1; j < tokenListLength; j++) {
						if (mytokenlist[j].type == "<LCB>") {
							if (!first_cr_br_passed) {
								cr_br_start = j;
								first_cr_br_passed = true;
							}

							cr_br_counter++;
						}

						if (mytokenlist[j].type == "<RCB>") {
							cr_br_counter--;

							if (cr_br_counter == 0 and first_cr_br_passed) {
								cr_br_end = j;

								curlic_brackets_borders.push_back(cr_br_start);
								curlic_brackets_borders.push_back(cr_br_end);

								break;
							}
						}
					}
				}
			}
		}

		void semicolon_check() {
			int line = 1;
			for (int token_index = 0; token_index < tokenListLength - 1; token_index++) {
				if (mytokenlist[token_index].type == "<NEW_LINE>") {
					line++;
				}
				if (mytokenlist[token_index].type == "<CONTINUE>") {
					for (int j = 1; j < tokenListLength - 1 - token_index; j++){
						if (mytokenlist[token_index + j].type == "<SEMICOLON>") { 
							break;
						}
						else if (mytokenlist[token_index + j].type != "<SEMICOLON>" and mytokenlist[token_index + j].type != "<SPACE>" 
							and mytokenlist[token_index + j].type != "<NEW_LINE>") {
							Error new_error = Error("E1", R"(Нет ";" после continue.)", line, token_index);
							errorlist.push_back(new_error);
							break;
						}
					}
				}
			}
		}

		void correct_token_befor_continue() {
			std::vector<int> block_to_check;

			int line = 1;
			int block_start = 0;
			int block_end = tokenListLength;

			for (int token_index = 0; token_index < tokenListLength; token_index++) {
				int block_size = -1;
				if (mytokenlist[token_index].type == "<NEW_LINE>") {line++;}
				if (mytokenlist[token_index].type == "<CONTINUE>") {
					for (int index = 0; index < curlic_brackets_borders.size() - 1; index += 2) {
						if (curlic_brackets_borders[index] < token_index and token_index < curlic_brackets_borders[index + 1]) {
							int block_size_temp = curlic_brackets_borders[index + 1] - curlic_brackets_borders[index];
							if (block_size == -1 or block_size > block_size_temp) {
								block_size = block_size_temp;
								block_start = curlic_brackets_borders[index];
								block_end = curlic_brackets_borders[index + 1];
								
							}
						}
					}

					block_to_check.push_back(block_start);
					block_to_check.push_back(block_end);
					block_to_check.push_back(line);
					block_to_check.push_back(token_index);
				}
			}
			
			for (int i = 0; i < block_to_check.size(); i += 4) {
				line = block_to_check[i + 2];
				for (int j = block_to_check[i + 3] - 1; j > block_to_check[i]; j--) {
					if (mytokenlist[j].type == "<NEW_LINE>") {
						line--;
					}
					else if (mytokenlist[j].type != "<SPACE>" and mytokenlist[j].type != "<NEW_LINE>" and mytokenlist[j].type != "<LCB>"
						and mytokenlist[j].type != "<RCB>" and mytokenlist[j].type != "<SEMICOLON>" and mytokenlist[j].type != "<RB>"
						and mytokenlist[j].type != "<LB>") {
						Error new_error = Error("E2", "Перед continue стоит неверный символ.", line, j);
						errorlist.push_back(new_error);
						break;
					}

					if (mytokenlist[j].type == "<SEMICOLON>") {
						break;
					}
				}
			}
		}

		void continue_in_cycle() {
			int line = 1;

			for (int i = 0; i < tokenListLength; i++) {
				if(mytokenlist[i].type == "<NEW_LINE>") { line++; }
				if (mytokenlist[i].type == "<CONTINUE>") {
					bool curr_continue_in_cycle = false;
					for (int j = 0; j < cycle_block_borders.size(); j += 2) {
						if (cycle_block_borders[j] < i and i < cycle_block_borders[j + 1]) {
							curr_continue_in_cycle = true;
							break;
						}
					}

					if (!curr_continue_in_cycle) {
						Error new_error = Error("E3", "Continue используется вне тела цикла.", line, i);
						errorlist.push_back(new_error);
					}
				}
			}
		}

		void continue_not_in_condition() {
			int line = 1;

			for (int i = 0; i < tokenListLength; i++) {
				if (mytokenlist[i].type == "<NEW_LINE>") { line++; }
				if (mytokenlist[i].type == "<CONTINUE>") {
					bool curr_continue_in_condition = false;
					for (int j = 0; j < condition_borders.size(); j += 2) {
						if (condition_borders[j] < i and i < condition_borders[j + 1]) {
							curr_continue_in_condition = true;
							break;
						}
					}

					if (curr_continue_in_condition) {
						Error new_error = Error("E4", "Continue в теле условия.", line, i);
						errorlist.push_back(new_error);
					}
				}
			}
		}

};