#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cstdlib>

// Macros que me ajudam a marcar a tabela usando bits. 
#define getbit(buf, bit) ((buf)[bit >> 3] &  (1 << ((bit)%8)))
#define setbit(buf, bit)  (buf)[bit >> 3] |= (1 << ((bit)%8))


/*
    Funcao que, dado um primo, risca o composto numa linha de tamanho (high - low)
*/
void markBlock(char* buf2, long int low, long int high, long int prime){
	long int j, first;
	
	first = low - low % prime;
	if(first < low) first += prime;
	if(first % 2 == 0) first += prime;
	
	if(first <= high){
    	j = (first - low)/2;
    	for(; j <= (high - low)/2; j += prime)
    	    setbit(buf2, j);
	}
};


void limits(int64_t *low, int64_t* high, int id, int p, int64_t n, int64_t sqr){
    int64_t blockSize = (n-sqr)/p;
    
    *low = sqr + blockSize*id + 1;
    *high = *low + blockSize - 1;
    
    if(id == p-1) *high += (n-sqr) % p;
    if(*low % 2 == 0) *low ++;
    if(*high % 2 == 0) *high --;
}


int64_t Sieve(int64_t n, int id, int p, int64_t bufsize, int64_t bufsize2, int64_t low, int64_t high){
    int64_t i, j, k, prime, count = 0;
    
    char *buf1 = (char*)calloc(bufsize/8+1, sizeof(char));
    char *buf2 = (char*)calloc(bufsize2/8+1, sizeof(char));
    
    for(i = 0; i < bufsize; i++){
        if(!getbit(buf1, i)) {
            prime = i*2+3;
            //j = 2*i*i+6*i+3;
            j = i + prime;
            for(; j < bufsize; j += prime)
                setbit(buf1, j); 
    
            if(id == 0) 
                count++;
    
            markBlock(buf2, low, high, prime);
        }
    }

    for(i = 0; i < bufsize2; i ++)
        if(!getbit(buf2, i))
            count++;

    return count;
}

int main(int argc, char** argv){
	int64_t n = atol(argv[1]);
    int64_t count, globalSum = 0;
    int64_t low, high;
    int64_t sqr = sqrt((double)n);
    int64_t bufsize, bufsize2;
    
    int id, p;
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    MPI_Barrier(MPI_COMM_WORLD);
    
    limits(&low, &high,  id, p, n, sqr);
    bufsize2 = (high - low)/2+1;
    bufsize = (sqr-3)/2;

    count = Sieve(n, id, p, bufsize, bufsize2, low, high);

    MPI_Reduce(&count, &globalSum, 1, MPI_UNSIGNED, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
    
    if(id == 0) printf("%lld\n", (long long) globalSum + 1);
    
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
