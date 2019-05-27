// PA, Lista 1
// problema 26 Matriz simetrica
#include <iostream>
using namespace std;
int main() {
    int m, n, a, s = 0;
    cin >> m >> n;
    if(m==n) {
        int adj[m][n];
        for(int i=0; i<m; i++)
            for(int j=0; j<n; j++) {
                cin >> a;
                adj[i][j] = a;
            }
        s = 1;
        int i = 0;
        while(i<m && s) {
            int j = i;
            while(j<n && s) {
                cout << adj[i][j] << " " << adj[j][i] << endl;
                if(adj[i][j]!=adj[j][i]) s = 0;
                j++;
            }
            i++;
        }
    } else{
        // read and ignore
        int i = n*m; while(--i) cin >> a;
    }

    if(s) cout << "Matriz e simetrica" << endl;
    else cout << "Matriz nao e simetrica" << endl;
    return 0;
}


