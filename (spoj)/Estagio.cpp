#include <iostream>
#include <stdio.h>

using namespace std;

int N,a,b,p,notamax, t=1;
int aluno[1001];
int main(){
    while(1){
       scanf("%d", &N);
       if (N==0)break;
       notamax = 0;
       p = 0;
       for(int i=0;i<N;i++){
           scanf("%d %d", &a, &b);
           if(b>notamax){
               notamax = b;
               p = 0;
           }
           if(b >= notamax){
               aluno[p]=a;
               p++;
           }
       }

       printf("Turma %d\n",t++);
       for(int i=0;i<p;i++){
           printf("%d ",aluno[i]);
       }
       printf("\n\n");

    }
    return 0;
}
