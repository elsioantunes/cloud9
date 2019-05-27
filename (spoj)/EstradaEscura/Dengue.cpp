// http://br.spoj.com/problems/DENGUE/
// Algoritmo: desfolhamento
// similares: 
//      http://br.spoj.com/problems/REUNIAO2/  (floyd w)
//      http://br.spoj.com/problems/SUPERMER/  (medianas)
//      http://br.spoj.com/problems/REDOTICA/  (kruskal)

#include <iostream>
using namespace std;
int main() {
    int T = 1, n, x, y;
    int k, h, p, s;
    while(1) {
        cin >> n;
        if(n==0)break;
        int soma[n], grau[n], fila[n];
        for(int i=0; i<n; i++) {
            grau[i]=0;soma[i]=0;fila[i]=0;
        }
        for(int i=0; i<n-1; i++) {
            cin >> x >> y;
            x--;y--;
            grau[x]++;grau[y]++;
            soma[x]+=y;soma[y]+=x;
        }
        k=h=0;
        for(int i=0; i<n; i++)
            if(grau[i]==1)       // eh folha?
                fila[k++] = i;   // poe na fila!


        for(int i=0; i<n; i++) {
            p = fila[h++];       // pega vertice da fila
            s = soma[p];
            grau[s]--;
            soma[s]-= p;
            if(grau[s]==1)       // eh folha agora?
                fila[k++] = s;   // poe na fila!
        }
        // O ultimo (ou penultimo) colocado na fila
        // eh o "vertice central"  ou com maior excentricidade.
        cout << "Teste "  << T++ << endl;
        cout << fila[n-1]+1 << endl;
        cout << endl;
    }
    return 0;
}
