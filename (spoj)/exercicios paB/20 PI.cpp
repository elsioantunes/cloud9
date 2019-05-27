// PA, Lista 1
// problema 20 PI
#include <iostream>
#include <math.h>
using namespace std;
int main() {
    int n, x = 4, y = 1, t = 1;
    double s = 0;
    cin >> n;
    while(--n){
        s += (double)x/(y*t);
        y += 2;
        t *= -1;
    }
    cout << s << endl;
    return 0;
}


