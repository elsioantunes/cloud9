// Reduzindo detalhes em um mapa
// http://br.spoj.com/problems/RMAPA11/
// Histirinha:  retornar soma dos comprimentos das rodovias do subconjunto selecionado para um dado mapa.
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
using namespace std;

int *array;

int find(int i) {
    if(i == array[i]) 
        return i;
    else 
        return array[i] = find(array[i]);
}

struct Aresta {
    int a, b, c;
    Aresta(){}
    Aresta(int x, int y, int z) {
        a = x; b = y; c = z;
    }
};

int main() {
    int m, n, a, b, c, sum=0;

    cin >> n >> m;

    array = new int[n];
    Aresta *arestas = new Aresta[m];

    for(int i=0; i<n; i++)
        array[i] = i;

    for(int i=0; i<m; i++)
        arestas[i] = Aresta(0,0,-1);

    int k=0;
    for(int i=0; i<n; i++) {
        cin >> a >> b >> c;
        //arestas.push(Aresta(a,b,c));
        int j=0;
        while(j<k && c>arestas[j].c) j++;
        if(c!=arestas[j].c){
            for(int h=j;h>j;h--)
                arestas[h] = arestas[h-1];
            arestas[j] = Aresta(a,b,c);
            k++;
        }
    }
    
    while(k--) {
        Aresta pq = arestas[k];
        if(find(pq.a) != find(pq.b)) {
            sum += pq.c;
            array[find(pq.a)] = find(pq.b);
        }
    }
    cout << sum << endl;

    return 0;
}
