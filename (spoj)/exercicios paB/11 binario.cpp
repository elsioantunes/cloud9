// PA, Lista 1
// problema 11 binario
#include <iostream>
#include <math.h>
using namespace std;
int main() {
    int n;
    cin >> n;
    int s = log(n)/log(2)+1;
    int j = s;
    int b[s];
    while(n){
        b[--j] = n%2;
        n /= 2;
    }
    for(int i=0; i<s; i++)
        cout << b[i];
    return 0;
}


