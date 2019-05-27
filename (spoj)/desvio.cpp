// br.spoj.com/problems/DESVIO/
#include <iostream>
using namespace std;
int N, M, C, K, U, V, P;
int infinity = 999999;
int adj[250][250];
int main() {
   while(true) {
      cin >> N >> M >> C >> K;
      if(N==0)break;
      for(int i=0; i<N; i++)
         for(int j=0; j<N; j++)
            adj[i][j]= infinity;
      for(int i=0; i<M; i++) {
         cin >> U >> V >> P;
         adj[U][V]=P;
         adj[V][U]=P;
      }
      for(int i=0; i<C; i++)
         for(int j=0; j<N; j++)
            if(j-i!=1)
               adj[i][j]=infinity;
               
      for(int k=0; k<N; k++)            // Floyd, uh!
         for(int i=0; i<N; i++)
            if( i!=k && adj[i][k]<infinity)
               for(int j=0; j<N; j++)
                  if(adj[i][j] > adj[i][k]+adj[k][j])
                     adj[i][j] = adj[i][k]+adj[k][j];
      cout << adj[K][C-1] << endl;
   }
   return 0;
}
