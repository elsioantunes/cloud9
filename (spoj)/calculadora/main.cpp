//br.spoj.com/problems/CALCU11/
#include <iostream>
#include <stdio.h>
using namespace std;

int main() {
    int N, D;
    double n = 1, d = 1;
    short buf[10];
    char C;
    for(int i=0; i<10; i++) buf[i]=0;
    scanf("\n%d", &N);

    for(int i=0; i<N; i++) {
        scanf("\n%d %c", &D, &C);
        if(C=='*') n *= D;
        else n /= D;
    }
    unsigned int r = n;
    cout << r << endl;
    return 0;
}
