// PA, Lista 1
// problema 15 Serie2
#include <iostream>
#include <math.h>
using namespace std;
int main() {
    int n, x = 2, y = 20;
    double s = 0;
    while(y){
        s += (double)x/y;
        x *= 2;
        y --;
    }
    cout << s << endl;

    return 0;
}


