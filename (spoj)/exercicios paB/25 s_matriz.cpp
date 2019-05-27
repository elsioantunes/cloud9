// PA, Lista 1
// problema 25 s_matriz
#include <iostream>
#include <math.h>
using namespace std;
int main() {
    int m, n, a, b;
    cin >> m >> n;
    int adj[m][n];

    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            cin >> a;
            adj[i][j] = a;
        }
    }

    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            cin >> a;
            adj[i][j] += a;
        }
    }

    cout << endl;
    cout << endl;
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            cout << adj[i][j] << "\t";
        }
        cout << endl;
        cout << endl;
    }
    return 0;
}


