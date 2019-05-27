//http://br.spoj.com/problems/CATALO13/
#include <iostream>
#include <stdio.h>
using namespace std;
int N, E, X, Y, H, K, O, D;
int infinity = 999999;
int adj[501][501];
int main() {
    while(true) {
        cin >> N >> E;

        for(int i=1; i<=N; i++)
            for(int j=1; j<=N; j++)
                adj[i][j]=infinity;


        for(int i=0; i<E; i++) {
            scanf("%d%d%d", &X, &Y, &H);
            X++;Y++;
            adj[X][Y]=H;
        }

        for(int k=1; k<=N; k++)       // Floyd again... uh!!
            for(int i=1; i<=N; i++)
                if( i!=k && adj[i][k]<infinity)
                    for(int j=1; j<=N; j++)
                        if(adj[i][j] > adj[i][k]+adj[k][j])
                            adj[i][j]=adj[i][k]+adj[k][j];


        cin >> K;
        int S[K];
        for(int i=0; i<K; i++) {
            cin >> D;
            S[i] = D+1;
        }

        int smin = infinity;
        for(int O=1; O<=N; O++) {
            int s = 0;
            cout << " " << O-1 << ": ";
            for(int i=0; i<K; i++) {
                D = S[i];
                cout <<adj[O][D]<<  " + ";
                if(adj[O][D]!=infinity){
                    s+=adj[O][D];
                }
            }
            if(!s)s = infinity;
            cout << s << endl;
            if(smin>s)smin=s;
        }
        cout << " : " <<smin << endl;
    }
    return 0;
}

/*

12 16
1 0 3
2 1 3
3 2 3
5 0 3
8 0 3
0 1 6
1 2 6
0 5 6
2 3 7
0 8 8
3 4 4
2 10 4
5 6 4
5 7 7
5 11 4
8 9 5
6
4
10
6
7
11
9

*/

