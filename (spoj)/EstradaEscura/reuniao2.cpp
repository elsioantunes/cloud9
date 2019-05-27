// http://br.spoj.com/problems/REUNIAO2/
// Historinha: Caminhoneiros de várias cidades precisam se encontrar, qual seria o menor trajeto total?
// Algoritmo: Busca do centroide do grafo por Floyd Warshall. 
//            Pega o menor valor entre os maiores valores de cada linha. 
//            Também dá pra fazer por desfolhamento, 
//            mas (ainda) não sei como seria com grafos valorados.
// similar: 
//      http://br.spoj.com/problems/SUPERMER/ 
//      http://br.spoj.com/problems/DENGUE/

#include <iostream>
using namespace std;

int main() {
    int m, n, x, y, p;
    cin >> m >> n;
    int M[m][m];
    int inf = m*m;
    for(int i=0;i<m;i++)
        for(int j=0;j<m;j++)
            M[i][j] = inf;

    for(int i=0;i<n;i++){
        cin >> x >> y >> p;
        M[x][y] = p;
        M[y][x] = p;
    }

    for(int k=0;k<m;k++)       // Floyd Warshall, uh!
        for(int i=0;i<m;i++)
            for(int j=0;j<m;j++)
                M[i][j] = min(M[i][j], M[i][k]+M[k][j]);

    int r = inf;
    for(int i=0;i<m;i++){
        int s = 0;
        for(int j=0;j<m;j++)
            s = max(s, M[i][j]);
        r = min(r, s);
    }
    cout << r << endl;
    return 0;
}
