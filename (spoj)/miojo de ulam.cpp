#include <iostream>
#include <math.h>
#include <stdlib.h>
using namespace std;

int main() {
    int x, y, j=0, i=0, q=0;
    int c = 3;
    int a = 5;
    int b = 7;
    //cin >> c >> a >> b;
    while(true) {
        if(j==0) {
            q = i+i+1;
            x = i;
            y = 0;
        }
        if(j<q) {
            //if(abs(x*a-y*b)==c)break;
            cout << abs(x*a-y*b) << endl;
            if(abs(x*a-y*b)==35)break;

            if(y<x){
                y++;
            } else {
                x--;
            }
            j++;
        } else {
            j=0;
            i++;
        }
    }
    cout << max(x*a,y*b) << endl;
    return 0;
}
