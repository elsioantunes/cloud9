#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
    int p;
    signed long int n,i,sqr;
    while (1){
        scanf("%li",&n);
        //if(n==0)break;
        if(n<0) n=-n;

        sqr = n;
        if(n>100){
            sqr = 100;
            while(sqr*sqr<n){
                sqr++;
            }
        }

        p = 1;
        for(i=2;i<sqr;i++){
            if((n%i)==0)p=0;
        }
        if(p==1 && abs(n)>1) printf("%s\n","sim");
            else  printf("%s\n","nao");


        break;
    }

    return 0;
}
