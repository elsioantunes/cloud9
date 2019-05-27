//br.spoj.com/problems/CATALO13/
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

int main() {
    struct vert {
        string nome;
        int n, len;
    };
    unordered_map<string, vert> mp;

    int adj[150][150];
    int infinity = 999999;
    for(auto &i:adj)
        for(auto &j:i)
            j=infinity;

    int n, k=1;
    cin >> n;
    for(int c=0; c<n; c++) {
        string tripa, gomo;
        int no=0, i=0, oldLen = 0;
        cin >> tripa;
        while(no!=-1) {
            no = tripa.find("/", no+1);
            gomo = tripa.substr(0, no);
            if(!mp[gomo].n) {
                mp[gomo].n = k++;
                mp[gomo].len = gomo.length();
            }
            int j = mp[gomo].n;
            if(no==-1)oldLen++;
            else adj[j][i] = 3;
            adj[i][j] = mp[gomo].len-oldLen+1;
            i = j;
            oldLen = mp[gomo].len + 1;
        }
    }

    for(int c=0; c<k; c++)       // Floyd again... uh!!
        for(int i=0; i<k; i++)
            for(int j=0; j<k ; j++)
                adj[i][j]=min(adj[i][j], adj[i][c]+adj[c][j]);

    int sMin = infinity;
    for(int i=0; i<k; i++) {
        if(adj[i][0]!=infinity) {
            int s = 0;
            for(int j=0; j<k; j++) {
                if(adj[j][0]==infinity) {
                    s += adj[i][j];
                }
            }
            if(sMin>s)sMin=s;
        }
    }
    cout << sMin << endl;
    return 0;
}





/*
6
delta/india/juliet/lima
bravo/echo
bravo/foxtrot
charlie/hotel
delta/india/kilo
bravo/golf
76


3
Rock/AngraCarryOn.mp3
MPB/Caetano/Sampa.mp3
MPB/Cartola/Alvorada.mp3
59

2
Preferidas/chacoalha/uia.mp3
Preferidas/chacoalha/eia.mp3
14

*/
