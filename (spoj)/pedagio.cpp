#include <iostream>
using namespace std;
int main() {
    int C, E, L, P, x, y, T=1;
    int buf[51][51];
    int fila[51];
    while(1) {
        cin >> C >>  E >>  L >>  P; 
        if(C==0)break;
        int k=0, h=0, g, city[51];
        for(int i=1; i<=50; i++) city[i]=0;
        for(int i=0; i<=C; i++)
            for(int j=0; j<=C; j++)
                buf[i][j]=false;
        for(int i=1; i<=E; i++) {
            cin >> x >>  y;
            buf[x][y]=true;
            buf[y][x]=true;
        };
        fila[k++]=L;
        while(h<k) {
            g = fila[h++];
            city[g] += 100;
            for(int i=1; i<=C; i++) {
                if(buf[g][i])
                    if(city[i]<100) {
                        fila[k++] = i;
                        city[i] = city[g] + 1;
                    }
            }
        }
        cout << "Teste " << T++ << endl;
        for(int i=1; i<=50; i++)
            if(city[i]%100<=P&&city[i]%100>0)
                cout << i << " ";
        cout << endl << endl;
    }
    return 0;
}



