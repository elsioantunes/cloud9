// PA, Lista 1
// problema 16 Serie3
#include <iostream>
#include <math.h>
using namespace std;
int main() {
    int n, x = 37, y = 1;
    double s = 0;
    while(x){
        s += (double)(x*(x+1))/y;
        x --;
        y ++;
    }
    cout << s << endl;

    return 0;
}


