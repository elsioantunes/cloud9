// http://br.spoj.com/problems/ORKUT/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <sstream>
using namespace std;

struct vertice {
    int grauEntrada;
    vector<string> adj;
};

int main() {
    string nome;
    string nome2;
    int n, N, T=1;

    while(true) {
        int nArestas = 0;
        int N;
        cin >> N;
        if(N==0)break;
        for(int i=0; i<N; i++) cin >> nome;

        queue<string> fila;
        unordered_map <string, vertice> vert;

        for(int i=0; i<N; i++) {
            cin >> nome >> n;
            vert[nome].grauEntrada = n;
            if(n==0) fila.push(nome);

            for(int j=0; j<n; j++) {
                cin >> nome2;
                nArestas ++;
                vert[nome2].adj.push_back(nome);
            }
        }



        stringstream saida; // Ordenação topológica
        while(!fila.empty()) {
            string u = fila.front();
            fila.pop();
            saida << u << " ";
            for(const auto &el:vert[u].adj) {
                n = --vert[el].grauEntrada;
                nArestas--;
                if(n==0)
                    fila.push(el);
            }
        }
        cout << "Teste "<< T++ << "\n";
        if(nArestas==0) cout << saida.str() << endl << endl;
        else cout << "impossivel\n\n";

    }

    return 0;
}
