#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <map>
using namespace std;

// Define operator precedence
map<char, int> prec{{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}};

// Function to generate Three Address Code
vector<string> generate_TAC(const string& expr) {
    vector<string> TAC; // to store the Three Address Code
    stack<char> opstack; // to store operators
    stack<string> valstack; // to store values

    // Function to perform operations when a higher precedence operator is encountered
    auto perform_op = [&](){
        char op = opstack.top();
        opstack.pop();
        string op2 = valstack.top();
        valstack.pop();
        string op1 = valstack.top();
        valstack.pop();
        string res = "t" + to_string(TAC.size()+1); // new temporary variable
        TAC.push_back(res + " = " + op1 + " " + op + " " + op2);
        valstack.push(res);
    };

    for (int i = 0; i < expr.length(); i++) {
        if (expr[i] == ' ') {
            continue;
        }
        else if (isdigit(expr[i]) || isalpha(expr[i])) {
            string val = "";
            while (i < expr.length() && (isdigit(expr[i]) || isalpha(expr[i]))) {
                val += expr[i];
                i++;
            }
            i--;
            valstack.push(val);
        }
        else if (expr[i] == '(') {
            opstack.push(expr[i]);
        }
        else if (expr[i] == ')') {
            while (opstack.top() != '(') {
                perform_op();
            }
            opstack.pop();
        }
        else { // operator
            while (!opstack.empty() && opstack.top() != '(' && prec[opstack.top()] >= prec[expr[i]]) {
                perform_op();
            }
            opstack.push(expr[i]);
        }
    }

    while (!opstack.empty()) {
        perform_op();
    }

    return TAC;
}

int main() {
    string expr = "x = a+b*c-d";
    vector<string> TAC = generate_TAC(expr);
    for (string tac : TAC) {
        cout << tac << endl;
    }
    return 0;
}
