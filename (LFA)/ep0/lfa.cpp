// Programa que simula automatos finitos deterministicos
// Autor: Elsio Antunes (ra:11097612) <tksmkd@gmail.com>
// Dificuldades: * Nao se deve esperar strings e sim linhas, 
//               pra considerar o caso epslon (string vazia);
//               * pra sanar o problema anterior usei getline
//               que causou outro problema: capturar o \n apos o inteiro k
//               * depois de solucionar o problema o professor modificou as instancias
//               invalidando a solução. Então usei scanf. Mas em cpp  isso eh pog :p
//               * O conjunto de estados finais 
//               deve ser recebido de uma forma específica;

#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;
 
int adj[100000][26];
bool f[100000];
int n, k, q;

int main() {

    // captura automato
    cin >> n >> k; 
    for(int i=0;i<n;i++)
        for(int j=0;j<k;j++)
            cin >> adj[i][j];
 
    // captura estados finais
    cin >> k;     
    for(int i=0;i<n;i++)
        f[i] = false;
    for(int j=0;j<k;j++)
        cin >> q,
        f[q] = true;

    // captura strings 
    scanf("%d\n", &k);
    string w;
    for(int j=0;j<k;j++){
        getline(cin,w);
        //cout << "["<< w <<"]"<< endl;
        q = 0;          // assumindo zero, ja que o pdf omite.
        for(unsigned int i=0;i<w.length();i++)
            q = adj[q][w[i]-97];
        cout << (f[q]?"SIM":"NAO")  << endl;
    }
 
    return 0;
}
 