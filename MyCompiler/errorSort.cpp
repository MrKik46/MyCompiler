#include <vector>
#include "error.h"

std::vector<Error> sortErrorList(std::vector<Error> errorlist) {
	for (int i = 0; i < errorlist.size(); i++) {
		for (int j = 1; j < errorlist.size() - i; j++) {
			if (errorlist[j - 1].token_position > errorlist[j].token_position) {
				Error temp = errorlist[j - 1];
				errorlist[j - 1] = errorlist[j];
				errorlist[j] = temp;
			}
		}
	}
	return errorlist;
}