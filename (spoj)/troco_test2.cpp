// http://br.spoj.com/problems/TROCO13/
// Algoritmo: subset sum
// relacionados: http://br.spoj.com/problems/TESOURO/
//               http://br.spoj.com/problems/DESCULPA/   (um pouco mais avançado)
// Video do prof Balan (UFABC) sobre esse problema:
//      https://www.youtube.com/watch?v=ehrJjRHCBvY

#include <iostream>
using namespace std;

int main() {
    int s, n, v;
    cin >> s;
    int Vs[s+1];
    for(int i=1;i<=s;i++)
        Vs[i]=0;
    Vs[0]=1;

    cin >> n;
    for(int i=0;i<n;i++){       // subset sum, uh!
        cin >> v;
        for(int j=s;j>=v;j--)
            Vs[j] |= Vs[j-v];
    }

    cout << (Vs[s]?"S":"N") << endl;
    return 0;
}


