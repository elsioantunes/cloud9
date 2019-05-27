#include <iostream>
using namespace std;
int n,m,x,mx,tmp,i,j;
int main(){
    cin >> n;
    cin >> m;
    int *p = new int[n];
    mx = 0;
    for(i=0;i<n;i++){
        cin >> x;
        p[mx] = x;
        for(j=0;j<mx;j++){
            if(p[mx-j] > p[mx-j-1]){
               tmp = p[mx-j-1];
               p[mx-j-1] = p[mx-j];
               p[mx-j] = tmp;
            }
        }
        mx++;
    }
    for(j=0;j<m;j++){
        cout <<p[j]<< endl;
    }
    delete []p;
    return 0;
}
