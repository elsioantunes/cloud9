// https://www.ime.usp.br/~pf/estruturas-de-dados/aulas/kmp.html
// https://github.com/PetarV-/Algorithms/blob/master/String%20Algorithms/Knuth-Morris-Pratt.cpp
#include <iostream>
using namespace std;

int main(){
    string s = "acaacabacaacaacaacabbacaacabacaacabaacaacabcaacabacaacabaacaacabcabacaacab";
    string w = "acaacab";

    cout << s << endl;

    int *P = new int[w.length()];

    for(int i=0;i<w.length();i++)
        P[i] = -1;
    
    for(int i=0, j=-1;i<w.length();){
        while(j > -1 && w[i] != w[j])
            j = P[j];
        i++; j++;
        P[i] = j;
    }

    for(int i=0;i<w.length();i++)
        cout << P[i] << " ";
    cout << endl;


    for(int i=0, j=0;i<s.length();){
        while(j > -1 && s[i] != w[j])
            j = P[j];
        i++; j++;
        if(j==w.length()){
            for(int k=0;k< i-w.length() ;k++)
                cout << " ";
            cout << w << endl;
        }
    }
    return 0;
}


/* ## SAÍDA ##
abcelsioelsslio def elsioelsslioelsioelsslioe mais elelsioelssliosio
-1 0 0 0 0 0 1 2 3 
   elsioelss
                    elsioelss
                                elsioelss
*/