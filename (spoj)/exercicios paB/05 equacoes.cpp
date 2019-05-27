// PA, Lista 1
// problema 6 equacoes
#include <iostream>
using namespace std;
int main() {
    int a, b, c, d, D, u, v;
    double x, y;
    cin >> a >> b >> c >> d >> u >> v;
    D = a*d - b*c;
    if(D){
        x = (d*u-b*v)/D;
        y = (a*v-c*u)/D;
        cout << x << ", " << y << endl;
    }else{
        cout << "ad - bc precisa ser diferente de zero" << endl;
    }
    return 0;
}


