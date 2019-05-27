// PA, Lista 1
// problema 18 Serie5
#include <iostream>
#include <math.h>
using namespace std;
int main() {
    int n, x = 1000, y = 1, t = 1;
    double s = 0;
    while(y<=1000){
        s += (double)x/(y*t);
        x -=3;
        y ++;
        t *= -1;
    }
    cout << s << endl;
    return 0;
}


