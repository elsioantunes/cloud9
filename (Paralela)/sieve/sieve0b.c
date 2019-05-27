#include <stdio.h>
#include <stdlib.h>

#define T unsigned long
#define B char    
#define print(a) printf("%zu ", a)
#define prints(s) printf("%s", s)
#define endl printf("\n");
#define tb printf("\t");
#define isprime(p) !buf1[p]
    
T SQR(T n){
    T menor, maior;
    if(n < 0) n = 0;
    if(n < 2) return n;
    menor = SQR(n >> 2) << 1;
    maior = menor + 1;
    if(maior * maior > n) 
        return menor;
    else
        return maior;
}


int GCD(T a, T b){
    return b == 0? a: GCD(b, a % b);
}


    
int main(int argc, char** argv){
    T i, j, f, w, m, w2, q, count = 0, n = atol(argv[1]);
    T sqr = SQR(n);
    int debug = atol(argv[2]);
    
    B* buf1 = (B*) calloc(sqr+1, sizeof(B)); if(buf1 == NULL) {printf("Deu ruim pra alocar %d MBs", (int)sqr/1000000);};
    B* buf2 = (B*) calloc(n+1,   sizeof(B)); if(buf2 == NULL) {printf("Deu ruim pra alocar %d MBs", (int)n/1000000);};
    
    
    for(i = 5, w2 = 2; i <= sqr; i+=w2, w2= 6-w2){
        if(!buf2[i]){
            
            if(debug){
                print(i);
                prints("::");
                //print(i*j);
                tb;
            }
            if(0){
                for(j = i; j <= n/i; j +=2){
                    
                    
                    //if (GCD(j, 210) != 1) continue;
                    if(j%3==0) continue;
                    
                    
                    buf2[i*j] = 1;
                    if(debug){
                        print(j);
                        //print(i*j);
                        tb;
                    }
                }
                if(debug) endl;

            }else{
                // equivalente a... 
                for(j = i*i; j <= n; j += 2*i)
                    buf2[j] = 1;
            }
            
            
        }
        //if(debug) endl;
    }    
    
        /*
        for(f = 5,w = 2; f <= n/5; f += w, w = 6-w){
            if(f >= i && i*f <= n) {
            
            if(!buf1[i]) {

            buf2[i*f] = 1;
                
            }}
        }
        */

        
    if(0)
    for(w = 2; 3 * w - w % 2 - 1 < n; w ++){
        i = 3 * w - w % 2 - 1;
        if(!buf2[i]){ 
            //print(i);
            count++;
       }
    }   
    
    else
    for(i = 5; i < n; i++){
        m = i * i % 30;
        if(m == 1 || m == 19)
            if(!buf2[i])
                count++;
    }
            
        
    endl;
        
    
    /*
    */

    print(count+3);
    endl;
    return 0;
}


/* 
    3 1000 168
    4 10000 1229
    5 100000 9592
    6 1000000 78498
    7 10000000 664579
    8 100000000 5761455        
    9 1000000000 50847534
   10 10000000000 455052511
   11 100000000000 4118054813 
   12 1000000000000 37607912018
   13 10000000000000 346065536839
*/
