// Sequências de Röntgen
// http://br.spoj.com/problems/RONTGEN/
// By Elsio
#include <iostream>
#include <sstream>
using namespace std;
int main() {
    int N, n;
    cin >> N;
    for(int i=0; i<N; i++) {
        string s;
        cin >> s >> n;
        for(int i=0; i<=n; i++) {
            cout << s << endl;
            char c = s[0];
            int d = 1;
            ostringstream ss;
            for(int i=1; i<=s.length();i++) {
                if(s[i]==c){
                    d++;
                }else {
                    ss << d << c;
                    d = 1;
                    c = s[i];
                }
            }
            s = ss.str();
        }
        cout << endl;
    }
    return 0;
}
