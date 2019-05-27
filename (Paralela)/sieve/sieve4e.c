#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Macros que me ajudam a marcar a tabela usando bits. 
#define getbit(buf, bit) ((buf)[bit >> 3] &  (1 << ((bit)%8)))
#define setbit(buf, bit)  (buf)[bit >> 3] |= (1 << ((bit)%8))

// Macros que me ajudaram a testar outros types
#define T unsigned long
#define C unsigned char

// Macros para implementar wheels. Facil entender, difícil implementar.
#define wheel(i) (3*(i+2)-(i+2)%2-1)
#define antiwheel(i) ((i+2)/3-2)
#define next(i) (2*i-(2*i+1)/3)

// debug
#define print(a) printf("%zu\n", a)
#define prints(s) printf("%s", s)
#define endl printf("\n");
#define tb printf("\t");




//Funcao que, dado um primo, risca o composto numa linha de tamanho (high - low)
void markBlock(C* buf2, T low, T high, T prime){
	T first;
	T i, j, d, dprime;
	
	first = low - low % prime;
	if(first < low) first += prime;
	if(first % 2 == 0) first += prime;
	
	dprime = 2*prime; //10
	d = dprime - next(prime); // 10 - 7 = 3
	
	for(j = first-low; wheel(j) <= high-low; j += prime)
	    setbit(buf2, j);
	    
};


void limits(T *low, T *high, int id, int p, T n, T sqr){
    T blockSize = (n-sqr)/p;
    
    (*low) = sqr + blockSize*id + 1;
    (*high) = *low + blockSize - 1;
    
    if(id == p-1) (*high) += (n-sqr) % p;
    if((*low) % 2 == 0) (*low) ++;
    if((*high) % 2 == 0) (*high) --;
}


T Sieve(T n, int id, int p, T low, T high){
    T i, j, d, prime, dprime, count = 0;
    T sqr = sqrt((double)n);
    T bufsize, bufsize2;
    
    bufsize = antiwheel(sqr);
    bufsize2 = antiwheel(high - low);
    
    
    C* buf1 = (C*) calloc(bufsize/8, sizeof(C));
    C* buf2 = (C*) calloc(bufsize2/8, sizeof(C));
    
    

    for(i = 0; i <= antiwheel(sqr); i++){
        if(!getbit(buf1, i)) {
            prime = wheel(i);
            dprime = 2*prime;
            d = dprime - next(prime);
            for(j = i + dprime - d; wheel(j) + dprime < n; j += dprime){
                setbit(buf1,j);
                setbit(buf1,j+d); 
            }
            
            if(wheel(j) < n)
                setbit(buf1, j);

            if(id == 0) 
                count++;
    
            markBlock(buf2, low, high, prime);
            
        }
    }
    
    for(i = 0; i < bufsize2; i++){
        if(!getbit(buf2, i)){
            count++;
            printf("%d :: %zu\n", id, wheel(i + bufsize2));
        }
    }
    endl;

    free(buf1);
    free(buf2);
    return count;
}

int main(int argc, char** argv){
	T n = atoll(argv[1]);
    T count = 0, globalSum = 0;
    T low, high;
    T sqr = sqrt((double)n);
    
    int id, p;
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    MPI_Barrier(MPI_COMM_WORLD);
    
    limits(&low, &high,  id, p, n, sqr);

    count = Sieve(n, id, p, low, high);
    

    MPI_Reduce(&count, &globalSum, 1, MPI_UNSIGNED, MPI_SUM, 0, MPI_COMM_WORLD);
    if(id == 0) printf("%zu\n", globalSum + 3);
    MPI_Finalize();
    return 0;
}

/* 

    lscpu:
        Arquitetura:           x86_64
        Modo(s) operacional da CPU:32-bit, 64-bit
        Byte Order:            Little Endian
        CPU(s):                4
        On-line CPU(s) list:   0-3
        Thread(s) per núcleo   1
        Núcleo(s) por soquete: 4
        Soquete(s):            1
        Nó(s) de NUMA:         1
        ID de fornecedor:      GenuineIntel
        Família da CPU:        6
        Modelo:                58
        Model name:            Intel(R) Core(TM) i5-3570 CPU @ 3.40GHz
        Step:                  9
        CPU MHz:               1605.703
        CPU max MHz:           3800,0000
        CPU min MHz:           1600,0000
        BogoMIPS:              6784.57
        Virtualização:         VT-x
        cache de L1d:          32K
        cache de L1i:          32K
        cache de L2:           256K
        cache de L3:           6144K
        NUMA node0 CPU(s):     0-3
        Flags:                 fpu vme de pse tsc msr pae mce cx8 apic sep mtrr 
                               pge mca cmov pat pse36 clflush dts acpi mmx fxsr 
                               sse sse2 ss ht tm pbe syscall nx rdtscp lm 
                               constant_tsc arch_perfmon pebs bts rep_good nopl
                               xtopology nonstop_tsc aperfmperf pni pclmulqdq 
                               dtes64 monitor ds_cpl vmx smx est tm2 ssse3 cx16
                               xtpr pdcm pcid sse4_1 sse4_2 x2apic popcnt 
                               tsc_deadline_timer aes xsave avx f16c rdrand 
                               lahf_lm epb ssbd ibrs ibpb stibp kaiser 
                               tpr_shadow vnmi flexpriority ept vpid fsgsbase
                               smep erms xsaveopt dtherm ida arat pln pts 
                               flush_l1d
        
        time mpirun -n 3 lol4c 1000000000
        50847534
        50847534
        50847534
        
        real	0m11.090s
        user	0m33.084s
        sys	0m0.072s
        
        time mpirun -n 2 lol4c 1000000000
        50847534
        50847534
        
        real	0m9.033s
        user	0m17.944s
        sys	0m0.076s
        
        
        




    ## cloud9 ##
    
    3 1000 168        0.68s
    4 10000 1229        0.67s
    5 100000 9592        0.63s
    6 1000000 78498        0.68s
    7 10000000 664579        0.77s
    8 100000000 5761455        1.33s
    9 1000000000 50847534        17.68s user, 14.3 real (!)
   10 10000000000 455052511       
   11 100000000000 4118054813     
   12 1000000000000 37607912018   
   13 10000000000000 346065536839 
*/
