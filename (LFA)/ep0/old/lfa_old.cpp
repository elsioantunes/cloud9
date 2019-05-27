// Programa que simula automatos finitos deterministicos
// Autor: Elsio Antunes (ra:11097612) <tksmkd@gmail.com>
// Dificuldades: * Nao se deve esperar strings e sim linhas, 
//               pra considerar o caso epslon (string vazia);
//               * O conjunto de estados finais 
//               deve ser recebido de uma forma específica;

#include <iostream>
#include <string>
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
    cin >> k;    
    string w;
    for(int j=0;j<k;j++){
        getline(cin,w);
        q = 0;          // assumindo zero, ja que o pdf omite.
        for(unsigned int i=0;i<w.length();i++)
            q = adj[q][w[i]-97];
        cout << (f[q]?"SIM":"NAO")  << endl;
    }
 
    return 0;
}
 