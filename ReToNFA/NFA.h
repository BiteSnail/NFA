//Regular Expression에서 NFA로 변환하기 위한 함수들입니다.
//Regular Expression이 std::string으로 주어졌을 때
//1. 공백이 포함되어 있을 수 있다면 removeChar(std::string, char)로 먼저 공백을 제거합니다.
//2. concatenate가 생략되어 있다면 addConcatenation(std::string)으로 제 위치에 concate기호를 추가해줍니다.
//3. convertInfixToPostfix(std::string)으로 Infix형식의 Regular Expression을 Postfix로 변환합니다.
//
//Postfix 형식의 regular expression을 ReToNFA(std::string)을 이용하여 class NFA로 변환합니다.
//1. print()는 변환된 NFA의 transition table을 확인합니다.
//2. isAccept(std::string)는 주어진 language가 NFA에서 accept되는지 확인합니다.
#pragma once
#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <queue>
#include "stafx.h"

//후위식 변환을 위한 in-stack-priority, in-comming-prioirtiy
static std::map<char, int> isp;
static std::map<char, int> icp;

typedef struct _TRANSITION {
	int from;
	int to;
	char alpha;
	struct _TRANSITION(int _from, int _to, char _alpha) :
		from(_from),
		to(_to),
		alpha(_alpha) {}
	bool operator==(const struct _TRANSITION& ot) {
		return to == ot.to && alpha == ot.alpha;
	}
	bool operator>(const struct _TRANSITION& ot) {
		return from == ot.from ? to == ot.to ? alpha > ot.alpha : to > ot.to : from > ot.from;
	}
	bool operator<(const struct _TRANSITION& ot) {
		return from == ot.from ? to == ot.to ? alpha < ot.alpha : to < ot.to : from < ot.from;
	}
}TRANS;

class NFA {
	std::vector<TRANS> transitions;
	//initial state, final state, new state index
	int init;
	int fin;
	int id;
public:
	NFA() {
		init = 0;
		fin = 1;
		id = 1;
	}
	NFA(int _init, int _fin) :
		init(_init),
		fin(_fin),
		id(_fin) {}
	NFA(const NFA& ot) :
		init(ot.init),
		fin(ot.fin),
		id(ot.id),
		transitions(ot.transitions) {}
	//NFA에 transition을 추가합니다.
	void add(int from, int to, char alpha);
	void add(TRANS t);
	//다른 NFA의 모든 transitions을 추가합니다.
	void append(NFA another);
	//NFA의 transition Table을 출력합니다.
	void print();
	int get_init() { return init; }
	int get_final() { return fin; }
	int get_id() { return id; }
	void set_final(int _id) { fin = _id; }
	void addState() { id++; }
	//notation이 NFA에 accept되는지 확인합니다.
	bool isAccept(std::string notation);
};

//ISP, ICP에 priority를 지정합니다.
void setPriority();

inline bool isTerminal(const char oneletter) {
	return (oneletter >= 'a' && oneletter <= 'z');
}

inline bool isConcate(const char oneletter) {
	return isTerminal(oneletter) || (oneletter != OR && oneletter != BLANK && oneletter != OPENPARENTHESIS);
}

inline bool isOper(char c) {
	return c == CLOSURE || c == CONCATENATE || c == OR || c == OPENPARENTHESIS;
}

std::string convertInfixToPostfix(std::string infixNotation);
//str에서 c를 모두 제거하여 반환합니다.
std::string removeChar(std::string str, char c);
//notation에 concate기호를 추가합니다.
std::string addConcatenation(const std::string notation);

//Target NFA에 kleene clousre를 추가합니다.
NFA kleene(NFA Target);
//L, R NFA를 OR합니다.
NFA Or(NFA L, NFA R);
//L, R NFA를 Concatenate합니다
NFA Concat(NFA L, NFA R);
NFA ReToNFA(std::string Re);