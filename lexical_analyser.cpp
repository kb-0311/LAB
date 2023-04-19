#include <iostream>
#include <vector>
#include <string>
#include <chrono>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
using namespace std;
// using namespace __gnu_pbds;
using namespace chrono;
typedef long long int ll;
bool isPunctuator(char ch) {
	string cha = " +-*/,;><=()[]{}&|";
	for (auto it : cha) {
		if (it == ch) {
			return true;
		}
	}
	return false;
}

bool valididentifer(string sub) {
	string temp = "0123456789";
	for (auto it : temp) {
		if (it == sub[0]) return false;
	}
	if (isPunctuator(sub[0])) return false;
	return true;
}

bool iskeyword(string sub) {
	vector<string> v = {"if", "else", "while", "break", "do", "continue", "int", "double", "float", "return", "char", "case", "sizeof", "long", "short", "typedef", "switch", "unsigned", "static", "goto", "struct", "void"};
	for (auto it : v) {
		if (it == sub) {
			return true;
		}
	}
	return false;
}

bool isInteger(string sub) {
	string num = "-0123456789";
	for (auto it : sub) {
		int check = 0;
		for (auto i : num) {
			if (i == it) {
				check = 1;
				break;
			}
		}
		if (check) continue;
		return false;
	}
	return true;
}

bool isReanumber(string str) {
	int i, len = str.size();
	bool flag = false;

	if (len == 0)
		return (false);
	for (i = 0; i < len; i++) {
		if (str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != '3' && str[i] != '4' && str[i] != '5' && str[i] != '6' && str[i] != '7' && str[i] != '8' && str[i] != '9' && str[i] != '.')
			return (false);
		if (str[i] == '.')
			flag = true;
	}
	return flag;
}

bool isOperator(char ch){
        string op = "+-*/><=";
        for (auto it : op) {
            if (it == ch) return true;
        }
        return false;
    };

void go(){
    vector<string> v;
	string s;
	int cnt = 0;
	while (getline(cin, s)) {
		v.push_back(s);
	}
    

	int c = 0;
	for (auto str : v) {
		if (c) {
			if (str.size() >= 2 && str[str.size() - 2] == '*' && str.back() == '/') {
				c = 0;
			}
			continue;
		}
		if (str.size() >= 2) {
			if (str[0] == '/' && str[1] == '/') {
				continue;
			}
			if (str[0] == '/' && str[1] == '*') {
				c = 1;
				continue;
			}
		}
		int left = 0, right = 0;
		int len = str.size();
		while (right <= len && left <= right) {
			if (isPunctuator(str[right]) == false) {
				right++;
			}
			if (isPunctuator(str[right]) && left == right) {
				if (isOperator(str[right])) {
					cnt++;
					cout << str[right] << " IS AN OPERATOR" << endl;
				}
				right++;
				left = right;
			}
			else if (isPunctuator(str[right]) && left != right || (right == len && left != right)) {
				string sub = str.substr(left, right - left);
				if (iskeyword(sub)) {
					cout << sub << " IS A KEYWORD" << endl;
					cnt++;
				}
				else if (isInteger(sub)) {
					cnt++;
					cout << sub << " IS AN INTEGER" << endl;
				}
				else if (isReanumber(sub)) {
					cnt++;
					cout << sub << " IS A REAL NUMBER" << endl;
				}
				else if (valididentifer(sub) && isPunctuator(str[right - 1]) == false) {
					cnt++;
					cout << sub << " IS A VALID IDENTIFIER" << endl;
				}
				else if (valididentifer(sub) == false && isPunctuator(str[right - 1]) == false) {
					cout << sub << " IS NOT A VALID IDENTIFIER" << endl;
				}
				left = right;
			}
		}
		if (str.back() == ';') {
			cnt++;
			cout << "; IS A SEPERATOR" << endl;
		}
	}
	cout << "TOTAL NUMBER OF TOKENS: " << cnt << endl;    
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("err.txt", "w", stderr);
#endif
    auto start1 = high_resolution_clock::now();
    go();
    auto stop1 = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop1 - start1);
    cerr << "Time: " << duration.count() / 1000 << endl;
    return 0;
}