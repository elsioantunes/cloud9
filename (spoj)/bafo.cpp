#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;

int i,n,c=1,r;
int a, b;
int aldo, beto;

int main(){
    while(true){
        cin >> n;
        if(n==0)break;
        a=0;b=0;i=0;
        while(i++<n){
            cin >> aldo;
            cin >> beto;
            a+=aldo;
            b+=beto;
        }

        char* r = "Beto";
        if(a>b)r = "Aldo";
        printf("Teste %d\n%s\n\n",c++,r);
    }
    return 0;
}
