/*
Author: Yiu Yu Ho

We define a function f(i,j,c): the minimum number of days for a cell
letter c to grow into the segment [i,j] of the given worm.

if c --> ab is a rule, then one potential option for f(i,j,c) is
(1) c grows into ab
(2) a grows into [i,k], b grows into [k+1,j], for some k in [i,j-1]
This gives f(i,j,c) = 1 + max(f(i,k,a),f(k+1,j,b))

This gives us a recurrence relation to apply dynamic programming on.

In essence, the problem is really asking for a minimum height parse tree of a sentence,
when give a Context Free Grammar in Chomsky Normal Form.

Refer to Cocke-Younger-Kasami (CYK) algorithm for more details.
*/

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const int L = 20;
const int INF = 10000;

int H(char c) {
    return c-'A';
}

int Maxi(int x,int y) {
    return x>=y?x:y;
}
int Mini(int x,int y) {
    return x<=y?x:y;
}

void solve() {
    int cc;
    int mid,i,j,k;
    int A,len,x,age;
    int cost;

    char rule[64];
    int R[100][3],Rn;

    char cell[64];
    int min[50][50][L];

    cc=1;
    cin>>Rn;
    while(Rn>0) {
        for(i=0; i<Rn; i++) {
            cin>>rule;
            R[i][0]=H(rule[0]);
            R[i][1]=H(rule[1]);
            R[i][2]=H(rule[2]);
        }

        cin>>cell;
        len=strlen(cell);

        for(i=0; i<len; i++)
            for(j=i; j<len; j++)
                for(A=0; A<L; A++) {
                    min[i][j][A] = INF;
                }

        for(i=0; i<len; i++)
            min[i][i][H(cell[i])]=0;

        for(k=1; k<len; k++)
            for(i=0; i+k<len; i++) {
                j=i+k;

                for(x=0; x<Rn; x++)
                    for(mid=i; mid<j; mid++) {
                        cost = 1 + Maxi( min[i][mid][R[x][1]], min[mid+1][j][R[x][2]] );
                        min[i][j][R[x][0]] = Mini(min[i][j][R[x][0]],cost);
                    }
            }

        age = INF;
        for(A=0; A<L; A++) 
            age = Mini(age,min[0][len-1][A]);

        if(age<INF) {
            cout<<age<<endl;
        } else {
            cout<<-1<<endl;
        }
        cc++;
        cin>>Rn;
    }
}

int main() {
    clock_t startTime = clock();
    solve();
    clock_t endTime = clock();

    cerr<<"Time Spent = "<<(double)(endTime-startTime)/(CLOCKS_PER_SEC)<<"(sec)"<<endl;
    return 0;
}
