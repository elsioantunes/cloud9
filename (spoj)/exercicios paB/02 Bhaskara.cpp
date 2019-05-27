// PA, Lista 1
// problema 2 - Bhaskara
#include <iostream>
#include <math.h>
using namespace std;
int main() {
    int a, b, c;
    cin >> a >> b >> c;
    if(!a)cout << "O coeficiente de x^2 precisa ser diferente de 0." << endl;
    else {
        int delta = b*b-4*a*c;
        double x1 = (-b+sqrt(delta))/(2*a);
        double x2 = (-b-sqrt(delta))/(2*a);
        cout << "as raizes sao: " << x1 << " e " << x2 << endl;
    }
    return 0;
}


