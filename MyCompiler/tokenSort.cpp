#include <vector>
#include "token.h"

std::vector<token> sortTokenList(std::vector<token> tokenlist) {
	for (int i = 0; i < tokenlist.size(); i++) {
		for (int j = 1; j < tokenlist.size() - i; j++) {
			if (tokenlist[j - 1].position > tokenlist[j].position) {
				token temp = tokenlist[j - 1];
				tokenlist[j - 1] = tokenlist[j];
				tokenlist[j] = temp;
			}
		}
	}
	return tokenlist;
}