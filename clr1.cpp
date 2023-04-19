#include <iostream>
#include <chrono>
#include <map>
#include <string>
#include <functional>

using namespace std;
// using namespace __gnu_pbds;
using namespace chrono;
typedef long long int ll;
void go(){
    /*
        ip : xxxyy$ -> Accepted
        ip : xxxy$ -> Rejected
    */
    map <pair<int, char>, pair<char, int>> mp;
    mp[{0, 'x'}] = { 's',3 };
    mp[{0, 'y'}] = { 's',4 };

    mp[{1, '$'}] = { 's' , -2 };

    mp[{2, 'x'}] = { 's',6 };
    mp[{2, 'y'}] = { 's',7 };

    mp[{3, 'x'}] = { 's',3 };
    mp[{3, 'y'}] = { 's',4 };

    mp[{4, 'x'}] = { 'r',3 };
    mp[{4, 'y'}] = { 'r',3 };

    mp[{5, '$'}] = { 'r',1 };

    mp[{6, 'x'}] = { 'r',6 };
    mp[{6, 'y'}] = { 'r',7 };

    mp[{7, '$'}] = { 'r',3 };

    mp[{8, 'x'}] = { 'r',2 };
    mp[{8, 'y'}] = { 'r',2 };

    mp[{9, '$'}] = { 'r',2 };

    map <pair<int, char>, int> gp;
    gp[{0, 'X'}] = 1;
    gp[{0, 'Z'}] = 2;

    gp[{2, 'Z'}] = 5;

    gp[{3, 'Z'}] = 8;

    gp[{6, 'Z'}] = 9;

    map <int, pair<int, char>> rp;
    rp[1] = { 4,'X' }, rp[2] = { 4,'Z' }, rp[3] = { 2,'Z' };

    function <void(string)> check = [&](string ip){
        string st; st.push_back('0');
        int ptr = 0; bool temp = 0;
        int n = ip.length();
        ll ct = 0;
        cout << "stack          top_of_stack  I/P    Operation" << endl;
        while (ptr < n)
        {
            cout << st << " "; for (int i = 0; i < 15 - st.size(); i++) cout << " ";
            auto t = st.back() - '0';
            if (!mp.count({ t,ip[ptr] })) break;
            if (t == 1 && ip[ptr] == '$')
            {
                cout << 1 << "            $        Accepted" << endl;
                temp = 1;
                break;
            }
            if (mp[{t, ip[ptr]}].first == 's') //Shift Operation
            {
                cout << t << "            " << ip[ptr] << "        ";
                cout << "shift" << " " << endl;
                st.push_back(ip[ptr]);
                st.push_back(mp[{t, ip[ptr]}].second + '0');
                ptr++;
                continue;
            }
            else                                //Reduce Operation
            {
                cout << t << "            " << ip[ptr] << "        ";
                cout << "reduce" << " " << endl;
                int pops = rp[mp[{t, ip[ptr]}].second].first;
                char g = rp[mp[{t, ip[ptr]}].second].second;
                while (pops--) { if (st.empty()) break; st.pop_back(); }
                if (st.empty()) break;
                auto y = st.back() - '0';
                st.push_back(g);
                st.push_back(gp[{ y, g}] + '0');


            }
            ct++;
            if (ct > 15) break;
        }
        if (!temp) cout << "\nRejected" << endl;
    };

    string s; cin >> s;
    check(s);
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