#include <iostream>
using namespace std;
#define N_PEOES 3
#define N_CASAS 5

int **board = new int*[N_PEOES];
int i, j, n, a, b, N1, N2;

void init(){
    N1 = 0; N2 = 0;
    for (i = 0; i < N_PEOES; i++)
        board[i]  = new int[N_CASAS];
}

void printBoard(){
    char p;
    cout << " -| ";
    for(i = 0; i < N_PEOES; i++){
        for(j = 0; j < N_CASAS; j++){
            if (board[i][j] == 0) p = '.';
            if (board[i][j] == 1) p = '0';
            if (board[i][j] == 2) p = '#';
            cout << p << " ";
        }
        cout << " || ";
    }
}

int update(int K1, int K2){
    
    int ret = 0, ant[3];

    for (j = 0; j < N_CASAS; j++)
        for(i = 0; i < N_PEOES; i++)
            board[i][j] = 0;
            
    n = K1;
    for(i = 0; i < N_PEOES; i++){
        j = n % N_CASAS;
        n = (n - j) / N_CASAS;
        board[i][j] = 1;
        ant[i] = j;
    }

    n = K2;
    for(i = 0; i < N_PEOES; i++){
        j = n % N_CASAS;
        n = (n - j) / N_CASAS;
        if (board[i][N_CASAS-1-j] == 1) ret = 1;
        //if (ant[i]>j) ret = 1;
        board[i][N_CASAS-1-j] = 2;
    }
    
    return ret;
}

int gcd(int a, int b){
    if(b==0) return a;
    return gcd(b, a%b);
}

int main(){
    init();
    int buf[8000],bi=0;

    int k = 0, c01 = 0, t1, m; 
    
    //for(int h=0;h<31;h++) 
    for(int k1 = 0; k1 < 125; k1++){
        for(int k2 = 0; k2 < 125; k2++){
            m = k2-k1;

            if(1){
            
                t1 = update(k1, k2);
                if(t1 == 0) {
                    printBoard();
                    cout << "-  \t:: " <<   m << " \t: " << m%5<< " \t:: "<< c01 <<  endl;
                    c01++;
                    buf[bi++]=m;
                }
                k ++;
            }
        }
    }
    
    
    
    return 0;
    
    
    int s;
    string str="";
    cout << endl << endl;
    for(i=0;i<bi;i++){
        cout << buf[i]<< " ";
        
        n = buf[i];
        str = "";
        for(j=0;j<3;j++){
            s = n%5;
            if(s==0) str = " . "+str;
            if(s==1) str = " - "+str;
            if(s==2) str = " / "+str;
            if(s==3) str = " + "+str;
            if(s==4) str = " # "+str;
            n = (n-s)/5;
        }
        //cout << str << endl;
        
    }

    return 0;
}