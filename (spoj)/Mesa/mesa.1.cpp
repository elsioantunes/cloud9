// Mesa da Sra Montagny!
// http://br.spoj.com/problems/MESA/     (grafo bipartido)
// Algoritmo: detecção de bipartissão de grafo (ciclos ímpares) usando BFS
// Relacionados:
//      http://br.spoj.com/problems/OBIDOMIN/  (mais difícil)
//      http://br.spoj.com/problems/GINCAN11/  (mais facil)
// 		http://br.spoj.com/problems/ENERGIA/   (beem mais facil)
#include <iostream>
#include <stdio.h>
using namespace std;

int m, n, x, y, t=1;
int *adj, *v;

bool dfs(int j, int c){
    v[j] = 1-c; 
    for(int i=0;i<n;i++)
        if(adj[i*n+j]){
            if(v[i]==1-c) return false;
            if(v[i]==-1 && !dfs(i,1-c)) return false;
        }
    return true;
}

bool bip(){
    for(int i=0;i<n;i++)
        if(v[i]==-1 && !dfs(i, 0)) 
            return false;
    return true;
}

int main(){

    while(cin >> n >> m){
        adj = new int[n*n];
        v = new int[n];
        
        for(int i=0;i<n*n;i++)
            adj[i] = 0;
        
        for(int i=0;i<n;i++)
            v[i] = -1;
        
        for(int i=0;i<m;i++){
            scanf("%d %d", &x, &y);
            x--;y--;
            adj[x*n+y]=1;
            adj[y*n+x]=1;
        }

        cout << "Instancia " << t++ << endl;
        cout << (bip()?"sim":"nao") << endl;
        cout << endl;
    }
}
