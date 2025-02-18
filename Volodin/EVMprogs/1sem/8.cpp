#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <stack>
#include <vector>
using namespace std;

vector <string> boper = {"!=", "==", "<=", ">=", ">", "<", "+", "-", "*", "/", "&&", "||", "&", "|", "="};
vector <string> uoper = { "!", "-", "~" };

int isoper(const string& s, const vector <string>& oper) {
	for (int i = 0; i < oper.size(); i++)
		if (s.find(oper[i]) == 0)
			return oper[i].length();
	return 0;
}

string wrongSymb(const string& tmps, string& s, string eror = "Wrong symbol") {
	return  eror + " #" + to_string(tmps.rfind(s)) + "\nThe end is:\n" + s;
}

int getNumber(string s) {
	int i = 0;
	while (i < s.length() && isdigit(s[i]))
		i++;
	return i;
}
int getSymb(string s) {
	return s[0] == '\'' && s[2] == '\'' ? 3 : 0;
}
int getVariable(string s) {
	int i = 0;
	while (isdigit(s[i]) || isalnum(s[i]) || s[i] == '_')
		i++;
	return i;
}

string compile(string s) {
	if (s.find('{') == string::npos)
		return "You have no '{' symbol"; 
	if (s.find_first_not_of(" \t\n") == string::npos)
		return "The code is empty";
	const string tmps = s.substr(0);
	s = s.substr(s.find_first_not_of(" \t\n"));
	if (s.substr(0, 2) != "if")
		return "Keyword \"if\" is not first";
	s = s.substr(2);
	stack <int> st;
	bool state; // 0 - after bop, uop, (; 1 - after ), var
	bool firstBracketWas = false;
	while (!s.empty()) {
		s = s.substr(s.find_first_not_of(" \t\n"));
		if (s[0] == '(') {
			if (!firstBracketWas || !state) {
				s = s.substr(1);
				st.push('(');
			}
			else
				return wrongSymb(tmps, s);
			state = 0;
			firstBracketWas = true;
		}
		else {
			if (!firstBracketWas)
				return "There are no main brackets";
			if (s[0] == '{')
				break;
			if (s[0] == ')') {
				if (state) {
					if (!st.empty()) {
						st.pop();
						s = s.substr(1);
					}
					else
						return wrongSymb(tmps, s, "Too much closing brackets");
				}
				else
					return wrongSymb(tmps, s);
				state = 1;
			}
			else if (isdigit(s[0])) {
				if (!state) {
					int t = getNumber(s);
					if (t != 0)
						s = s.substr(t);
					else
						return wrongSymb(tmps, s, "Wrong value");
				}
				else
					return wrongSymb(tmps, s);
				state = 1;
			}
			else if (isalnum(s[0]) || s[0] == '_') {
				if (!state) {
					int t = getVariable(s);
					if (t != 0)
						s = s.substr(t);
					else
						return wrongSymb(tmps, s, "Wrong variable name");
				}
				else
					return wrongSymb(tmps, s);
				state = 1;
			}
			else if (s[0] == '\'') {
				if (!state) {
					int t = getSymb(s);
					if (t != 0)
						s = s.substr(t);
					else
						return wrongSymb(tmps, s, "Wrong value");
				}
				else
					return wrongSymb(tmps, s);
				state = 1;
			}
			else {
				int t = isoper(s, boper);
				if (t) {
					if (state) {
						s = s.substr(t);
					}
					else
						return wrongSymb(tmps, s, "No place for binary operator");
					state = 0;
				}
				else {
					t = isoper(s, uoper);
					if (t) {
						if (!state) {
							s = s.substr(t);
						}
						else
							return wrongSymb(tmps, s, "No place for unary operator");
						state = 0;
					}
					else
						return wrongSymb(tmps, s, "You can not use this symbol");
				}				
			}
		}
	}
	if (!st.empty())
		return "You have more open brackets than you need";
	if (s[0] == '{') {
		int bal = 0;
		for (int i = 0; i < s.length(); i++) {
			if (s[i] == '{')
				bal++;
			if (s[i] == '}')
				bal--;
			if (bal < 0)
				return "You are no good with \"{}\" brackets";
		}
		if (bal != 0)
			return "You are no good with \"{}\" brackets";
		int t = s.find_last_of('}');
		if (t + 1 == s.length())
			s = "";
		t = s.find_first_not_of(" \t\n");
		if (t != string::npos)
			return "You have something after \"{}\" brackets";
	}
	return "Your code may be right";
}

int main() {
	ifstream f;
	f.open("inputcheckercompilingif.txt");
	string pred = "start";
	string t = "";
	string s;
	while (getline(f, s)) {
		if (s.substr(0, 3) == "%%%") {
			if (t != "") {
				cout << pred << '\n';
				cout << compile(t) << endl;
				t = "";
			}
			pred = s.substr(3);
		}
		else
			t += s;	
	}
	cout << pred << '\n';
	cout << compile(t) << endl;
	f.close();
}