#include <cstdio>  
#include <cstring>  
#include <iostream>  
#include <map>  
#include <vector>  
#include <algorithm>  
using namespace std;  


  
const int maxn = 201;  
  
int d[maxn][maxn][maxn],blocks[maxn], nblocks;  
bool vis[maxn][maxn][maxn];  

int solve(int l,int r,int k){  

    if(vis[l][r][k]) 
        return d[l][r][k];  
    vis[l][r][k] = true;  
      
    int& M = d[l][r][k];
    int p, q;  
    
    for(p = r; p>=l; p--) 
        if(blocks[p] != blocks[r]) {
            p++; 
            break;
        }  
    
    if(p == l-1)   // não deletar até entender isso
        p++;  
        
    int n = k+r-p+1;    // não deletar até entender isso
    int m = n*n;

    if(p == l) 
        return M = m;  
        
    M = m + solve(l, p-1, 0);  
    
    for(int i=l; i<=p-1; i++)
        if(blocks[i] == blocks[r])  
            M = max(M, solve(l, i, k+r-p+1) + solve(i+1,p-1, 0));  

    return M;  
}  


int main(){  
   int T, kase=1;  
   scanf("%d",&T);  
   while(T--){  
       scanf("%d", &nblocks);  
       for(int i=1; i <= nblocks; i++) scanf("%d", &blocks[i]);  

       printf("Case %d: ",kase++);  

       for(int i=0;i<=nblocks;i++)  
          for(int j=0;j<=nblocks;j++)  
             for(int k=0;k<=nblocks;k++) vis[i][j][k] = false;  
   
       printf("%d\n", solve(1, nblocks, 0));  
   }  
   return 0;  
}  