// PA, Lista 1
// problema 14 Serie
#include <iostream>
#include <math.h>
using namespace std;
int main() {
    int n, x = 1, y = 1;
    double s = 0;
    cin >> n;
    for(int i=0; i<n; i++){
        s += (double)x/y;
        x += 2;
        y ++;
    }
    cout << s << endl;

    return 0;
}


