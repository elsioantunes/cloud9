// Mania de par
//
// problem: URI https://www.urionlinejudge.com.br/judge/pt/problems/view/1931
//          UVA https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=4829
//
// Origem: XX Maratona de Programação da SBC 2015
//
// related: SPOJ br.spoj.com/problems/DESVIO/
//
// Obs: esta versão da solução, apesar de resolver os casos que constam no site da maratona
//      não foram aceitos pelos juízes online acima citados.

#include <iostream>
#include <algorithm>
#include <vector>

#define inf 1000000000   // 1 bilhão
#define A(a,b) adj[a][b]
#define dist(a) adj[0][a]
#define mindist(a, b) min(dist(b), dist(a) + A(a, b))

using namespace std;

int n, N, M, U, V, P;

int main() {
    cin >> n >> M;
    N = n*2;
    vector<int> adj[N];
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            adj[i].push_back(inf);

    vector<bool> visit;
    for(int i=0; i<N; i++) visit.push_back(false);

    for(int i=0; i<M; i++) {
        cin >> U >> V >> P;
        U--;V--;
        A(U, V+n)=P;
        A(V+n, U)=P;
        A(U+n, V)=P;
        A(V, U+n)=P;
    }


    int i = 0;   // origem
    int D = n-1; // destino
    int k = 0;   // menor distancia

    while(i!=D && k < inf) {
        if(i)
        for(int j=0; j<N; j++)
            if(A(i, j)!=inf)
                dist(j) = min(dist(j), dist(i) + A(i, j));

        visit[i] = true;
        k = inf;
        for(int j=0; j<N; j++)
            if(dist(j)<=k && !visit[j]) {
                k = dist(j);
                i = j;
            }
    }
    if(k==inf) cout << -1 << endl;
    else cout << k << endl;
    return 0;
}


