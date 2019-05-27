// PA, Lista 1
// problema 6 Fatores
#include <iostream>
using namespace std;
int main() {
    int n;
    cin >> n;
    cout << "Fatores de x: ";
    for(int i=1;i<=n/2;i++)
        if(n%i==0) cout << i << " ";
    return 0;
}


