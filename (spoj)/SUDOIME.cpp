#include <string>
#include <iostream>
#include <stdlib.h>
using namespace std;

int main() {
    int m, n;
    cin >> m;
    int buf[81];
    for(int i=0; i<m; i++) {
        bool teste = false;
        int expressao;
        for(int j=0; j<81; j++) cin >> buf[j];
        for(int tipo=0; tipo<3; tipo++) { //linha, coluna e bloco
            for(int l=0; l<9; l++) {
                int s = 0, p = 1;
                for(int c=0; c<9; c++) {
                    if(tipo<2) {
                        // À quem interessar possa
                        // essa expressão é uma mistura das equações
                        // 9k+j e 9j+k diferenciadas pelo "tipo"
                        expressao = (tipo*8+1)*l + ((1-tipo)*8+1)*c;
                    } else {
                        // Daria pra juntar essa expressão com a de cima tb
                        // mas dá trabalho demais pensar nisso.
                        // Desnecessário pra resolução do problema.
                        expressao = 9*((c+9*(l/3))/3)+(c%3)+(l%3)*3;
                    }
                    s +=buf[expressao]; // uma vez encontrados com quais números trabalhar
                    p *=buf[expressao]; // agora é só conferir a validade
                }
                // apenas testando
                // a soma e o produto dos dez números
                // de cada linha e cada coluna
                // se os valores forem diferente disso...
                if(s!=45||p!=362880)teste=true;
            }
        }

        string r = "SIM";
        if(teste) r = "NAO";

        cout << "Instancia " << i+1 << endl << r << endl << endl;
    }
    return 0;
}

/*

3
1 3 2 5 7 9 4 6 8
4 9 8 2 6 1 3 7 5
7 5 6 3 8 4 2 1 9
6 4 3 1 5 8 7 9 2
5 2 1 7 9 3 8 4 6
9 8 7 4 2 6 5 3 1
2 1 4 9 3 5 6 8 7
3 6 5 8 1 7 9 2 4
8 7 9 6 4 2 1 5 3

1 3 2 5 7 9 4 6 8
4 9 8 2 6 1 3 7 5
7 5 6 3 8 4 2 1 9
6 4 3 1 5 8 7 9 2
5 2 1 7 9 3 8 4 6
9 8 7 4 2 6 5 3 1
2 1 4 9 3 5 6 8 7
3 6 5 8 1 7 9 2 4
8 7 9 6 4 2 1 3 5

1 3 2 5 7 9 4 6 8
4 9 8 2 6 1 3 7 5
7 5 6 3 8 4 2 1 9
6 4 3 1 5 8 7 9 2
5 2 1 7 9 3 8 4 6
9 8 7 4 2 6 5 3 1
2 1 4 9 3 5 6 8 7
3 6 5 8 1 7 9 2 3
8 7 9 6 4 2 1 5 4



*/
