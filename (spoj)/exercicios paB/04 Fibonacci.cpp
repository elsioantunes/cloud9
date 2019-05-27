// PA, Lista 1
// problema 4 Fibonacci
#include <iostream>
using namespace std;
int main() {
    int n, f = 0, a = 0, b = 1;
    cin >> n;
    while(--n) {
        a = b;
        b = f;
        f = a + b;
        cout << f;
        if (n>1)cout << ", ";
    }
    return 0;
}


