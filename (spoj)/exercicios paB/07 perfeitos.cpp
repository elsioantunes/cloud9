// PA, Lista 1
// problema 07 perfeitos
#include <iostream>
using namespace std;
int main() {
    int m, n = 1;
    cin >> m;
    while(--m) {
        int s = 0;
        for(int i=1; i<=n/2; i++)
            if(n%i==0)s+=i;
        if(s==n) cout << n << endl;
        n ++;
    }
    return 0;
}


