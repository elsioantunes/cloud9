// Reduzindo detalhes em um mapa
// http://br.spoj.com/problems/RMAPA11/
// algoritmo  "Prim" 
// Video que ajudou: https://www.youtube.com/watch?v=rsIlC0VeHew
//                   https://www.youtube.com/watch?v=RXL8Z-HfdHQ
// relacionado: br.spoj.com/problems/REDOTICA/ (resolvido com kruskal)

#include <iostream>
using namespace std;

int main() {
    int n, m, x, y, p, inf = 500;
    cin >> n >> m;
    int adj[n][n], v[n], d[n];

    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            adj[i][j]=inf,
            v[i]=0,
            d[i]=inf;

    for(int i=0; i<m; i++)
        cin >> x >> y >> p,
        adj[--x][--y]=adj[y][x]=p;



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
    cout << s << endl;
    return 0;
}
