#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <chrono>
using namespace std;
// using namespace __gnu_pbds;
using namespace chrono;
typedef long long int ll;

vector<string> a(1e5);
map<char, int> fir_vis, fol_vis;
map<char, vector<string>> mpp;
map<char, set<char>> fir, fol;
char eps = '#';
void cal_first(char c){
    fir_vis[c] = 1;
    for (auto &it: mpp[c]){

        if (!mpp.count(it[0])){
            fir[c].insert(it[0]);
            continue;
        }

        if (!fir_vis[it[0]]) cal_first(it[0]);

        for (auto& j: fir[it[0]]){
            if (j == eps){
                int i;
                for (i = 1; i < it.size(); i++){
                    if (!mpp.count(it[i])){
                        fir[c].insert(it[i]);
                        break;
                    }
                    if (!fir_vis[it[i]]) cal_first(it[i]);
                    for (auto& k: fir[it[i]]){
                        if (k != eps){
                            fir[c].insert(k);
                        }
                    }
                    if (fir[it[i]].find(eps) == fir[it[i]].end()) break;
                }
                if (i == it.size()) fir[c].insert(j);
                continue;
            }
            fir[c].insert(j);
        }
    }
}
void cal_fol(char c){
    fol_vis[c] = 1;
    for (int i = 0; i < a.size(); i++){
        string s = a[i];
        for (int j = 3; j < s.size(); j++){
            if (s[j] == c){
                int ind = j + 1;
                if (ind == s.size()){
                    if (!fol_vis[s[0]]) cal_fol(s[0]);
                    if (s[0] == c) fol[s[0]].insert('$');
                    for (auto& k: fol[s[0]]) fol[c].insert(k);
                }
                else{
                    if (!mpp.count(s[ind])){
                        fol[c].insert(s[ind]);
                        continue;
                    }
                    for (auto& k: fir[s[ind]]){
                        if (k == eps){
                            int jj = j + 1;
                            for (int jj = j + 1; jj < s.size(); jj++){
                                if (!mpp.count(s[jj])){
                                    fol[c].insert(s[jj]);
                                    break;
                                }
                                for (auto& ch: fir[s[jj]]){
                                    if (ch != eps) fol[c].insert(ch);
                                }
                                if (fir[s[jj]].find(eps) == fir[s[jj]].end()) break;
                            }
                            if (jj == s.size()){
                                if (s[0] == c) fol[s[0]].insert('$');
                                if (!fol_vis[s[0]]) cal_fol(s[0]);
                                for (auto& k: fol[s[0]]) fol[c].insert(k);
                            }
                            continue;
                        }
                        fol[c].insert(k);
                    }
                }
            }
        }
    }
}
void go(){
    int n;
    cin>>n;
    for (int i = 0; i < n; i++){
        cin>>a[i];
        string s = a[i].substr(3, a[i].size());
        mpp[a[i][0]].push_back(s);
    }

    for (auto& it: a){
        if (!fir_vis[it[0]]) cal_first(it[0] );
    }
    cout<<"First"<<endl;
    for (auto& it: fir){
        cout<<it.first<<" -- ";
        for (auto& i: it.second){
            cout<<i<<" ";
        }
        cout<<endl;
    }
    cout<<endl;

    fol[a[0][0]].insert('$');
    for (auto& it: a){
        if (!fol_vis[it[0]]) cal_fol(it[0]);
    }
        cout<<"Follow"<<endl;

    for (auto& it: fol){
        cout<<it.first<<" -- ";
        for (auto& i: it.second){
            cout<<i<<" ";
        }
        cout<<endl;
    }
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