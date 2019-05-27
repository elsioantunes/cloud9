#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

int blocks[210],len[210],dp[210][210][210];
int sum[210], su[210];

inline int sq(int x){return x*x;}


int main(){
    int T,time;
    scanf("%d",&T);
    for(time=1;time<=T;++time){
        int n = 0, m, t1;
        scanf("%d", & m);

        for (int i = 1; i <= m; ++i) {
            scanf("%d", & t1);
            if (t1 == blocks[n])
                ++len[n];
            else {
                blocks[++n] = t1;
                len[n] = 1;
            }
        }

        for (int i = 1; i <= n; ++i) {
            m -= len[i];
            sum[i] = m;
        }

        memset(dp, 0, sizeof(dp));

        int i, l, r, re;
        for (i = 0; i < n; i++) {
            for (l = 1; l + i <= n; l++) {
                r = l + i;

                re = sum[r];

                for (int t = 0; t <= re; t++) {
                    dp[l][r][t] = dp[l][r - 1][0] + sq(t + len[r]);
                }

                for (int k = l; k < r; k++) {
                    if (blocks[k] == blocks[r]) {

                        for (int t = 0; t <= re; t++) {
                            dp[l][r][t] = max(
                                dp[l][r][t],

                                dp[l][k][len[r] + t] + dp[k + 1][r - 1][0]
                            );
                        }
                    }
                }
            }
        }
        printf("Case %d: %d\n",time,dp[1][n][0]);
    }
    return 0;
}