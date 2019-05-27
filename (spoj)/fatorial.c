#include <stdio.h>
#include <stdlib.h>

int fatorial(x){
   if (x<2) return 1;
   if (x<3) return x;
   return fatorial(x-1)*x;
}

int main(){
    int n;
    scanf("%d",&n);
    //if(n<0 || n>12) return 0;
    printf("%d\n",fatorial(n));
    return 0;
}
