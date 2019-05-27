// Jogo da Memória
// http://www.urionlinejudge.com.br/repository/UOJ_1928.html
// solução da maratona usando Lowest Common Ancestor:
// http://olimpiada.ic.unicamp.br/extras/solucoes/2014f2p1_memoria/abella.cpp
// Implementacao usando Floyd Wharshal
//       por ser O(n³) nao passou no URI

#include <iostream>
using namespace std;

int main() {
  int n, a, b, c, result = 0;

  cin >> n;

  int *query = new int[2*n];
  int **adj = new int*[n];

  for(int i=0; i<n; i++){
    query[i]=0;
    adj[i] = new int[n];
    for(int j=0; j<n; j++)
      adj[i][j]=i==j?0:0x07ffffff;
  }

  for(int i=0; i<n; i++){
    cin >> c; c--;
    query[2*c+1] = query[2*c];
    query[2*c] = i;
  }
  
  for (int i=0;i<n-1;i++){
    cin >> a >> b; a--, b--;
    adj[a][b]=1;
    adj[b][a]=1;
  }
  
  if(n<=500)
  for(int k=0; k<n; k++)            // Floyd Warshall
    for(int i=0; i<n; i++)
      for(int j=0; j<n; j++)
        adj[i][j] = min(adj[i][j], adj[i][k]+adj[k][j]);

  
  for(int i=0; i<n; i++)           // soma
    result += adj[query[2*i]][query[2*i+1]];

  cout << result << endl;
  return 0;
}
