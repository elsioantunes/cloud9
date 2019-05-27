//http://br.spoj.com/problems/DENGUE/
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

        for(int i=0; i<n-1; i++) { /// desfolhamento
            cin >> x >> y;
            x--;y--;
            grau[x]++;grau[y]++;   // grau eh o numero de adjs
            soma[x]+=y;soma[y]+=x; // a soma guarda seus nomes (genial isso!)
        }

        k=h=0;
        for(int i=0; i<n; i++)
            if(grau[i]==1)       // eh folha?
                fila[k++] = i;   // poe na fila!

        for(int i=0; i<n; i++) {
            p = fila[h++];       // pega vertice da fila
            s = soma[p];         // ele eh folha, a soma aponta pro adj.
            grau[s]--;           // o grau desse adj eh decrementado
            soma[s]-= p;         // retira-se a folha p
            if(grau[s]==1)       // s virou folha agora?
                fila[k++] = s;   // poe na fila!
        }
        // O ultimo (ou penultimo) colocado na fila
        // eh o "vertice central"  ou com menor excentricidade.
        cout << "Teste "  << T++ << endl;
        cout << fila[n-1]+1 << endl;
        cout << endl;
    }
    return 0;
}
