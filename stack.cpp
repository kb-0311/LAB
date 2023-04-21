#include<iostream>
#include<algorithm>
#include<vector>
#include<map>
#include<string>
#define pb push_back
using namespace std;



void parse(string& ip, map<pair<int, char>, pair<char, int>>& ACTION, map<pair<int, char>, int>& GOTO, map <int, pair<int, char>>& rp){
    string st; // will be used as stack
    st.push_back('0');
    int ptr = 0; // stack pointer
    bool temp = 0;
    int len = ip.length();
    int ct = 0;
    cout << "Stack          Top_of_stack  I/P    Operation" << endl;
    while(ptr < len){
        cout << st << " ";
        for(int i = 0; i < 15 - st.size(); i++) cout << " ";
        auto t = st.back() - '0'; // Conversion 
        // Note that t here represents the top of the stack
        if(!ACTION.count({t, ip[ptr]})) break;

        if(t == 1 && ip[ptr] == '$'){ // Accepted string
            cout << 1 << "            $        Accepted" << endl;
            temp = 1;
            break;
        }
        // For shift operation
        if(ACTION[{t, ip[ptr]}].first == 's'){
            cout << t << "            " << ip[ptr] << "        ";
            cout << "shift" << " " << endl;
            st.push_back(ip[ptr]); // Pushing back the string pointer
            st.push_back(ACTION[{t, ip[ptr]}].second + '0'); // Pushing the state
            ptr++; // Increment stack pointer
            continue;
        }
        // For reduce operation
        else{
            cout << t << "            " << ip[ptr] << "        ";
            cout << "reduce " << endl;
            // Find the number of popping operations to perform
            int pop_stack = rp[ACTION[{t, ip[ptr]}].second].first;
            char go_to_char = rp[ACTION[{t, ip[ptr]}].second].second;
            while(pop_stack--){if(st.empty()) break; st.pop_back();}

            if(st.empty()) break;

            // Check GOTO and then push the Char and its value to the stack
            auto y = st.back() - '0';
            st.push_back(go_to_char);
            st.push_back(GOTO[{y, go_to_char}] + '0');
        }

        ct++;
        if(ct > 15) break;
    }
    if(!temp) cout << "\nRejected" << endl;
}

void soln(){
    map<pair<int, char>, pair<char, int>> ACTION;
    map<pair<int, char>, int> GOTO;

    ACTION[{0, 'p'}] = {'s', 3};
    ACTION[{0, 'q'}] = {'s', 4};

    ACTION[{1, '$'}] = {'s', -3};

    ACTION[{2, 'p'}] = {'s', 3};
    ACTION[{2, 'q'}] = {'s', 4};

    ACTION[{3, 'p'}] = {'s', 3};
    ACTION[{3, 'q'}] = {'s', 4};

    ACTION[{4, 'p'}] = {'r', 3};
    ACTION[{4, 'q'}] = {'r', 3};
    ACTION[{4, '$'}] = {'r', 3};

    ACTION[{5, '$'}] = {'r', 1};

    ACTION[{6, 'p'}] = {'r', 2};
    ACTION[{6, 'q'}] = {'r', 2};
    ACTION[{6, '$'}] = {'r', 2};

    GOTO[{0, 'Q'}] = 2;
    GOTO[{0, 'P'}] = 1;

    GOTO[{2, 'Q'}] = 5;
    GOTO[{3, 'Q'}] = 6;

    // Key = production number
    // first = No of elements to pop
    // second = symbol its reduced to
    map <int, pair<int, char>> rp;
    rp[1] = {4, 'P'};
    rp[2] = {4, 'Q'};
    rp[3] = {2, 'Q'};
    
    string s;
    cout << "Enter the string " << endl;
    cin >> s;

    parse(s, ACTION, GOTO, rp);
}

int main(){
    int tc;
    cout << "Enter the number of testcases: " << endl;
    cin >> tc;
    for(int i = 0; i < tc; i++){
        soln();
    }
return 0;
}