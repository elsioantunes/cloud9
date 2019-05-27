//br.spoj.com/problems/CATALO13/
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

int main() {
    int n, peso[150];
    string tripa, gomo;
    unordered_map<string, int> mp;

    peso[0] = -1;

    int adj[150][150];
    for(auto &i:adj)
        for(auto &j:i)
            j=-1;

    int k = 1;
    cin >> n;
    for(int i=0; i<n; i++) {
        cin >> tripa;
        tripa += '/'; // pra facilitar as contas

        int no = 0;
        int last;
        int galho = 0;
        int nomo;

        while(1) {
            no = tripa.find("/",no+1);
            if(no==-1) {
                adj[last][nomo]--;
                break;
            }
            gomo = tripa.substr(0, no);

            if(!mp[gomo]) {          // usando strings
                mp[gomo] = k++;        // como endere�o de mem�ria
                nomo = mp[gomo];
                peso[nomo] = gomo.length();
            }

            adj[galho][nomo] = peso[nomo] - peso[galho];
            last = galho;
            galho = nomo;

            //  - identificar esse gomo como �nico
            //       pra n�o confundir com pastas filhas de mesmo nome.
            //  - coloco o gomo no galho atual da �rvore
            //       no in�cio, galho = 0 (raiz)
            //  - fazer o gomo como novo galho
            //       pra que o pr�ximo gomo da tripa
            //       seja filho dele.
        }
    }

    // uma vez terminada a montagem do grafo, procede-se a busca pelo caminho mais curto.

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
