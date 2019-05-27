// br.spoj.com/problems/CATALO13/
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

int main() {
    struct vertice{
        string s, pai;
        int i, f, p, r;
        bool isFolha;
    };
    unordered_map<string, vertice> mp;
    int T = 0, n, k = 0;
    cin >> n;
    for(int c=0; c<n; c++) {
        vertice u;
        string tripa, gomo;
        int no = 0;
        cin >> tripa;
        T += tripa.length();
        tripa = "/" + tripa; // pra facilitar as contas
        while(no!=-1) {
            no = tripa.find("/", no+1);
            gomo = tripa.substr(0, no);
            vertice v;
            if(!mp[gomo].f){
                v.isFolha = no==-1;
                v.s = gomo;
                v.p = gomo.length() - u.s.length();
                v.pai = u.s;
                mp[gomo] = v;
            }
            mp[gomo].f++;
            u = mp[gomo];
        }
    }


    int s, r = T;
    for(auto p:mp){
        if(p.second.isFolha){
            s = T;
            vertice q = p.second;
            while(q.pai!=""){
                q = mp[q.pai];
                s += (n-q.f)*3 - q.f*q.p;
            }
            if(s<r)r=s;
        }

    }
    cout << r << endl;
    return 0;
}





