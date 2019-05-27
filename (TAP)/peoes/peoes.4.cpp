#include <iostream>
#include <vector>

using namespace std;
#define PEOES 3
#define CASAS 5
#define Matriz vector<vector<int> > // Atalhos...
#define Vetor vector<int>           // pq isso nao eh python :p  
#define mIter Matriz::iterator
#define vIter Vetor::iterator
#define Iter_M mIter it = M.begin(); it != M.end(); it++
#define Iter_v vIter v_it = v.begin(); v_it != v.end(); v_it++
#define Iter_u vIter u_it = u.begin(); u_it != u.end(); u_it++

int coluna[56][2];
int idColuna[CASAS][CASAS];
int tabuleiro[30857][3];
int idTabuleiro[56][56][56];
bool terminal[30857];

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
            for(int k = 0; k < id; k++)
                //if( i <= j && j <= k ){ // elimina permutacoes
                if(1){
                    tabuleiro[ID][0] = i; // devolve posicao de colunas
                    tabuleiro[ID][1] = j; // a partir do ID
                    tabuleiro[ID][2] = k;
                    idTabuleiro[i][j][k] = ID; // devolve ID a partir de posicao de cada coluna
                    terminal[ID++] = coluna[i][0] == CASAS-1 && \
                                     coluna[j][0] == CASAS-1 && \
                                     coluna[k][0] == CASAS-1 || \
                                     coluna[i][1] == 0 && \
                                     coluna[j][1] == 0 && \
                                     coluna[k][1] == 0; /* verifica conf terminal*/
                }
            
}

Vetor valid_mov(int player, int id){
    Vetor v;
    int p = coluna[id][0], q = coluna[id][1], lim;
    if(player == 0)
        if(q == p+1 && q!= CASAS-1) // eh caso de pular?
            v.push_back(idColuna[p+2][q]); // pula
        else{
            // ja pulou?
            if(q<p) lim = CASAS; else lim = q;
            // se sim o limite eh o final do tabuleiro
            // senao o limite eh o adversario 
            for(int i = p + 1; i < lim; i++)
                v.push_back(idColuna[i][q]); 
            // No caso terminal i = p+1 = lim = CASAS
            // nao existe o loop i nem v e M volta vazio.
        }
    else
        // analogo 
        if(p == q-1 && p!= 0)
            v.push_back(idColuna[p][q-2]); 
        else {   
            if (p<q) lim = p+1; else lim = 0;
            for(int i = lim; i < q; i++)
                v.push_back(idColuna[p][i]); 
        }
    return v;
}


Vetor valid_conf(int player, int ID){
    Vetor u, v;
    if(terminal[ID])
        v.push_back(ID);
    for(int i = 0; i < PEOES; i++){
        int k[3] = {
            tabuleiro[ID][0], tabuleiro[ID][1], tabuleiro[ID][2]
        };
        u = valid_mov(player, tabuleiro[ID][i]);
        for(Iter_u){
            k[i] = (*u_it);
            v.push_back(idTabuleiro[k[0]][k[1]][k[2]]);
        }
    }
    if(!v.size())
        v.push_back(ID);
    return v;
}

int main(){
    init();
    
    
    Vetor v = valid_conf(0, idTabuleiro[15][16][16]);
        
    for(Iter_v){
        printTab((*v_it));    
        cout << endl;
    }



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

1684 1688 1692 1696 1764 1768 1772 1776 1844 1848 1852 
1856 1924 1928 1932 1936 3284 3288 3292 3296 3364 3368 
3372 3376 3444 3448 3452 3456 3524 3528 3532 3536 4884 
4888 4892 4896 4964 4968 4972 4976 5044 5048 5052 5056 
5124 5128 5132 5136 6484 6488 6492 6496 6564 6568 6572 
6576 6644 6648 6652 6656 6724 6728 6732 6736 6737 6738 
6739 6756 6757 6758 6759 6776 6777 6778 6779 6796 6797 
6798 6799 7136 7137 7138 7139 7156 7157 7158 7159 7176 
7177 7178 7179 7196 7197 7198 7199 7536 7537 7538 7539 
7556 7557 7558 7559 7576 7577 7578 7579 7596 7597 7598 
7599 7936 7937 7938 7939 7956 7957 7958 7959 7976 7977 
7978 7979 7996 7997 7998 7999



valid_mov() test

    Vetor u;

    int ID = 0;
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 4; j++){
            cout << "para o ID " << ID << " temos:" << endl;
            u = valid_mov(1, ID++);
            for(Iter_u){
                cout <<  (*u_it) << " " ;
            }
            cout << endl;
        }
    }


*/