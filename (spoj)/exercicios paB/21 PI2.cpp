// PA, Lista 1
// problema 21 PI2
#include <iostream>
#include <math.h>
using namespace std;
int main() {
    int n, x = 1, y = 1, t = 1;
    double s = 0;
    cin >> n;
    while(--n){
        s += (double)t/x;
        y += 2;
        x = y*y*y;
        t *= -1;
    }
    cout << pow(32*s,1.0/3) << endl;
    return 0;
}


