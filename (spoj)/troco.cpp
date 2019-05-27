#include <iostream>
using namespace std;
char troco(){
    struct tipo{unsigned long v;} buf[100000];;
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
                        if(!teste[u])buf[k++].v=u;
                        teste[u]=true;
                    }
                }
                buf[k++].v=v;
                teste[v]=true;
            }
        }
        return 'N';
}
int main() {
    cout << troco() << endl;
    return 0;
}


