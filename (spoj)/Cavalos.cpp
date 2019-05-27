// Movimentos do Cavalo
// https://www.urionlinejudge.com.br/judge/pt/problems/view/1100#include <iostream>
#include <iostream>
#include <string>
using namespace std;
int main() {
    int a, b, t, adj[64][64];
    int inf = 0xffffffff/4;
    for(int i=0; i<64; i++) {
        for(int j=0; j<64; j++) {
            adj[i][j] = inf;
            if((abs(j%8-i%8)==1&&abs(j/8-i/8)==2)||
               (abs(j%8-i%8)==2&&abs(j/8-i/8)==1)) {
                adj[i][j] = 1;
                adj[j][i] = 1;
            }
            if(i==j)adj[j][i] = 0;
        }
    }

    string p, q;
    while(cin >> q >> p) {
        a = (p[0]-'a')+(p[1]-'1')*8;
        b = (q[0]-'a')+(q[1]-'1')*8;

        int k = 0, visit[64];
        for(int i=0; i<64; i++) visit[i] = 0;
        int i = a;
        int D = b;
        while(i!=D && k < inf) {
            for(int j=0; j<64; j++)
                if(adj[i][j]!=inf)
                    adj[a][j] = min(adj[a][j], adj[a][i] + adj[i][j]);
            visit[i] = 1;
            k = inf;
            for(int j=0; j<64; j++)
                if(adj[a][j]<=k && !visit[j]) {
                    k = adj[a][j];
                    i = j;
                }
        }
        cout << "To get from "<< q <<" to "<< p <<" takes "<< k <<" knight moves." << endl;
        if(p==q)break;
    }
    return 0;
}


