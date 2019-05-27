//http://uva.onlinejudge.org/external/3/369.html
#include <iostream>
#include <stdio.h>
using namespace std;
int main() {
    int M, N;
    long buf[200][200];
    for(int i=0;i<200;i++) {
        for(int j=0; j<i+1; j++) {
            buf[i][j] = 0;
            if(i==j||j==0)buf[i][j] = 1;
            if(i) buf[i][j] = buf[i-1][j]+buf[i-1][j-1];
        }
    }
    while(1){
        scanf("%d %d",&N,&M);
        if(N==0||M==0) break;
        cout << N << " things taken " << M << " at a time is " << buf[N][M] << " exactly." << endl;
    }
    return 0;
}
