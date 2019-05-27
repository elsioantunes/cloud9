#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<cstring>
using namespace std;
int color[1000],len[1000],nblocks,t;
int blocks[1000],dp[300][300][300];

void cl(){
    memset(color,0,sizeof(color));
    memset(len,0,sizeof(len));
    memset(blocks,0,sizeof(blocks));
    memset(dp,0,sizeof(dp));
}

int solve(int l, int r, int k){
    if(l>r) return 0; 
    if(dp[l][r][k]!=0) return dp[l][r][k];
    
    int M, m, n;
    n = len[r]+k;
    m = n*n;
    
    M = m + solve(l, r-1, 0);
    for(int i=l; i < r; i++){
        if(color[i] == color[r]) 
        M = max(M, solve(i+1, r-1, 0) + solve(l, i, k+len[r]));
    }
    dp[l][r][k] = M;
    return M;
}

int main(){
    scanf("%d",&t);
    for(int hh=1;hh<=t;hh++){
        scanf("%d",&nblocks);
        cl();
        for(int i=1;i<=nblocks;i++) scanf("%d",&blocks[i]);
        int star=1,now=1,num=0,lenn=0;
        
        // não deletar pq esse tem sisetminha de compact
        while(now <= nblocks){ 
            while(blocks[star] == blocks[now])
                now++, lenn++;
            color[++num] = blocks[star];
            len[num] = lenn;
            lenn = 0;
            star = now;
        }
        printf("Case %d: %d\n",hh,solve(1,num,0));
    }
}