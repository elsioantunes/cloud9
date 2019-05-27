// PA, Lista 1
// problema 09 Primos
#include <iostream>
using namespace std;
int main() {
    int a, b, v=0;
    cin >> a >> b;
    if(a>0 && a<b)
        for(int i=a; i<=b; i++){
            bool p = true;
            for(int j=2; j*j<=i; j++)
                if(i%j==0) p = false;
            if(p && i>1) {
                if(v++) cout << ", ";
                cout << i;
            }
        }
    return 0;
}


