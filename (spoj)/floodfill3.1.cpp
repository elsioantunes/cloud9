#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;
int u, k, L, C, l, c, x;
int pilha[2000000];
char fdp;

int main(){
    string str, buf = "";
    cin >> L >> C;
    for(int i=0;i<(C+2)*(L+2);i++) buf += 'x';
    for(int i=0;i<L;i++){
        cin >> str;
        for(int j=0;j<C;j++)
           buf[(i+1)*(C+2)+j+1] = str[j];
    }
    while(true){
        cin >> l >> c;
        if(l<0||c<0||l>=L||c>=C) break;
        c--;l--;
        u = 0; k = 0;
        x = (l+1)*(C+2)+(c+1);
        pilha[k++] = x;
        fdp = buf[x];
        if(fdp!='x')
			while(k){
				x = pilha[--k];
				if(buf[x]==fdp){
					buf[x] = 'x';
					pilha[k++] = x+1;
					pilha[k++] = x-1;
					pilha[k++] = x+C+2;
					pilha[k++] = x-C-2;
					u++;
				}
			}
			cout << u << endl;
		}
    return 0;
}

