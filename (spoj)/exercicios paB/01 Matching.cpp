// PA, Lista 1
// problema 1 - String-matching
#include <iostream>
#include <string>
using namespace std;
int main() {
    string T, P;
    int n, m, s;
    cin >> T >> P;
    n = T.length();
    m = P.length();
    while(s<=n-m){
        int j = m-1;
        while (j>0 && P[j]==T[s+j])
            j -= 1;
        if(!j)
            cout << "Padrao ocorre na posicao " << s << endl;
        s++;
    }
    return 0;
}


