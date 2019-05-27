// PA, Lista 1
// problema 23 serie8
#include <iostream>
#include <math.h>
using namespace std;
int main() {
    int n, x = 1, y = 15, t = 1;
    double s = 0;
    while(y*y>=1){
        s += (double)t*x/(y*y);
        x *=2;
        y --;
        t *= -1;
    }
    cout << s << endl;
    return 0;
}


