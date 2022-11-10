#include "NFA.h"

int main() {
	std::string regularNotation = "(a|b)*(abcdef)";
	std::string postfixNotation;
	std::string expression;
	std::cout << "����ǥ����: ";
	postfixNotation = convertInfixToPostfix(addConcatenation(removeChar(regularNotation, BLANK)));
	std::cout << regularNotation<<std::endl;

	NFA res = ReToNFA(postfixNotation);
	res.print();

	while (1) {
		std::cout << "�׽�Ʈ�ϰ� ���� �� �Է��ϼ���. : ";
		std::cin >> expression;
		std::cout << expression <<"\t" << (res.isAccept(expression) ? "Accept!" : "Reject!") << std::endl;
	}

	return 0;
}