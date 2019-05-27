#include <iostream>
#include <stdio.h>
using namespace std;
int m, n, c=1;
int main(){
    while(true){
        cin >> n;
        if(n==0)break;
        m = 1;
        for(int i=0;i<n;i++)m *=2;
        printf("Teste %d\n%d\n\n",c++,m-1);
    }
    return 0;
}
 