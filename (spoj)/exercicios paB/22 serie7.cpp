// PA, Lista 1
// problema 22 serie7
#include <iostream>
#include <math.h>
using namespace std;
int main() {
    int n, x = 25, y = 1, t = 1;
    double w, s = 0;
    cin >> w;
    while(--x){
        s += (double)t*pow(w,x)/y;
        y ++;
        t *= -1;
    }
    cout << s << endl;
    return 0;
}


