//br.spoj.com/problems/PAISES/
#include <iostream>
#include <stdio.h>
using namespace std;
int N, E, X, Y, H, K, O, D;
int infinity = 999999;
int adj[501][501];
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
        for(int k=1; k<=N; k++)       // Floyd again... uh!!
            for(int i=1; i<=N; i++)
                if( i!=k && adj[i][k]<infinity)
                    for(int j=1; j<=N; j++)
                        if(adj[i][j] > adj[i][k]+adj[k][j])
                            adj[i][j]=adj[i][k]+adj[k][j];
        cin >> K;
        for(int i=0; i<K; i++) {
            cin >> O >> D;
            if(adj[O][D]!=infinity)
                cout << adj[O][D] << endl;
            else
                cout << "Nao e possivel entregar a carta" << endl;
        }
    }
    return 0;
}

