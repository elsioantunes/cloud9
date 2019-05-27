#include <iostream>
using namespace std;

int main() {
    int m, n, x, y, p;
    cin >> n >> m;
    cout << "n = " << n << endl;
    cout << "m = " << m << endl;
    int adj[500][500];
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            adj[i][j] = -1;
        }
    }
    
    for(int i=0;i<m;i++){
        cin >> x >> y >> p;
        x--;y--;
        adj[x][y]=p;
        adj[y][x]=p;
    }
    
    cout << "adj = [";
    for(int i=0;i<n;i++){
        cout << (i?"], [ ":"[");
        for(int j=0;j<n;j++){
            cout << (j?", ":"") << adj[i][j];
        }
    }
    cout << "]];" << endl;
    return 0;
}
