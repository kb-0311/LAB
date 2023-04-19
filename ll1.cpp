#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;


void go(){
    map<pair<int, char>, pair<char, int>> mpp;
    mpp[{0, 'a'}] = { 's',3 };
    mpp[{0, 'b'}] = { 's',4 };
    mpp[{1, '$'}] = { 's',-2 };
    mpp[{2, 'a'}] = { 's',3 };
    mpp[{2, 'b'}] = { 's',4 };
    mpp[{3, 'a'}] = { 's',3 };
    mpp[{3, 'b'}] = { 's',4 };
    mpp[{4, 'a'}] = { 'r',3 };
    mpp[{4, 'b'}] = { 'r',3 };
    mpp[{4, '$'}] = { 'r',3 };
    mpp[{5, 'a'}] = { 'r',1 };
    mpp[{5, 'b'}] = { 'r',1 };
    mpp[{5, '$'}] = { 'r',1 };
    mpp[{6, 'a'}] = { 'r',2 };
    mpp[{6, 'b'}] = { 'r',2 };
    mpp[{6, '$'}] = { 'r',2 };
    map<pair<int, char>, int> gpp;
    gpp[{0, 'A'}] = 2;
    gpp[{0, 'S'}] = 1;
    gpp[{2, 'A'}] = 5;
    gpp[{3, 'A'}] = 6;
    map<int, pair<int, char>> rpp;
    rpp[1] = { 4,'S' };
    rpp[2] = { 4,'A' };
    rpp[3] = { 2,'A' };


    function<void(string)> check = [&](string ip){
        string st;
        st.push_back('0');
        int ptr = 0; bool temp = false;
        int n = ip.size();
        ll cnt = 0;
        cout<<"stack          top_of_stack  I/P    Operation"<<endl;
        while (ptr < n){
            cout<<st<<" ";
            for (int i = 0; i < 15 - st.size(); i++) cout<<" ";
            auto t = st.back() - '0';
            if (!mpp.count({t, ip[ptr]})) break;
            if (t == 1 && ip[ptr] == '$'){
                cout<<1<<"            $        Accepted"<<endl;
                temp = true;
                break;
            }
            if (mpp[{t, ip[ptr]}].first == 's'){
                cout<<t<<"            "<<ip[ptr]<<"        "<<"shift" << " " << endl;
                st.push_back(ip[ptr]);
                st.push_back(mpp[{t, ip[ptr]}].second - '0');
                ptr++;
                continue;
            }
            if (mpp[{t, ip[ptr]}].first == 'r'){
                cout << t << "            " << ip[ptr] << "        "<< "reduce" << " " << endl;
                int pops = rpp[mpp[{t, ip[ptr]}].second].first;
                char g = rpp[mpp[{t, ip[ptr]}].second].second;
                while (pops--){ if (st.empty()) break; st.pop_back();}
                if (st.empty()) break;
                auto y = st.back() - '0';
                st.push_back(g);
                st.push_back(gpp[{y, g}] - '0');
            }
            cnt++;
            if (cnt > 15) break;
        }
        if (!temp) cout<<"Rejected"<<endl;
    };


    string s;
    cin>>s;
    check(s);
}


int main(){
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    go();
    return 0;
}