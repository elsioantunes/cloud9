// PA, Lista 1
// problema 19 Serie6
#include <iostream>
#include <math.h>
using namespace std;
int main() {
    int n, x = 480, y = 10, t = 1;
    double s = 0;
    cin >> n;
    while(--n){
        s += (double)x/(y*t);
        x -=3;
        y ++;
        t *= -1;
    }
    cout << s << endl;
    return 0;
}


