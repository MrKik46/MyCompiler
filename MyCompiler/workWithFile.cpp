#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <iostream>
#include <vector>
#include "error.h"

class WorkWithFile {
private:
	std::string line;

public:
	std::string get_lines() {
		char letter;
		FILE* file = fopen("myCode.txt", "r");

		if (file) {
			while ((letter = fgetc(file)) != EOF) {
				line.push_back(letter);
			}

			fclose(file);
		}
		else {
			std::cout << "File is corrupted" << std::endl;
		}

		return line;
	}

	void log_errors(std::vector<Error> errorlist) {
		std::ofstream file("result.txt");

		if (errorlist.size() == 0) {
			file << "Continue is used correctly!";
		}
		else {
			for (int i = 0; i < errorlist.size(); i++) {
				file << errorlist[i].line << "> Error " << errorlist[i].type << ": " << errorlist[i].info << " " << std::endl;
			}
		}

		file.close();
	}

	void show() {
		for (int i = 0; i < line.size(); i++) {
			std::cout << line[i];
		}
		std::cout << std::endl << std::endl;
	}
};