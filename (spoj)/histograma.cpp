#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;
int main(){
    int X, Y, C, c;
    while(true){
		cin >> X;
		cin >> Y;
		cin >> C;
		if (X==0) break;
		int *h = new int[X*Y];
		for(int i=0;i<C+1;i++) h[i]=0;
		for(int i=0;i<X;i++)
		    for(int j=0;j<Y;j++){
				cin >> c;
				h[c]++;
			}
		for(int i=0;i<C+1;i++)
		    cout << i << ":" << h[i] << " ";
		    cout << endl;
    }
    return 0;
}

