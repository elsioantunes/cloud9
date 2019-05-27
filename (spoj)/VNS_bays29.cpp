// Caixeiro Viajante método VNS
// instância: [bays29 : 2020]  http://www.iwr.uni-heidelberg.de/groups/comopt/software/TSPLIB95/tsp/
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

int n;


void swp(int a, int b, int *ord) {
    if(a>b) {
        int tmp = a;
        a = b;
        b = tmp;
    }
    while(a<b) {
        int tmp = ord[a];
        ord[a] = ord[b];
        ord[b] = tmp;
        a++;b--;
    }
}

void imprime(int *ord, int s){
    cout << "f(s) = " << s << ";   s = {";
    for(int i=0;i<n;i++){
        cout << ord[i];
        if(i<n-1) cout << " ";
    }
    cout << "}\n\n";
}

int main() {
    n = 29;
int ord[n];
int adj[n][n];
    srand(time(NULL));








    int p, q = 0 ;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++) {
            cin >> p;
            adj[i][j] = p;
            adj[j][i] = p;
        }

    for(int i=0; i<n; i++) ord[i] = i;






    /********************************************************
    ********************************************************/

    int inf = 0x7fffffff;
    int s = inf;
    int s1 = inf;

    while(true) {
        s1 = inf;
        int k = 0;
        while(true) {
            int rnd1 = rand()%(n-1)+1;
            int rnd2 = rand()%(n-1)+1;
            swp(rnd1,rnd2,ord);

            int s2 = 0;
            for(int i=0; i<n-1; i++)
                s2 += adj[ord[i]][ord[i+1]];
            s2 += adj[ord[n-1]][ord[0]];

            if(s2<s1) {
                s1 = s2;
                k = 0;
            } else {
                swp(rnd1,rnd2,ord);
                if(k++>3000) break;
            }
        }

        if(s1<s){
            s = s1;
            imprime(ord, s);
        }
    }

    return 0;
}


