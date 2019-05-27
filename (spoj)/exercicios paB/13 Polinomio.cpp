// PA, Lista 1
// problema 13 Polinomio
#include <iostream>
#include <math.h>
using namespace std;
int main() {
    int n;
    double x, a, s = 0;
    cin >> n >> x;
    for(int i=0; i<n; i++){
        cin >> a;
        s += a*pow(x,i);
    }
    cout << "O valor de P(x) e: " << s << endl;
    return 0;
}


