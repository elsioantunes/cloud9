// br.spoj.com/problems/REDOTICA/
// arvore geradora minima
// union-find
#include <iostream>
using namespace std;
int main() {
    int M, N, X, Y, Z, swp, T = 1;
    struct Vertice {int x, y, z, ok;};
    while(1) {
        cin >> N >> M; if(N==0) break;
        Vertice v[N*N], w[M], vswp;
        for(int i=0; i<N*N; i++)
            w[i]=v[i]= {0,0,0,0};

        for(int i=0; i<M; i++) {
            cin >> X >> Y >> Z; X--;Y--;
            if(X>Y) {
                swp = X;
                X = Y;
                Y = swp;
            }
            v[Y*N+X] = {X, Y, Z, 1};
        }
        M = 0;
        for(auto &i:v)
            if(i.ok)w[M++]=i;

        for(int i=0; i<M-1; i++)       // buble
            for(int j=i+1; j<M; j++)
                if(w[i].z > w[j].z) {
                    vswp = w[i];
                    w[i] = w[j];
                    w[j] = vswp;
                }
        int S[N], t1, t2;                // Kruskal
        for(int i=0; i<N; i++)S[i]=i;
        for(int i=0; i<M; i++){
            t1 = S[w[i].x];
            t2 = S[w[i].y];
            if(t1!=t2){
                w[i].ok++;
                for(int j=0; j<N; j++)
                    if(S[j]==t2)
                        S[j]=t1;
            }
        }
        cout << "Teste " << T++ << endl;
        for(int i=0; i<M; i++)
            if(w[i].ok==2) cout << w[i].x+1 << " " << w[i].y+1 << endl;
        cout << endl;
    }
    return 0;
}
