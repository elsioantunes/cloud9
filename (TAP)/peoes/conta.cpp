#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
#define Matriz vector<vector<int> > 
#define Vetor vector<int> 

int getColId(double Z, int i){
    while(i > 0){
        Z /= 56;
        i--;
    }
    return fmod(Z,56);
}


main(){
    int W, w, d = 0;
    int cont  = 0;
    W = 550731776; // max id number
    w = 5461512; // total unic ids

    Matriz getTab;
 
    for(int j = 0; j < W; j++){
        int k[5], ok = 1;
        for(int i = 0; i < 5; i++){
            k[i] = getColId(j, i);
            if(i)
                if(k[i] > k[i-1]){
                    ok = 0;
                    break;
                }
            
        }
        
        if(ok){
            /*
            if(k[3]==55){
                
                for(int i = 0; i < 5; i++){
                    getTab[cont][i] = k[i];
                }
                    
                for(int i = 0; i < 5; i++){
                    cout << getTab[cont][i] << " ";
                }   
                cout << ": " << cont << endl;
            }
            */
            cont ++;
        }
    }
    cout <<  cont << endl;
    

    return 0;
}