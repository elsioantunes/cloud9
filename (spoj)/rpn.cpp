#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
double s;
char line[200];
double pilha[1000];

int main(){
    while(true){
       int len=0,i=0,p=0;
       cin.getline(line, 200);
       if(line[0]=='#')break;
       while(line[i++]!=0)len++;

       for(int i=0;i<len;i++){
           if(line[i] <'0'||line[i]>'9'){      // operador
               double b = pilha[p-1];
               double a = pilha[p-2];
               if(line[i]=='+') pilha[p-2]=a+b;
               if(line[i]=='-') pilha[p-2]=a-b;
               if(line[i]=='*') pilha[p-2]=a*b;
               if(line[i]=='/') pilha[p-2]=a/b;
               if(line[i]=='+' || line[i]=='-' || line[i]=='*' || line[i]=='/' || line[i]==' '){
                   if(line[i]!=' ')p--;
               }else{
                   p = 1000;
               }
           }else{
               s = line[i]-'0';                          // operando
               while(line[i+1]>='0' && line[i+1]<='9'){
                   s *=10;
                   s += line[i+1]-'0';
                   i++;
               }
               pilha[p]=s;
               p++;
           }
       }

       if(p!=1)
           cout << "erro" << endl;
       else
           cout << pilha[0] << endl;
    }
    return 0;
}
