#include <iostream>
#include <stdio.h>
using namespace std;

int V,T,m,n=0;
int bit[] = {50,10,5,1};
int main(){
    while(1){
        scanf("%d",&V);
        if(V==0)break;
        printf("Teste %d\n",++T);
        for(int i=0;i<4;i++){
            n = bit[i];
            m = V/n;
            printf("%d ",m);
            V -= m*n;
        }
        printf("\n");
        printf("\n");
    }
    return 0;
}
