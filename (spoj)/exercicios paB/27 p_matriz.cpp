// PA, Lista 1
// problema 27 p_matriz
#include <iostream>
using namespace std;
int main() {
    int m, a, n, k;
    cin >> m >> k >> n;
    int A[m][k], B[k][n], C[m][n];

    for(int i=0; i<m; i++)
        for(int j=0; j<k; j++) {
            cin >> a;
            A[i][j] = a;
        }

    for(int i=0; i<k; i++)
        for(int j=0; j<n; j++) {
            cin >> a;
            B[i][j] = a;
        }

    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            C[i][j] = 0;
            for(int h=0; h<k; h++)
                C[i][j] += A[i][h] * B[h][j];
            cout << C[i][j] << "\t";
        }
        cout << endl << endl;
    }

    return 0;
}


