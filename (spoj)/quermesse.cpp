#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;

int n,m,r,i;
int c=1;

int main(){
    while(true){
        i = 0;
        cin >> n;
        if(n==0)break;
        while(i<n){
            cin >> m;
            if(m==i+1) r=m;
            i++;
        }
        printf("Teste %d\n%d\n\n",c++,r);
    }
    return 0;
}





