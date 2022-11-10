#include "NFA.h"

bool NFA::isAccept(std::string notation) {
	typedef std::pair<int, std::string> tr;
	std::map<std::pair<int, char>, std::set<int> > table;
	std::map<tr, bool> visited;
	std::queue<tr > q;
	std::pair<int, std::string> cur = { init, "" };
	std::sort(transitions.begin(), transitions.end());

	//transition table을 생성합니다.
	for (int i = 0; i < transitions.size(); i++) {
		table[{transitions[i].from, transitions[i].alpha}].insert(transitions[i].to);
	}


	//Accept됨을 확인하기 위해서 BFS 이용
	q.push(cur);
	visited[cur] = true;
	while (!q.empty()) {
		cur = q.front();
		q.pop();

		//만약 final state에 도달했을 때, 만들어진 string이 notation을 만족한다면 true를 반환
		if (cur.second == notation && cur.first == fin) {
			return true;
		}
		//현재 state에서 LAMDA로 연결된 state가 있다면 해당 state를 enqueue합니다.
		for (auto& t : table[{cur.first, LAMDA}]) {
			std::pair<int, std::string> next = { t, cur.second };
			if (visited[next] == false) {
				q.push(next);
				visited[next] = true;
			}
		}
		//다음 문자에 대한 transition이 있다면 해당 state를 enqueue합니다.
		char nextc = notation[cur.second.size()];
		if (nextc) {
			for (auto& t : table[{cur.first, nextc}]) {
				std::pair<int, std::string> next = { t, cur.second + nextc };
				if (visited[next] == false) {
					q.push(next);
					visited[next] = true;
				}
			}
		}
	}
	//BFS 종료 후 accept 되지 않았다면 false 반환
	return false;
}

void NFA::add(int from, int to, char alpha) {
	add(TRANS(from, to, alpha));
}

void NFA::add(TRANS t) {
	transitions.push_back(t);
}

void NFA::append(NFA another) {
	int nextid = 0;
	//다른 NFA의 transition을 현재 NFA의 state status와 고려하여 추가합니다.
	for (int i = 0; i < another.transitions.size(); i++) {
		TRANS t = another.transitions[i];
		t.from += id;
		t.to += id;
		nextid = std::max(nextid, t.to);
		transitions.push_back(t);
	}
	id = nextid;
	fin = id;
}

void NFA::print() {
	std::map<std::pair<int, char>, std::set<int> > table;
	std::set<char> alphabet;
	std::sort(transitions.begin(), transitions.end());
	//transition table을 만듭니다.
	for (int i = 0; i < transitions.size(); i++) {
		table[{transitions[i].from, transitions[i].alpha}].insert(transitions[i].to);
		alphabet.insert(transitions[i].alpha);
	}
	std::cout << "_";
	for (int i = 0; i <= alphabet.size(); i++) {
		std::cout << "________";
	}
	std::cout << std::endl;
	
	std::cout << "Seq\t|" ;
	for (auto c : alphabet) {
		std::cout << (c ? std::string(1, c) : "LAMDA") << "\t|";
	}
	std::cout << std::endl;
	std::cout << "=";
	for (int i = 0; i <= alphabet.size(); i++) {
		std::cout << "========";
	}
	std::cout << std::endl;
	for (int i = 0; i <= id; i++) {
		std::cout << i << "\t|";
		for (auto c : alphabet) {
			for (auto s : table[{i, c}])
				std::cout << s << " ";
			std::cout << "\t|";
		}
		std::cout << '\n';
	}
	std::cout << "-";
	for (int i = 0; i <= alphabet.size(); i++) {
		std::cout << "--------";
	}
	std::cout << std::endl;
}

NFA kleene(NFA Target) {
	NFA res;
	res.add(res.get_init(), res.get_final(), LAMDA);
	Target.add(Target.get_init(), Target.get_id(), LAMDA);
	Target.add(Target.get_id(), Target.get_init(), LAMDA);
	res.append(Target);
	return res;
}

NFA Or(NFA L, NFA R) {
	NFA res;
	int temp;
	res.add(res.get_init(), res.get_final(), LAMDA);
	res.append(L);
	temp = res.get_final();
	res.addState();
	res.add(res.get_init(), res.get_id(), LAMDA);
	res.append(R);
	res.addState();
	res.add(temp, res.get_id(), LAMDA);
	res.add(res.get_final(), res.get_id(), LAMDA);
	return res;
}

NFA Concat(NFA L, NFA R) {
	L.append(R);
	return L;
}

NFA ReToNFA(std::string Re) {
	NFA res;
	NFA l, r;
	std::stack<NFA> st; //연산 중 생기는 NFA들을 저장할 stack
	for (int i = 0; i < Re.size(); i++) {
		//만약 operator가 아니라면 해당 terminal을 accept하는 NFA를 생성한다.
		if (!isOper(Re[i])) {
			NFA newNFA;
			newNFA.add(newNFA.get_init(), newNFA.get_final(), Re[i]);
			st.push(newNFA);
		}
		else {
			//연산자일 경우 연산자의 종류에 따라 아래와 같이 진행한다.
			switch (Re[i]) {
			case CONCATENATE:
				r = st.top(); st.pop();
				l = st.top(); st.pop();
				st.push(Concat(l, r));
				break;
			case OR:
				r = st.top(); st.pop();
				l = st.top(); st.pop();
				st.push(Or(l, r));
				break;
			case CLOSURE:
				l = st.top(); st.pop();
				st.push(kleene(l));
				break;
			}
		}
	}
	//연산의 결과물(st.top())의 시작과 끝에 state를 붙여준다.(안 붙여도 되지만 initial과 final을 확실히 구분하기 위해)
	res.add(res.get_init(), res.get_final(), LAMDA);
	res.append(st.top());
	res.addState();
	res.add(res.get_final(), res.get_id(), LAMDA);
	res.set_final(res.get_id());
	return res;
}

void setPriority() {
	isp[OPENPARENTHESIS] = 0;	icp[OPENPARENTHESIS] = 999;
	isp[CONCATENATE] = 1;		icp[CONCATENATE] = 1;
	isp[OR] = 2;				icp[OR] = 2;
	isp[CLOSURE] = 3;			icp[CLOSURE] = 3;
}

std::string convertInfixToPostfix(std::string infixNotation) {
	std::string postfixNotation;
	std::stack<char> operStack;
	int operandCount = 0;
	int operatorCount = 0;
	setPriority();

	for (int i = 0; i < infixNotation.size(); i++) {
		//만약 terminal(a,b,c, etc.)이라면 바로.
		if (isTerminal(infixNotation[i])) {
			postfixNotation.push_back(infixNotation[i]);
			operandCount++;
		}
		else {
			//닫는 괄호일 때 여는 괄호까지 pop한다.
			if (infixNotation[i] == CLOSEPARENTHESIS) {
				while (operStack.top() != OPENPARENTHESIS) {
					postfixNotation.push_back(operStack.top());
					if (operStack.top() != CLOSURE) operatorCount++;
					operStack.pop();
				}
				operStack.pop();
				continue;
			}
			//top의 우선순위가 넣으려는 연산자보다 클 경우, 작거나 같은 연산자가 나올때까지 pop한다.
			while (!operStack.empty() && (isp[operStack.top()] > icp[infixNotation[i]])) {
				postfixNotation.push_back(operStack.top());
				if (operStack.top() != CLOSURE) operatorCount++;
				operStack.pop();
			}
			operStack.push(infixNotation[i]);
		}
	}
	//stack이 빌때까지 남은 operator들을 빼낸다.
	while (!operStack.empty()) {
		postfixNotation.push_back(operStack.top());
		if (operStack.top() != CLOSURE) operatorCount++;
		operStack.pop();
	}

	//operator와 operator의 개수가 알맞게 되어있지 않다면 INVALIDEXP를 반환한다.
	return (operandCount - operatorCount == 1) ? postfixNotation : INVALIDEXP;
}

std::string removeChar(std::string str, char c) {
	std::string removedstr;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == c)
			continue;
		removedstr.push_back(str[i]);
	}
	return removedstr;
}

std::string addConcatenation(const std::string notation) {
	std::string addNotation;

	addNotation.push_back(notation[0]);
	for (int i = 1; i < notation.size(); i++) {
		//현재 terminal혹은 여는 괄호일 때 바로 이전의 문자가 terminal 이거나 여는괄호, OR 연산자가 아니라면 CONCATENATE를 삽입한다.
		if ((isTerminal(notation[i]) || notation[i] == OPENPARENTHESIS) && isConcate(notation[i - 1])) {
			addNotation.push_back(CONCATENATE);
		}
		addNotation.push_back(notation[i]);
	}
	return addNotation;
}