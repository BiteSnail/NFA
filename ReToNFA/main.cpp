#include "NFA.h"

int main() {
	std::string regularNotation = "(a|b)*(abcdef)";
	std::string postfixNotation;
	std::string expression;
	std::cout << "정규표현식: ";
	postfixNotation = convertInfixToPostfix(addConcatenation(removeChar(regularNotation, BLANK)));
	std::cout << regularNotation<<std::endl;

	NFA res = ReToNFA(postfixNotation);
	res.print();

	while (1) {
		std::cout << "테스트하고 싶은 언어를 입력하세요. : ";
		std::cin >> expression;
		std::cout << expression <<"\t" << (res.isAccept(expression) ? "Accept!" : "Reject!") << std::endl;
	}

	return 0;
}