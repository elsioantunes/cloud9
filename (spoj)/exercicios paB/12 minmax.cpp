// PA, Lista 1
// problema 12 minmax
#include <iostream>
using namespace std;
int main() {
    int m = 0x7fffffff;
    int M = 0x7fffffff+1;
    int n, a;
    cin >> n;
    for(int i=0; i<n; i++){
        cin >> a;
        if(a<m)m=a;
        if(a>M)M=a;
    }
    cout << "O maximo eh "<< M << " e o minimo eh " << m << endl;
    return 0;
}


