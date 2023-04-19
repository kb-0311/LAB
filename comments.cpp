#include <iostream>
#include <string>
#include <chrono>
#include <fstream>
using namespace std;
using namespace chrono;
typedef long long int ll;

/* Write a C program to identify whether a given line is a comment or not.*/
void go(){
    string st, s;
    while (getline(cin, st)){
        s += st;
    }
    int sz = s.length();
    if (s[0] == '/' && s[1] == '/') { cout << "It's a comment!" << endl; return; }
    if (s[0] == '/' && s[1] == '*' && s[sz - 2] == '*' && s[sz - 1] == '/' && sz > 4) { cout << "It's a comment!" << endl; return; }
    cout << "It's not a comment!" << endl;
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
