// br.spoj.com/problems/DESVIO/ modificado para o "Mania de par" da maratona
#include <iostream>
#include <algorithm>
using namespace std;
int N, M, U, V, P;
int inf = 0x7fffffff;
int main() {
    cin >> N >> M;

    int **adj = new int*[N*2];                        // aloc mem
    for(int i=0; i<N*2; i++) adj[i] = new int[N*2];
    bool *visit = new bool[N*2];

    for(int i=0; i<N*2; i++) // o dobro dos vertices
        for(int j=0; j<N*2; j++)
            if(i==j) adj[i][j] = 0;  // zerando igual
            else adj[i][j] = inf;    // infinito no resto
    for(int i=0; i<N*2; i++) visit[i] = false; // zerando visited

    for(int i=0; i<M; i++) {  // coletando o grafo
        cin >> U >> V >> P;
        U--;V--; // vert numerados de zero a N
        adj[U][V+N]=P;
        adj[V+N][U]=P;  // ao invés de ligar o vértice ao proximo
        adj[U+N][V]=P;  // ligo a uma copia dele lá no final de adj
        adj[V][U+N]=P;  // a ligação só existe se ele foi pra cópia e voltou.
    }

    int i = 0;   // origem            //
    int D = N-1; // destino           //
    int k = 0;   // menor distancia   //       dijikstra, uh!
    while(i!=D && k < inf) {          //
        for(int j=0; j<N*2; j++)      //
            if(adj[i][j]!=inf)
                adj[0][j] = min(adj[0][j], adj[0][i] + adj[i][j]);

        visit[i] = true; // visited!
        k = inf;
        for(int j=0; j<N*2; j++)
            if(adj[0][j]<=k && !visit[j]) {
                k = adj[0][j]; // procurando o cara ainda não visitado
                i = j;         // com a menor distância da origem
            }                  // pra retornar em i.
    }                          // se não achar, k = infinito.

    if(k==inf) cout << "-1" << endl;
    else cout << k << endl;
    return 0;
}


