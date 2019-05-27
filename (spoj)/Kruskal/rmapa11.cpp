// Reduzindo detalhes em um mapa
// http://br.spoj.com/problems/RMAPA11/
// Historinha:  retornar soma dos comprimentos das rodovias do subconjunto selecionado para um dado mapa.
// Objetivo: calcular a arvore geradora minima
// Algoritmo usado: Kruskal com Union Find
// Ajudou:
//      https://www.youtube.com/watch?v=rsIlC0VeHew (funcionamento do algoritmo Prim)
//      http://www.informatik.uni-ulm.de/acm/Locals/2009/archive/team06_14:16:01_dark.cpp
// Relacionado:
//      br.spoj.com/problems/REDOTICA/
//      https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2678
//      https://www.urionlinejudge.com.br/judge/pt/problems/view/1152

#include <iostream>
#include <queue>
using namespace std;

int *array;

int find(int i) {
    if(i == array[i]) 
        return i;
    return array[i] = find(array[i]);
}

struct Aresta {
    int a, b, c;
    Aresta(){}
    Aresta(int x, int y, int z) {
        a = x;
        b = y;
        c = z;
    }
};

bool operator<(Aresta a, Aresta b){
    return a.c>b.c;
}

int main() {
    int m, n, a, b, c, sum;

    cin >> m >> n;

    priority_queue<Aresta>pq;
    sum = 0;

    array = new int[m];
    for(int i=0; i<m; i++) 
        array[i] = i;

    for(int i=0; i<n; i++) {
        cin >> a >> b >> c;
        pq.push(Aresta(a,b,c));
    }

    while(!pq.empty()) {
        Aresta aresta = pq.top();
        if(find(aresta.a) != find(aresta.b)) {
            sum += aresta.c;
            array[find(aresta.a)] = find(aresta.b);
        }
        pq.pop();
    }
    
    cout << sum << endl;

    return 0;
}
