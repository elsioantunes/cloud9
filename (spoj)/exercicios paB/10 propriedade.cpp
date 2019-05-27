// PA, Lista 1
// problema 10 propriedade
#include <iostream>
using namespace std;
int main() {
    for(int i=1000; i<=9999; i++){
        int x = i/100;
        int y = i - 100*x;
        if((x+y)*(x+y)==i)
            cout << "(" << x << " + " << y << ")^2 = " << i <<  endl;
    }
    return 0;
}


