#include <iostream>
using namespace std;

int main() {
    int k, len, T=1;
    int a,b,o;
    while(1) {
        cin >> a >> b;
        if(a==0)break;
        int buf[a];
        int buf2[a];
        for(int i=0; i<a; i++) {
            cin >> buf[i];
        }
        for(int j=0; j<b; j++) {
            cin >> len >> o;
            k = 0;
            int a[len];
            for(int i=0; i<len; i++) {
                cin >> a[i];
                if(o==a[i]) {
                    buf2[k++]=buf[i];
                }
            }
            for(int i=0; i<k; i++) {
                buf[i] = buf2[i];
            }
        }
        cout << "Teste " << T++ << endl << buf[0] << endl << endl;
    }
    return 0;
}
