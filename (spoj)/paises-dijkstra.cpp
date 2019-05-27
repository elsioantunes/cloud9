//br.spoj.com/problems/PAISES/
#include <iostream>
#include <stdio.h>
using namespace std;
int N, E, X, Y, H, K, O, D;
int infinity = 999999;
int adj[502][501];
int main() {
    while(true) {
        cin >> N >> E;
        if(N==0)break;
        for(int i=1; i<=N; i++)
            for(int j=1; j<=N; j++)
                adj[i][j]=infinity;
        for(int i=0; i<E; i++) {
            scanf("%d%d%d", &X, &Y, &H); adj[X][Y]=H;
            if(adj[Y][X]!=infinity) adj[X][Y]=adj[Y][X]=0;
        }
        cin >> K;
        for(int i=0; i<K; i++) {
            cin >> O >> D;
            for(int i=1; i<=N; i++) adj[N+1][i]=0; // dijikstra, uh!
            int j = O; // isto eh um oh!
            int k = 0; // isto nao eh.
            while(j!=D && k<infinity){
                for(int i=1; i<=N; i++)
                    if(adj[j][i]!=infinity)
                        adj[O][i]=min(adj[O][i], adj[O][j]+adj[j][i]);
                adj[N+1][j]=1;
                k = infinity;
                for(int i=1; i<=N; i++)
                    if(adj[O][i]<=k && !adj[N+1][i]){
                        k = adj[O][i];
                        j = i;
                    }
            }
            if(k!=infinity)
                cout << k << endl;
            else
                cout << "Nao e possivel entregar a carta" << endl;
        }
    }
    return 0;
}

