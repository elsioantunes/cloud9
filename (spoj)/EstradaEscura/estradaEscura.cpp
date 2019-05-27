// Estradas Escuras
// https://www.urionlinejudge.com.br/judge/pt/problems/view/1152
// adaptado de "Reduzindo detalhes em um mapa"
//              http://br.spoj.com/problems/RMAPA11/
// algoritmo  "Prim" 
// Video que ajudou: https://www.youtube.com/watch?v=rsIlC0VeHew
// relacionado: br.spoj.com/problems/REDOTICA/ (resolvido com kruskal)
// entradas originais: http://www.informatik.uni-ulm.de/acm/Locals/2009/input/dark.in
// saidas originais: http://www.informatik.uni-ulm.de/acm/Locals/2009/output/dark.out
// PS: nao foi aceito. Resposta correta mas o limite de tempo eh pequeno

#include <iostream>
using namespace std;

int main() {
    int n, m, x, y, p;
     int inf = 0x7fffffff;

    while(true){
        int tt = 0; 
        cin >> n >> m;
        if(!n)break;
        
        int *v = new  int[n];
        int *d = new  int[n];
        int **adj = new  int*[n];
        for(int i=0;i<n;i++)
            adj[i] = new int[n];

        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
                adj[i][j]=inf,
                v[i]=0,
                d[i]=inf;
    
        for(int i=0; i<m; i++)
            cin >> x >> y >> p,
            tt += p,
            adj[x][y]=adj[y][x]=p;
    
        
        int j=0,s=0,k=n;
        d[0] = 0;
         
         
        while(k--) {                           // Prim
            int minimo = inf;
            for(int i=0; i<n; i++)
                if (!v[i] && d[i] < minimo)
                    minimo = d[i],
                    j = i;
    
            for(int i=0; i<n; i++)
                d[i] = min(d[i], adj[i][j]);
    
            v[j] = 1;
            s += minimo;
        }
        cout << tt - s << endl;
    }
    return 0;
}
