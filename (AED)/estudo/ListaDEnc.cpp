#include <iostream>
#include <string>
#include "ListaDEnc.h"
using namespace std;


int main(){
    ListaDEnc<string> lista;

    lista.insere("Elsio");
    lista.insere("Jorge");
    lista.insere("Pedro");
    lista.insere("Bruno");
    lista.insere("Aline");
    lista.insere("Renan");
    lista.insere("apaga");
    lista.insere("Lucas");
    lista.insere("Andre");
    lista.insere("Pablo");

    for(int i=0;i<lista.tamanho();i++)
        cout << i << ":"<< lista.elemento(i) << endl;
    cout << endl;
    cout << "O Lucas esta na posicao: "<< lista.pesquisa("Lucas") << endl;
    cout << endl;


    lista.remove("apaga");
    lista.remove_pos(2);
    for(int i=0;i<lista.tamanho();i++)
        cout << i << ":"<< lista.elemento(i) << endl;
    cout << endl;
    cout << "'apaga' nao esta mais na lista;"<< endl;
    cout << "removido tambem o item de numero 2"<< endl;
    cout << "nas posicoes 2, 4 e 6, respectivamente estao: ";
    cout << lista.elemento(2) << ", ";
    cout << lista.elemento(4) << " e ";
    cout << lista.elemento(6) << endl;




    return 0;
}
