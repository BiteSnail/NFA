//#include <iostream>
//#include <string>
//#include <stack>
//#include <vector>
//#include <map>
//#include <set>
//#include <algorithm>
//#include <queue>
//
//#define CONCATENATE '+'
//#define CLOSURE '*'
//#define OR '|'
//#define OPENPARENTHESIS '('
//#define CLOSEPARENTHESIS ')'
//#define BLANK ' '
//#define LAMDA '\0'
//#define ALPHABET char
//
//std::map<char, int> isp;
//std::map<char, int> icp;
//
//
//
//void setPriority() {
//	isp[OPENPARENTHESIS] = 0;	icp[OPENPARENTHESIS] = 999;
//	isp[CONCATENATE] = 1;		icp[CONCATENATE] = 1;
//	isp[OR] = 2;				icp[OR] = 2;
//	isp[CLOSURE] = 3;			icp[CLOSURE] = 3;
//}
//
//inline bool isTerminal(const char oneletter) {
//	return (oneletter >= 'a' && oneletter <= 'z');
//}
//
//inline bool isConcate(const char oneletter) {
//	return isTerminal(oneletter) || (oneletter != OR && oneletter != BLANK && oneletter != OPENPARENTHESIS);
//}
//
//std::string convertInfixToPostfix(std::string infixNotation) {
//	std::string postfixNotation;
//	std::stack<char> operStack;
//	int operandCount = 0;
//	int operatorCount = 0;
//
//	for (int i = 0; i < infixNotation.size(); i++) {
//		if (isTerminal(infixNotation[i])) {
//			postfixNotation.push_back(infixNotation[i]);
//			operandCount++;
//		}
//		else {
//			if (infixNotation[i] == CLOSEPARENTHESIS) {
//				while (operStack.top() != OPENPARENTHESIS) {
//					postfixNotation.push_back(operStack.top());
//					if (operStack.top() != CLOSURE) operatorCount++;
//					operStack.pop();
//				}
//				operStack.pop();
//				continue;
//			}
//			while (!operStack.empty() && (isp[operStack.top()] > icp[infixNotation[i]])) {
//				postfixNotation.push_back(operStack.top());
//				if (operStack.top() != CLOSURE) operatorCount++;
//				operStack.pop();
//			}
//			operStack.push(infixNotation[i]);
//		}
//	}
//
//	while (!operStack.empty()) {
//		postfixNotation.push_back(operStack.top());
//		if (operStack.top() != CLOSURE) operatorCount++;
//		operStack.pop();
//	}
//
//	return (operandCount - operatorCount == 1) ? postfixNotation : "Invalid Notation";
//}
//
//std::string removeChar(std::string str, char c) {
//	std::string removedstr;
//	for (int i = 0; i < str.size(); i++) {
//		if (str[i] == c)
//			continue;
//		removedstr.push_back(str[i]);
//	}
//	return removedstr;
//}
//
//std::string addConcatenation(const std::string notation) {
//	std::string addNotation;
//
//	addNotation.push_back(notation[0]);
//	for (int i = 1; i < notation.size(); i++) {
//		if ((isTerminal(notation[i]) || notation[i] == OPENPARENTHESIS) && isConcate(notation[i - 1])) {
//			addNotation.push_back(CONCATENATE);
//		}
//		addNotation.push_back(notation[i]);
//	}
//	return addNotation;
//}
//
//typedef struct _TRANSITION {
//	int from;
//	int to;
//	char alpha;
//	struct _TRANSITION(int _from, int _to, char _alpha) :
//		from(_from),
//		to(_to),
//		alpha(_alpha) {}
//	bool operator==(const struct _TRANSITION& ot) {
//		return to == ot.to && alpha == ot.alpha;
//	}
//	bool operator>(const struct _TRANSITION& ot) {
//		return from == ot.from ? to == ot.to ? alpha > ot.alpha : to > ot.to : from > ot.from;
//	}
//	bool operator<(const struct _TRANSITION& ot) {
//		return from == ot.from ? to == ot.to ? alpha < ot.alpha : to < ot.to : from < ot.from;
//	}
//}TRANS;
//
////class _TRANS {
////public:
////	int to;
////	char alpha;
////	_TRANS(int _to, char _alpha) :
////		to(_to),
////		alpha(_alpha) {}
////	bool operator==(_TRANS& ot) const {
////		return to == ot.to && alpha == ot.alpha;
////	}
////	bool operator>(_TRANS& ot) const {
////		return to == ot.to ? alpha > ot.alpha : to > ot.to;
////	}
////	bool operator<(_TRANS& ot) const {
////		return to == ot.to ? alpha < ot.alpha : to < ot.to;
////	}
////};
////
////class STATE {
////public:
////	int id;
////	std::set<_TRANS> transitions;
////	STATE(int _id = 0) {
////		id = _id;
////	}
////	STATE(const STATE& ot) {
////		id = ot.id;
////		transitions = ot.transitions;
////	}
////	bool operator==(const STATE& ot) const {
////		return id == ot.id;
////	}
////	bool operator>(const STATE& ot) const {
////		return id > ot.id;
////	}
////	bool operator<(const STATE& ot) const {
////		return id < ot.id;
////	}
////};
////
////class _NFA {
////public:
////	std::set<ALPHABET> alphabet;
////	std::set<STATE> states;
////	STATE initialState;
////	std::set<STATE> finalState;
////	_NFA();
////	_NFA(const _NFA& ot) {
////		alphabet = ot.alphabet;
////		states = ot.states;
////		initialState = ot.initialState;
////		finalState = ot.finalState;
////	}
////	_NFA(ALPHABET alpha) {
////		add(0, 1, alpha);
////		initialState = *(states.find(STATE(0)));
////		finalState.insert(*(states.find(STATE(1))));
////	}
////	void add(int init, int fin, ALPHABET alpha) {
////		alphabet.insert(alpha);
////		if (states.find(STATE(fin)) == states.end()) {
////			states.insert(STATE(fin));
////		}
////		if (states.find(STATE(init)) != states.end()) {
////			STATE s = *states.find(STATE(init));
////			s.transitions.insert(_TRANS(fin, alpha));
////			states.erase(STATE(init));
////			states.insert(s);
////		}
////		else {
////			STATE s(init);
////			s.transitions.insert(_TRANS(fin, alpha));
////			states.insert(s);
////		}
////	}
////	_NFA operator+(const _NFA& ot) {
////		int id = states.end()->id;
////		for (auto& s : ot.alphabet) {
////			alphabet.insert(s);
////		}
////		for (auto& s : ot.states) {
////			for (auto& t : s.transitions)
////				add(s.id + id, t.to + id, t.alpha);
////		}
////		finalState.clear();
////		finalState.insert((*states.end()));
////		return *this;
////	}
////	_NFA closure() {
////		add(states.begin()->id, states.end()->id, LAMDA);
////		add(states.end()->id, states.begin()->id, LAMDA);
////		return *this;
////	}
////	_NFA operator|(const _NFA& ot) {
////		int id = states.end()->id;
////		for (auto& s : ot.alphabet) {
////			alphabet.insert(s);
////		}
////		for (auto& s : ot.states) {
////			for (auto& t : s.transitions)
////				add(s.id + s.id ? id : 0, t.to ==ot.states.end()->id ? 0 : t.to  + id, t.alpha);
////		}
////		return *this;
////	}
////	void print() {
////		for (auto& s : states) {
////			std::cout << s.id << ": ";
////			for (auto& k : s.transitions) {
////				std::cout << "(" << k.to << ", " << k.alpha << ")";
////			}
////			std::cout << std::endl;
////		}
////	}
////};
////
////
////_NFA ReToNFAA(std::string Re) {
////	_NFA res;
////	_NFA l, r;
////	std::stack<_NFA> st;
////	for (int i = 0; i < Re.size(); i++) {
////		if (!isOper(Re[i])) {
////			_NFA newNFA(Re[i]);
////			st.push(newNFA);
////		}
////		else {
////			switch (Re[i]) {
////			case CONCATENATE:
////				r = st.top(); st.pop();
////				l = st.top(); st.pop();
////				st.push(l + r);
////				break;
////			case OR:
////				r = st.top(); st.pop();
////				l = st.top(); st.pop();
////				st.push(l | r);
////				break;
////			case CLOSURE:
////				l = st.top(); st.pop();
////				st.push(l.closure());
////				break;
////			}
////		}
////	}
////	return res;
////}
//
//class NFA {
//	std::vector<TRANS> transitions;
//	int init;
//	int fin;
//	int id;
//public:
//	NFA() {
//		init = 0;
//		fin = 1;
//		id = 1;
//	}
//	NFA(int _init, int _fin) :
//		init(_init),
//		fin(_fin),
//		id(_fin) {}
//	NFA(const NFA& ot) :
//		init(ot.init),
//		fin(ot.fin),
//		id(ot.id),
//		transitions(ot.transitions) {}
//	void add(int from, int to, char alpha);
//	void add(TRANS t);
//	void append(NFA another);
//	TRANS newTrans(int from, int to, char alpha);
//	void print();
//	int get_init() { return init; }
//	int get_final() { return fin; }
//	int get_id() { return id; }
//	void set_final(int _id) { fin = _id; }
//	void addState() { id++; }
//	bool isAccept(std::string notation) {
//		std::map<std::pair<int, char>, std::set<int> > table;
//		std::map<std::pair<int, std::string>, bool> visited;
//		std::queue<std::pair<int, std::string> > q;
//		std::pair<int, std::string> cur = { init, "" };
//		std::sort(transitions.begin(), transitions.end());
//
//		for (int i = 0; i < transitions.size(); i++) {
//			table[{transitions[i].from, transitions[i].alpha}].insert(transitions[i].to);
//		}
//		q.push(cur);
//		visited[cur] = true;
//		while (!q.empty()) {
//			cur = q.front();
//			q.pop();
//
//			if (cur.second == notation && cur.first == fin) {
//				return true;
//			}
//			for (auto& t : table[{cur.first, LAMDA}]) {
//				std::pair<int, std::string> next = { t, cur.second };
//				if (visited[next] == false) {
//					q.push(next);
//					visited[next] = true;
//				}
//			}
//			char nextc = notation[cur.second.size()];
//			if (nextc) {
//				for (auto& t : table[{cur.first, nextc}]) {
//					std::pair<int, std::string> next = { t, cur.second + nextc };
//					if (visited[next] == false) {
//						q.push(next);
//						visited[next] = true;
//					}
//				}
//			}
//		}
//		return false;
//	}
//};
//
//TRANS NFA::newTrans(int from, int to, char alpha) {
//	return TRANS(from, to, alpha);
//}
//
//void NFA::add(int from, int to, char alpha) {
//	add(TRANS(from, to, alpha));
//}
//
//void NFA::add(TRANS t) {
//	transitions.push_back(t);
//}
//
//void NFA::append(NFA another) {
//	int nextid = 0;
//	for (int i = 0; i < another.transitions.size(); i++) {
//		TRANS t = another.transitions[i];
//		t.from += id;
//		t.to += id;
//		nextid = std::max(nextid, t.to);
//		transitions.push_back(t);
//	}
//	id = nextid;
//	fin = id;
//}
//
//void NFA::print() {
//	std::map<std::pair<int, char>, std::set<int> > table;
//	std::sort(transitions.begin(), transitions.end());
//
//	for (int i = 0; i < transitions.size(); i++) {
//		table[{transitions[i].from, transitions[i].alpha}].insert(transitions[i].to);
//	}
//
//	std::cout << "Seq" << '\t' << "a" << '\t' << "b" << '\t' << "LAMDA" << std::endl;
//	for (int i = 0; i <= id; i++) {
//		std::cout << i << '\t';
//		for (auto s : table[{i, 'a'}])
//			std::cout << s << " ";
//		std::cout << '\t';
//		for (auto s : table[{i, 'b'}])
//			std::cout << s << " ";
//		std::cout << '\t';
//		for (auto s : table[{i, '\0'}])
//			std::cout << s << " ";
//		std::cout << '\n';
//	}
//
//}
//
//bool isOper(char c) {
//	return c == CLOSURE || c == CONCATENATE || c == OR || c == OPENPARENTHESIS;
//}
//
//NFA kleene(NFA Target) {
//	Target.add(Target.get_init(), Target.get_final(), LAMDA);
//	Target.add(Target.get_final(), Target.get_init(), LAMDA);
//	return Target;
//}
//
//NFA Or(NFA L, NFA R) {
//	NFA res;
//	int temp;
//	res.add(res.get_init(), res.get_final(), LAMDA);
//	res.append(L);
//	temp = res.get_final();
//	res.addState();
//	res.add(res.get_init(), res.get_id(), LAMDA);
//	res.append(R);
//	res.addState();
//	res.add(temp, res.get_id(), LAMDA);
//	res.add(res.get_final(), res.get_id(), LAMDA);
//	return res;
//}
//
//NFA Concat(NFA L, NFA R) {
//	L.append(R);
//	return L;
//}
//
//NFA ReToNFA(std::string Re) {
//	NFA res;
//	NFA l, r;
//	std::stack<NFA> st;
//	for (int i = 0; i < Re.size(); i++) {
//		if (!isOper(Re[i])) {
//			NFA newNFA;
//			newNFA.add(newNFA.get_init(), newNFA.get_final(), Re[i]);
//			st.push(newNFA);
//		}
//		else {
//			switch (Re[i]) {
//			case CONCATENATE:
//				r = st.top(); st.pop();
//				l = st.top(); st.pop();
//				st.push(Concat(l, r));
//				break;
//			case OR:
//				r = st.top(); st.pop();
//				l = st.top(); st.pop();
//				st.push(Or(l, r));
//				break;
//			case CLOSURE:
//				l = st.top(); st.pop();
//				st.push(kleene(l));
//				break;
//			}
//		}
//	}
//	res.add(res.get_init(), res.get_final(), LAMDA);
//	res.append(st.top());
//	res.addState();
//	res.add(res.get_final(), res.get_id(), LAMDA);
//	res.set_final(res.get_id());
//	return res;
//}
//
//
//int main() {
//	std::string regularNotation = "(ab)*|b*";
//	std::string postfixNotation;
//	std::string expression;
//
//	setPriority();
//	std::cout << "정규언어를 입력하세요: ";
//	//std::cin >> regularNotation;
//	//std::cout << addConcatenation(removeChar(regularNotation, BLANK)) << std::endl;
//	postfixNotation = convertInfixToPostfix(addConcatenation(removeChar(regularNotation, BLANK)));
//	std::cout << postfixNotation << std::endl;
//
//	NFA res = ReToNFA(postfixNotation);
//	//_NFA res2 = ReToNFAA(postfixNotation);
//
//	res.print();
//
//	while (1) {
//		std::cout << "테스트하고 싶은 언어를 입력하세요. : ";
//		std::cin >> expression;
//		std::cout << expression << "\t" << (res.isAccept(expression) ? "Accept!" : "Reject!") << std::endl;
//	}
//	//res2.print();
//
//	return 0;
//}