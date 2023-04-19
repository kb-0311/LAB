#include <iostream>
#include <string>
bool X();
bool Y();
bool Z();
bool W();
using namespace std;

string input;
int idx;

bool match(char c) {
    if (input[idx] == c) {
        idx++;
        return true;
    }
    return false;
}

bool X() {
    if (match('x') && Y()) {
        return true;
    }
    return false;
}

bool Y() {
    if (input[idx] == 'y') {
        if (Z() && match('w') && Y()) {
            return true;
        }
        else if (match('x') && Y()) {
            return true;
        }
        else {
            return true;
        }
    }
    else {
        return true;
    }
}

bool Z() {
    if (match('y') && W()) {
        return true;
    }
    return false;
}

bool W() {
    if (input[idx] == 'z') {
        if (match('z') && W()) {
            return true;
        }
        else {
            return true;
        }
    }
    else {
        return true;
    }
}

int main() {
    cout << "Enter input string: ";
    getline(cin, input);
    idx = 0;

    if (X() && idx == input.length()) {
        cout << "Accepted" << endl;
    }
    else {
        cout << "Rejected" << endl;
    }

    return 0;
}
