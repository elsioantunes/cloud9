#include <string>
#include <iostream>
#include <stdlib.h>
using namespace std;


int main() {
    int teste = 1;
    while(true) {
        int soma=0, i=0, n;
        cin >> n;
        if(n==0)break;
        string line="";
        while(line=="") {
            getline(cin, line);
        }
        for(i=0; i<line.length(); i++) {
            int sinal = 0;
            char c = line[i];
            if(c=='-'||c=='+') {
                if(c=='-') sinal=1;
                i++;
            }
            int n = line[i]-'0';
            while(line[i+1]>='0' && line[i+1]<='9') {
                n *=10;
                n += line[i+1]-'0';
                i++;
            }
            if(sinal) n = -n;
            soma+=n;
        }
        cout << "Teste " << teste << endl << soma << endl << endl;
        teste++;
    }
    return 0;
}
