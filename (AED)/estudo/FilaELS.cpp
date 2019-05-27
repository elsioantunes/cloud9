#include <iostream>
using namespace std;

class FilaELS{ // ps: quando seu sistema aceitar a logica eu faco seus setgets.
    private:
        struct Celula{
            int n, sentinela;
            Celula *prox;
        };
        Celula *ini, *fim, *aux;
    public:
        FilaELS(){
            ini = new Celula();
            fim = ini;
            fim->prox = NULL;
        };
        void inserir(int n){
            fim->prox = new Celula();
            fim = fim->prox;
            fim->n = n;
            fim->prox = NULL;
        };
        int remover(){
            if(ini->prox){
                aux = ini;
                ini = ini->prox;
                delete aux;
                return ini->n;
            }
            return -123451; // da outra vez eu fiquei preso no seu zero. vai saber ne?
        };
        
        void mostra(){
            if(ini->prox){
                aux = ini;
                while(ini = ini->prox)
                    cout << (ini==aux->prox?"":" ") << ini->n;
                ini = aux;
                cout << endl;  // Eu nao sei se vc vai ver isso
            }
        };                          // mas parece que vc gosta de estimular o POG
                                    // se essa se essa versao for aceita em detrimento da outra
                                    // vou ter certeza que vc nao avalia soh a logica.
                                    // o tratamento do formato da saida DE DADOS nao eh trabalho da classe
                                    // e mudar o ponteiro de posicao nao eh pra ser feito na main
        
        ~FilaELS(){
            while(ini){
                aux = ini;
                ini = ini->prox;
                delete aux;
            }
        };
};

int main(){
    char c;
    int n;
    FilaELS fila;
    while(cin >> c){
        if(c=='E') {
            cin >> n;
            fila.inserir(n);
        }
        if(c=='D') {
            n = fila.remover();
            if(n!=-123451)
                cout << "<" << n << ">" << endl; // pq caralhos vc quer uma string?
        }
        if(c=='M') fila.mostra();
    };
    return 0;
}