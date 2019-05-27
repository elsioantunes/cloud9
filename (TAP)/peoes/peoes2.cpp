#include <iostream>
#include <vector>
using namespace std;

#define PEOES 3
#define CASAS 5
#define Vetor vector<long>

int col[56][2], idcol[56][56], comb, id;
struct Estado{
    long ID;
    int v, player;
    Vetor adj0, adj1;
};
long ID;
vector<Estado> tab;

/*************************************
*	utils 
*************************************/

void printbin(int n, int dig){
    string str;
    for(int i=0;i<dig;i++){
        int s = n%2;
        if(s)str = "O " + str;
        else str = ". " + str;
        n=(n-s)/2;
    }
    cout << str << endl;
}

void printcol(int id){
   for(int i=0;i<CASAS;i++){
      if(i==col[id][0]) cout << "0 ";
      else if(i==col[id][1]) cout << "X ";
      else cout << ". ";
   }
   cout << endl;   
}

void printtab(int a, int b, int c){
   printcol(a);
   printcol(b);
   printcol(c);
   cout << endl;   
}


/*************************************
*	utils pacarai
*************************************/

int C(int n, int k){
    if(k > n) return 0;
    if(k > n/2) k = n - k;
    int res = 1;
    for(int i = 0; i < k; i++){
        res *= n - i;
        res /= i + 1;
    }
    return res;
}

long gosper(long a, int init){
    if(init)
        return (1 << a) - 1;
    long c, r;
    c = a & -a;
    r = a + c;
    return (((r ^a) >> 2 ) /c) | r;
}

/************************************
*	principal
*************************************/

Vetor grafcol(int player, int id){
    int O = col[id][0], X = col[id][1], i;
    Vetor res;

    if(player == 0){
        if(O + 1 == X && X != CASAS-1) 
            res.push_back(idcol[O+2][X]);
        else{
           int lim = (O < X)?X:CASAS;
           for(i = O+1; i < lim; i++)
               res.push_back(idcol[i][X]);
        }
        
    }else{
        if(O + 1 == X && O != 0) 
            res.push_back(idcol[O][X-2]);
        else
           for(i = (O < X)?O+1:0; i < X; i++)
                res.push_back(idcol[O][i]);
    }
    return res;
}


void init(){
    id = 0;   // comb = C(CASAS,2)*2; 
    for(int i = 0; i < CASAS; i++)
        for(int j = 0; j < CASAS; j++)
            if(i != j){
               col[id][0] = i;
               col[id][1] = j;
               idcol[i][j] = id;
               id ++ ;
            }
    
    comb = id;
    for(int i = 0; i < PEOES; i++){
        ID = gosper(i+1, 1); 
        for(int j = 0; j < C(comb, i+1); j++){
            Estado est;
            est.ID = ID;
            if(i==0){
                Vetor g1 = grafcol(0, j);
                for(int k=0;k<g1.size();k++)
                   est.adj0.push_back(g1[k]);

            }
            tab.push_back(est); 
            ID = gosper(ID, 0); 
        }   
    }
}


/*

0   0 X . . .
1   0 . X . .
2   0 . . X .
3   0 . . . X
4   X 0 . . .
5   . 0 X . .
6   . 0 . X .
7   . 0 . . X
8   X . 0 . .
9   . X 0 . .
10  . . 0 X .
11  . . 0 . X
12  X . . 0 .
13  . X . 0 .
14  . . X 0 .
15  . . . 0 X
16  X . . . 0
17  . X . . 0
18  . . X . 0
19  . . . X 0

[0 1] [0 2] [0 3] [0 4] [1 0] 
[1 2] [1 3] [1 4] [2 0] [2 1] 
[2 3] [2 4] [3 0] [3 1] [3 2] 
[3 4] [4 0] [4 1] [4 2] [4 3] 

15, 23, 31, 39, 47, 55 

*/



int main(){
	
	init();
	
	for(int i=0;i<tab.size();i++){
	    cout << endl;
	    printbin(tab[i].ID, 20);
	    for(int j=0;j<tab[i].adj0.size();j++){
	        long k = 1 << tab[i].adj0[j];
	        printbin(k|tab[i].ID,20);
	    }
	       
	    cout << endl;
	}
	

	
	/*
	id = 0;
	for(int i=0; i<CASAS; i++){
	   for(int j=0; j<CASAS-1; j++){
	      Vetor res = grafcol(1, id);
	      cout << "[";
	      for(int j = 0; j < res.size(); j++)
	          cout << res[j] << " ";
	      cout << "] ";
	      id++;
	   }
	   cout << endl;
	}
	*/


    return 0;
}




/*

 C(5, 2) * 2 = 20
 C(8, 2) * 2 = 56

 C(20, 1) * C(2, 0) = 20      * 1   = 20     (a, a, a)  
 C(20, 2) * C(2, 1) = 190     * 2   = 390    (a, a, b) (a, b, b)  
 C(20, 3) * C(2, 2) = 1140    * 1   = 1140   (a, b, c)
                    + 1350          + 1540 
                      
 C(56, 1) * C(4, 0) = 56      * 1  = 56        (a, a, a, a, a)   
 C(56, 2) * C(4, 1) = 1540    * 4  = 6160      (a, b, b, b, b) (a, a, b, b, b) (a, a, a, b, b) (a, a, a, a, b)
 C(56, 3) * C(4, 2) = 27720   * 6  = 166320    (a, a, a, b, c) (a, b, b, b, c) (a, b, c, c, c) (a, a, b, b, c) (a, a, b, c, c) (a, b, b, c, c) 
 C(56, 4) * C(4, 3) = 367290  * 4  = 1469160   (a, a, b, c, d) (a, b, b, c, d) (a, b, c, c, d) (a, b, c, d, d) 
 C(56, 5) * C(4, 4) = 3819816 * 1  = 3819816   (a, b, c, d, e)
                    + 4216422      + 5461512

0   0 X . . .
1   0 . X . .
2   0 . . X .
3   0 . . . X
4   X 0 . . .
5   . 0 X . .
6   . 0 . X .
7   . 0 . . X
8   X . 0 . .
9   . X 0 . .
10  . . 0 X .
11  . . 0 . X
12  X . . 0 .
13  . X . 0 .
14  . . X 0 .
15  . . . 0 X
16  X . . . 0
17  . X . . 0
18  . . X . 0
19  . . . X 0




*/ 
	

