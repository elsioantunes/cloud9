#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define T double
#define print(a,b) printf("%d\t%.4f ", (int)(a), (b))
#define endl printf("\n")
#define tb printf("\t")
#define hr printf("\n-----------------------------\n")
#define dot printf(".")
#define hashtag printf("#")
#define sep printf("| ")
#define nan printf(". ")
#define printtb(s) print((s)); tb


int main(){
    double a, b = 7;
    double c;
    int i;

    for(a = 1; a < b/2; a++){
        c = ((a/b)*log(b/a) + ((b-a)/b)*log(b/(b-a)))/log(2);
        print(a, c); endl;
    }
    
    return 0;
}