// PA, Lista 1
// problema 17 Serie4
#include <iostream>
#include <math.h>
using namespace std;
int main() {
    int n, x = 1, y = 1, t = 1;
    double s = 0;
    while(x<=100){
        s += (double)x/(y*y*t);
        x ++;
        y ++;
        t *= -1;
    }
    cout << s << endl;
    return 0;
}


