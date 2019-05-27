//br.spoj.com/problems/CALCU11/
#include <iostream>
#include <stdio.h>
using namespace std;
int main() {
    int N, D;
    double n = 1, d = 1; // precisou ser double.
    short buf[10];
    char C;
    for(int i=0; i<10; i++) buf[i]=0;
    scanf("\n%d", &N);
    for(int i=0; i<N; i++) {                    //
        scanf("\n%d %c", &D, &C);               // sistema de histograma
        if(C=='*') buf[D]++;                    // pra simplificar frações
        else buf[D]--;                          //
    }                                           // o spoj não aceitou sem isso.
    for(int i=2; i<10; i++) {                   //
        D = buf[i];                             //
        if(D>0) for(int j=0; j<D; j++)n *= i;
        if(D<0) for(int j=0; j<-D; j++)d *= i;
    }
    unsigned int r = n/d;  // precisou ser uint.
    cout << r << endl;
    return 0;
}
