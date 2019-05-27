#include <iostream>
using namespace std;
struct tipo{unsigned long v;};
void heapfy(tipo *buf, unsigned int i, unsigned int len) {
    unsigned int j, c1, c2;
    tipo tmp;
    while(i < len) {
        j=i;
        c1=2*i+1; c2=2*i+2;
        if (c1<len && buf[c1].v>buf[j].v)j=c1;
        if (c2<len && buf[c2].v>buf[j].v)j=c2;
        if (j == i) return;
        tmp=buf[i];buf[i]=buf[j];buf[j]=tmp;i=j;
    }
}
void heap_sort(tipo *buf,unsigned int len) {
    tipo tmp;
    int i=len/2;
    while (--i >= 0)
        heapfy(buf, i, len);
    while(--len > 0) {
        tmp=buf[0];
        buf[0]=buf[len];
        buf[len]=tmp;
        heapfy(buf, 0, len);
    }
}
//heap_sort(buf,sizeof(buf)/sizeof(buf[0].v));

char troco(){
    tipo buf[100000];
    bool teste[100000];
    long V, v, u;
    int n;
    char r;

        long k=0;
        cin >> V >> n;
        for(long i=0;i<n;i++)teste[i]=false;
        for(int i=0;i<n;i++) {
            cin >> v;
            if(v==V)return 'S';
            if(v<V){
                long h=k;
                for(long j=0;j<h;j++){
                    u=v+buf[j].v;
                    if(u==V)return 'S';
                    if(u<V){
                        if(!teste[u]) buf[k++].v=u;
                        teste[u]=true;
                    }
                }
                buf[k++].v=v;
                teste[v]=true;
            }
        }

        //if(r=='N') {
        //    heap_sort(buf, n);
        //}
        return 'N';
}


int main() {
    cout << troco() << endl;
    return 0;
}


