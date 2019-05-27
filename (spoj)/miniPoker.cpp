#include <iostream>
#include <stdio.h>
using namespace std;
int main() {
    int m, n, b[5], bit, p,tmp, r;
        cin >> n;
        for(int i=1;i<n+1;i++){
            m = 5;while(m--)cin >> b[m];
            for(int i=0; i<4; i++)
                for(int j=i+1; j<5; j++)
                    if(b[i]>b[j]) {
                        tmp = b[i];
                        b[i] = b[j];
                        b[j] = tmp;
                    }
            bit = 0;
            p = 1;
            m = 4;while(m--) {
                bit *=2;
                if(b[m+1]==b[m])bit++;
                p *= b[m+1]-b[m];
            }
            if(p==1)r = 200+b[0];
            else if(bit==7 ||bit==14)r = 180+b[1];
            else if(bit==11)r = 160+b[0];
            else if(bit==13)r = 160+b[4];
            else if(bit==3||bit==6||bit==12)r = 140+b[2];
            else if(bit==5||bit==9||bit==10)r = 20+3*b[3]+2*b[1];
            else if(bit==1)r = b[0];
            else if(bit==2)r = b[1];
            else if(bit==4)r = b[2];
            else if(bit==8)r = b[3];
            else r = bit;

            cout << "Teste " << i << endl;
            cout << r << endl;
            cout << endl;
        }
    return 0;
}
