#include <stdio.h>
#include <stdlib.h>
#define wheel(i) (3*(i+2)-(i+2)%2-1)
#define antiwheel(i) ((i+2)/3-2)
#define T unsigned long
#define print(a) printf("%zu ", (a))
#define endl printf("\n")
#define tb printf("\t")
#define hr printf("\n-----------------------------\n")
#define dot printf(".")
#define hashtag printf("#")
#define sep printf("| ")
#define nan printf(". ")
#define printtb(s) print((s)); tb

typedef struct{
    int *list;
    int count;
} Factor;

void factor(T n){
    T i;
    int f[300], k=0;

    for(i = 1; i*i < n; i++){
        if (n % i) continue;
        n = n/i;
        if (i == 1) continue;
        f[k++] = i;
        f[k++] = n/i;
    }
    
    for(i = 0; i < k; i++){
        print((T)f[i]);
    }
    
    
}

int main(){
    T i;
    for(i=0; i<60; i++){
        //if(wheel(i) % 5) continue;
        print(i);tb;
        print(wheel(i)); tb;

        tb;
        print(i+60*1);tb;
        print(wheel(i+60*1)); tb;

        tb;
        print(i+60*2);tb;
        print(wheel(i+60*2)); tb;

        tb;
        print(i+60*3);tb;
        print(wheel(i+60*3)); tb;

        tb;
        print(i+60*4);tb;
        print(wheel(i+60*4)); tb;

        //factor(wheel(i));
        //factor(i);
        endl;
    }
    return 0;    
}