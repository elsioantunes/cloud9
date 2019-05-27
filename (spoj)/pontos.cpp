#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;
int p[1001][2],n;
double xx = 4000000,yy = 4000000;
double h = xx*xx+yy*yy;
int main(){
	cin >> n;
    for(int i=0;i<n;i++){
        cin >> p[i][0];
        cin >> p[i][1];
    }
    for(int i=0;i<n-1;i++)
        for(int j=i+1;j<n;j++){
            xx = p[i][0] - p[j][0];
            yy = p[i][1] - p[j][1];
            if(xx*xx+yy*yy<h)h=xx*xx+yy*yy;
        }
    cout << fixed << setprecision(3) << sqrt(h);
    return 0;
}
