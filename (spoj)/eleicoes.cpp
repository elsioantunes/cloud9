#include <iostream>
using namespace std;


void heapfy(unsigned int *heap,unsigned int i, unsigned int len) {
    unsigned int j, c1, c2 ,tmp;
    while(i < len) {
        j = i;
        c1 = 2*i+1; c2 = 2*i+2;
        if (c1<len && heap[c1]>heap[j])j = c1;
        if (c2<len && heap[c2]>heap[j])j = c2;
        if (j == i) return;
        tmp = heap[i];heap[i] = heap[j];heap[j] = tmp;i = j;
    }
}

void heap_sort(unsigned int *buf,unsigned int len) {
    unsigned int tmp;
    int i = len/2;

    while (--i >= 0)
        heapfy(buf, i, len);
    while(--len > 0) {
        tmp = buf[0];
        buf[0] = buf[len];
        buf[len] = tmp;
        heapfy(buf, 0, len);
    }
}


int main() {
    unsigned int i, j, n, x;
    cin >> n;
    if(n<1)return 0;
    unsigned int buf[n+1];

    for(i=0; i<n; i++) {
        cin >> x;
        buf[i] = x;
    }

    heap_sort(buf,sizeof(buf)/sizeof(buf[0]));


    int votos = 1;
    int vmax = 0, r;
    for(i=1; i<n+1; i++) {
        if(buf[i]==buf[i-1]){
            votos ++;
        }else{
            if(vmax<votos){
                r = buf[i-1];
                vmax = votos;
            }
            votos = 1;
        }
    }
    cout << r << endl;


    return 0;
}


