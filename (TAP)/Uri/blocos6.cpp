#include <iostream>
#include <cstring>
#include <cstdio>
#define buf(a,b,c) PD[a][b][c]
#define vis(a,b,c) vis[a][b][c]
#define zera(a) memset(a, 0, sizeof(a));
using namespace std;
int caso, ncasos, nblocks, block, nbrocks, brock;
int PD[205][205][205], blocks[205], histo[205];
bool vis[205][205][205];

/*##############################################################*/

int esolve(){
    
}

int solve(int l, int r, int n){
    // teste
    
    if(l>r) return 0;
    if(vis(l, r, n)) return buf(l, r, n);
    int M, m = n*n;
    
    
    M = m + solve(l, r-1, 0);
    
    for(int i = l; i < r; i++)
        if(blocks[i] == blocks[r])
            M = max(M, solve(l, i, n+1) + solve(i+1, r-1, 0));
            
    vis(l, r, n) = true;
    buf(l, r, n) = M;
    return M;
}

/*##############################################################*/

int solve_simples(){
    int i, soma = 0;
    zera(histo);
    for(i = 0; i < nblocks; i++) histo[blocks[i]]++;
    while (--i) soma += histo[i]*histo[i];
    return soma;
}

/*##############################################################*/
void entrada(){
    cin >> nblocks;
    for(int i = 1; i <= nblocks; i++){
        cin >> block;
        blocks[i] = block;
    }
}




void saida(){  
    zera(vis);
    cout << "Case " << caso << ": " << solve(1, nblocks, 0) << endl;
    
    /*
    int j, l, r;
    for (j = 0; j < nblocks; j++) {
        for (l = 0; l + j < nblocks; l++) {
            r = l + j;
            cout << buf(l, r, 1) << " ";
        }
        cout << endl;
    }
    */

    
    //cout << "Case " << caso << ": " << solve_simples() << endl;
}

/*##############################################################*/

int main(){
    zera(PD);
    cin >> ncasos;
    for(caso = 1; caso <= ncasos; caso++){
        entrada();
        saida();
    }
    return 0;
}

