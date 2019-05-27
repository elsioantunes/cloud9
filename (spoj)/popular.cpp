// http://br.spoj.com/problems/POPULAR
// By Elsio
#include <iostream>
using namespace std;
int main() {
    while(true) {
        int n, d;
        cin >> n;
        if(!n)break;
        int buf[n];
        for(int i=0; i<n; i++)buf[i]=0;
        for(int i=0; i<n; i++)
            for(int i=0; i<n; i++) {
                cin >> d;
                if(d)buf[i]++;
            }
        for(int i=1; i<n; i++)
            buf[0] = max(buf[0], buf[i]);
        cout << buf[0] << endl;
    }
    return 0;
}
