#include <iostream>
using namespace std;
#define PEOES 3
#define CASAS 5

int coluna[56][2];
int idColuna[CASAS][CASAS];
int tabuleiro[30857][3];
int idTabuleiro[56][56][56];
bool terminal[56][56][56];

/*************************************************************
 *                                                           * 
 * **********************************************************/
void printCol(int id){
    cout << id << "\t";
    for(int j = 0; j < CASAS; j++){
        if( j == coluna[id][0]) cout << " 0";
        else if( j == coluna[id][1]) cout << " x";
        else cout << " .";
    }
    cout << endl;
}

void printTab(int ID){
    cout << ID << endl;
    printCol(tabuleiro[ID][0]);
    printCol(tabuleiro[ID][1]);
    printCol(tabuleiro[ID][2]);
}

/*************************************************************
 *                                                           * 
 * **********************************************************/


int init(){
    int id = 0;
    for(int i = 0; i < CASAS; i++)
        for(int j = 0; j < CASAS; j++)
            if(i != j) {
                coluna[id][0] = i;
                coluna[id][1] = j;
                idColuna[i][j] = id++;
            }
    
    int ID = 0;
    for(int i = 0; i < id; i++)
        for(int j = 0; j < id; j++)
            for(int k = 0; k < id; k++){
                if( i <= j && j <= k ){
                    tabuleiro[ID][0] = i;
                    tabuleiro[ID][1] = j;
                    tabuleiro[ID][2] = k;
                    idTabuleiro[i][j][k] = ID++;
                    terminal[i][j][k] = coluna[i][0] == CASAS-1 && \
                                        coluna[j][0] == CASAS-1 && \
                                        coluna[k][0] == CASAS-1 || \
                                        coluna[i][1] == 0 && \
                                        coluna[j][1] == 0 && \
                                        coluna[k][1] == 0;
                }
            }
}

bool valido(int player, int id){
    
}


int main(){
    init();
    
    
        
    return 0;
}




/*

ID inicial 1263, representante 571


0  0 x . . .
1  0 . x . .
2  0 . . x .
3  0 . . . x
4  x 0 . . .
5  . 0 x . .
6  . 0 . x .
7  . 0 . . x
8  x . 0 . .
9  . x 0 . .
10  . . 0 x .
11  . . 0 . x
12  x . . 0 .
13  . x . 0 .
14  . . x 0 .
15  . . . 0 x
16  x . . . 0
17  . x . . 0
18  . . x . 0
19  . . . x 0

terminais
4 4 4,
4 4 8, 4 4 12, 4 4 16, 4 8 8, 4 8 12, 4 8 16, 4 12 12, 
4 12 16, 4 16 16, 8 8 8, 8 8 12, 8 8 16, 8 12 12, 
8 12 16, 8 16 16, 12 12 12, 12 12 16, 12 16 16, 
16 16 16, 16 16 17, 16 16 18, 16 16 19, 16 17 17, 
16 17 18, 16 17 19, 16 18 18, 16 18 19, 16 19 19, 
17 17 17, 17 17 18, 17 17 19, 17 18 18, 17 18 19, 
17 19 19, 18 18 18, 18 18 19, 18 19 19, 19 19 19

*/