#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

int main() {
    int n, galho, k=1, peso[150], m;
    string tripa, gomo;
    unordered_map<string, int> mp;

    peso[0] = -1;

    int adj[150][150];
    for(auto &i:adj)
        for(auto &j:i)
            j=-1;

    cin >> n;
    for(int i=0; i<n; i++) {
        cin >> tripa;
        tripa += '/';
        galho = 0;
        int no = 0;
        int last;


        while(1) {
            // to do list:
            //  - tenta tirar um gomo da tripa

            m = no;
            no = tripa.find("/",no+1);
            if(no==-1) {
                adj[last][mp[gomo]]--;
                break;
            }

            gomo = tripa.substr(0, no);
            if(!mp[gomo]) {
                mp[gomo] = k;
                peso[k] = gomo.length();
                k++;
            }


            adj[galho][mp[gomo]] = peso[mp[gomo]] - peso[galho];
            last = galho;
            galho = mp[gomo];


            //  - identificar esse gomo como único
            //       pra não confundir com pastas filhas de mesmo nome.
            //  - coloco o gomo no galho atual da árvore
            //       no início, galho = 0 (raiz)
            //  - fazer o gomo como novo galho
            //       pra que o próximo gomo da tripa
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
