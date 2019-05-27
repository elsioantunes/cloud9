#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;
struct vert {
    string s, pai;
    int r;
    bool OK;
};
unordered_map<string, vert>mp;
string nome, linha;
int n, total;
unsigned short del, fls, barra;

int main() {
    vert v;
    cin >> n;
    while(n--) {
        cin >> linha;
        vert u;
        total += linha.length();
        fls ++;
        del = 1;
        while(true) {
            barra = linha.find("/",del) + 1;
            nome = linha.substr(del-1, barra-del);
            v.s = nome;
            v.pai = u.s;

            if(!barra)
                v.OK = true;
            else
                v.OK = false;

            v.r = mp[nome].r?mp[nome].r:0;
            v.r += barra-del+4;
            mp[nome] = u = v;
            if(!barra)break;
            del = barra+1;
        }
    }

    n = total;
    for(auto &i:mp) {
        v = i.second;
        int x = total;
        while(v.pai!="") {
            v = mp[v.pai];
            x += 3*fls - v.r;
        }
        if(x<n)n=x;
    }

    cout << n << endl;
    return 0;
}



