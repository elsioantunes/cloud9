#include <iostream>
using namespace std;
int main() {
    int a,b,n,teste=1;
    while(true) {
        cin >> a >> b;
        if(a==0)break;
        int fila[10001],x=0,s=0,tmin=201,tmax=-201;
        for(int i=0; i<a; i++) {
            cin >> n;
            fila[x++] = n;
            if(i<b) {
                s += n;
            } else {
                s -= fila[x-b-1];
                s += fila[x-1];
            }
            if(i>b-2) {
                int tm = s/b;
                if(tm>tmax)tmax=tm;
                if(tm<tmin)tmin=tm;
            }
        }
        cout << "Teste " << teste++ << endl;
        cout << tmin << " " << tmax << endl;
        cout << endl;
    }
    return 0;
}
