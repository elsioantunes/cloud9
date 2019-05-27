//br.spoj.com/problems/CATALO13/
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

int main() {
    unordered_map<string, int> mp;
    struct pasta {
        string nome;
        int n;
    };

    int adj[150][150];
    for(auto &i:adj)
        for(auto &j:i)
            j=-1;

    int n, k=1;
    cin >> n;
    for(int c=0; c<n; c++) {
        string tripa;
        int no=0, i=0;
        cin >> tripa;
        while(no!=-1) {
            pasta p;
            no = tripa.find("/");
            p.nome = tripa.substr(0, no);
            tripa = tripa.erase(0, no+1);

            if(!mp[p.nome]){
                mp[p.nome]=k++;
            }
            p.n = mp[p.nome];

            adj[i][p.n] = p.n + 10;
            i = p.n;
        };
    }

    cout << endl;
    for(auto &i:mp){
        cout << i.first << " : " << i.second << endl;
    }
    cout << endl;



    for(int i=0;i<k;i++){
        cout << endl;
        for(int j=0;j<k;j++){
            cout <<adj[i][j] << "  ";
        }
        cout << endl;
    }
    //cout << " : " << no << " : "<< gomo << endl;

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
