// PA, Lista 1
// problema 08 Valor aproximado de e^x
#include <iostream>
using namespace std;
int main() {
    int n, f = 1;
    double s = 0, x, y = 1;
    cin >> n >> x;
    for(int i=0; i<n; i++){
        s += y/f;
        f *= i+1;
        y *= x;
    }
    printf("%f\n", s);
    return 0;
}


