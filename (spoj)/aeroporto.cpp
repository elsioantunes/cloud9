#include <iostream>
#include <stdio.h>
using namespace std;


int T=0,A=1,V=1,X,Y,tmp;
int M[101][2];

int main(){
    while(1){
        // obtendo dados
        scanf("%d %d",&A,&V);
        if(A==0 && V==0) break;

        // limpando a lista
        for(int i=0;i<A;i++){
            M[i][0]=0;
            M[i][1]=i;
        }

        // preenchendo a lista
        for(int i=0;i<V;i++){
            scanf("%d %d",&X,&Y);
            M[X-1][0]++;
            M[Y-1][0]++;
        }

        //ordenando a lista (por valor)
        for(int i=0;i<A-1;i++){
            for(int j=i+1;j<A;j++){
                if(M[i][0]<M[j][0]){
                    tmp = M[i][0];
                    M[i][0] = M[j][0];
                    M[j][0] = tmp;

                    tmp = M[i][1];       // trocando índices tb!
                    M[i][1] = M[j][1];
                    M[j][1] = tmp;
                }
            }
        }

        //ordenando a lista (por chave)
        for(int i=0;i<A-1;i++){
            for(int j=i+1;j<A;j++){
                if(M[i][0]==M[j][0] && M[i][0]<M[j][0]){
                    tmp = M[i][0];
                    M[i][0] = M[j][0];
                    M[j][0] = tmp;

                    tmp = M[i][1];       // trocando índices tb!
                    M[i][1] = M[j][1];
                    M[j][1] = tmp;
                }
            }
        }

        //exibindo a lista
        printf("Teste %d\n",++T);
        for(int j=0;j<A;j++){
            if(M[0][0] == M[j][0])
                printf("%d ",M[j][1]+1);
        }
        printf("\n");
        printf("\n");
    };

    //delete []M;
    return 0;
}
