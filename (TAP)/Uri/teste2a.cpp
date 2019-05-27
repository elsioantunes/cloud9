#include <cstdio>
#include <cstring>
#include <iostream>
#define buf(l,r,t) dp[l][r][t]
using namespace std;

int blocks[210],dp[210][210][210];

int main(){
    int ncasos, caso ;
    scanf("%d",&ncasos);
    for(caso = 1; caso <= ncasos; caso++){
        int nblocks = 0, t1;
        scanf("%d", &nblocks);

        for (int i = 1; i <= nblocks; ++i) {
            scanf("%d", & t1);
            blocks[i] = t1;
        }

        memset(dp, 0, sizeof(dp));
        
        int j, l, r;
        for (j = 0; j < nblocks; j++) {
            int g = 1;
            for (l = 1; l + j <= nblocks; l++) {
                r = l + j;

                if (g != buf(l, r, 0)){
                    //cout <<l << " - " ;
                    int sqra = 0, sqrb=1;
                    for (int n = 0; n <= nblocks-r; n++){ 
                        sqra += sqrb;
                        sqrb += 2;
                        buf(l, r, n) = buf(l, r-1, 0) + sqra;
                        //cout << buf(l, r, n) << " ";
                    }
                    //cout << endl;
                    g = buf(l, r, 0);
                }


                for (int i = l; i < r; i++) {
                    if (blocks[i] == blocks[r]) {
                        for (int n = 0; n <= nblocks-r; n++) {
                            buf(l, r, n) = max(
                                buf(l, r, n),
                                buf(l, i, n+1) + buf(i+1, r-1, 0)
                            );
                        }
                    }
                }
            }
        }
        printf("Case %d: %d\n", caso, buf(1, nblocks, 0));

        /*
        for (j = 0; j < nblocks; j++) {
            for (l = 0; l + j < nblocks; l++) {
                r = l + j;
                cout << buf(l, r, 0) << " ";
            }
            cout << endl;
        }
        */
    }
    return 0;
}