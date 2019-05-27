// Desrugenstein
// https://www.urionlinejudge.com.br/judge/pt/problems/view/1111
#include <iostream>
using namespace std;
int main() {
    unsigned int inf = 0xffffffff/4;
    int a, b = 0, n;
    while(cin >> n) {
        if(!n)break;

        int adj[n*n][n*n+1];
        for(int i=0; i<n*n; i++)
            for(int j=0; j<n*n; j++) {
                adj[i][j] = inf;
                if(i==j)adj[j][i] = 0;
            }

        for(int i=0; i<n*n; i++) {
            cin >> b; if(b) adj[i][i-n] = 1;
            cin >> b; if(b) adj[i][i+n] = 1;
            cin >> b; if(b) adj[i][i-1] = 1;
            cin >> b; if(b) adj[i][i+1] = 1;
        }

        int x,y,z,w;
        int m;
        cin >> m;
        for(int h=0; h<m; h++) {
            cin >> x >> y >> z >> w;
            a = (n-y-1)*n+x;
            b = (n-w-1)*n+z;

            int k = 0, visit[n*n];
            for(int i=0; i<n*n; i++) visit[i] = 0;
            int i = a;
            int D = b;
            while(i!=D && k < inf) {
                for(int j=0; j<n*n; j++)
                    if(adj[i][j]!=inf)
                        adj[a][j] = min(adj[a][j], adj[a][i] + adj[i][j]);
                visit[i] = 1;
                k = inf;
                for(int j=0; j<n*n; j++)
                    if(adj[a][j]<=k && !visit[j]) {
                        k = adj[a][j];
                        i = j;
                    }
            }
            if(k==inf)cout << "Impossible" << endl;
            else cout << k << endl;
        }
        cout << endl;
    }
    return 0;
}


