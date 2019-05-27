// Estradas Escuras (Dark Roads) 
// https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2678
// https://www.urionlinejudge.com.br/judge/pt/problems/view/1152
// Histirinha: calcular a economia na iluminacao de estradas
// Objetivo: calcular a arvore geradora minima (e subtrair os pesos do total)
// Algoritmo usado: Kruskal com Union Find (Prim muito demorado)
// Ajudou:
//      https://www.youtube.com/watch?v=rsIlC0VeHew (funcionamento do algoritmo Prim)
//      entradas originais: http://www.informatik.uni-ulm.de/acm/Locals/2009/input/dark.in
//      saidas originais: http://www.informatik.uni-ulm.de/acm/Locals/2009/output/dark.out
// Relacionado:
//      http://br.spoj.com/problems/RMAPA11/ (quase identico)
//      br.spoj.com/problems/REDOTICA/
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
    bool operator < (Aresta aresta) const{
        return c > aresta.c;
    }
};


int main() {
    int m, n, a, b, c, sum, needed;
    Aresta aresta;

    while((cin >> m >> n)&&n) {
        priority_queue<Aresta>pq;
        sum = needed = 0;

        array = new int[m];
        for(int i=0; i<m; i++) 
            array[i] = i;

        for(int i=0; i<n; i++) {
            cin >> a >> b >> c;
            pq.push(Aresta(a,b,c));
            sum += c;
        }

        while(!pq.empty()) {
            aresta = pq.top();
            pq.pop();
            if(find(aresta.a) != find(aresta.b)) {
                needed += aresta.c;
                array[find(aresta.a)] = find(aresta.b);
            }
        }
        
        cout << sum-needed << endl;
    }
    return 0;
}
