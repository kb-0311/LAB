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
    map <pair<int, char>, pair<char, int>> mp;
    mp[{0, 'p'}] = { 's',3 };
    mp[{0, 'q'}] = { 's',4 };

    mp[{1, '$'}] = { 's' , -2 };

    mp[{2, 'p'}] = { 's',3 };
    mp[{2, 'q'}] = { 's',4 };

    mp[{3, 'p'}] = { 's',3 };
    mp[{3, 'q'}] = { 's',4 };

    mp[{4, 'p'}] = { 'r',3 };
    mp[{4, 'q'}] = { 'r',3 };
    mp[{4, '$'}] = { 'r',3 };

    mp[{5, '$'}] = { 'r',1 };

    mp[{6, 'p'}] = { 'r',2 };
    mp[{6, 'q'}] = { 'r',2 };
    mp[{6, '$'}] = { 'r',2 };

    map <pair<int, char>, int> gp;
    gp[{0, 'Q'}] = 2;
    gp[{0, 'P'}] = 1;

    gp[{2, 'Q'}] = 5;
    gp[{3, 'Q'}] = 6;

    map <int, pair<int, char>> rp;
    rp[1] = { 4,'P' }, rp[2] = { 4,'Q' }, rp[3] = { 2,'Q' };

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
            if (mp[{t, ip[ptr]}].first == 's')
            {
                cout << t << "            " << ip[ptr] << "        ";
                cout << "shift" << " " << endl;
                st.push_back(ip[ptr]);
                st.push_back(mp[{t, ip[ptr]}].second + '0');
                ptr++;
                continue;
            }
            else
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