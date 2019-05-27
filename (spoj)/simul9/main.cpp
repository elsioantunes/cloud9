// br.spoj.com/problems/SIMUL09/
#include <iostream>
#include <stdio.h>
using namespace std;

int main() {
    int m, n, c=0;
    cin >> n >> m;

    struct Cell {
        char c;
        int x, y;
    } buf[m*2];

    int N[m*2];

    for(int i=0; i<m; i++)
        scanf("\n%c %d %d", &buf[i].c, &buf[i].x, &buf[i].y);


    for(int i=0; i<m; i++) {
        long long s=0;
        if(buf[i].c=='S') {
            if(i) {
                for(int j=buf[i].x; j<= buf[i].y; j++) {
                    n = j;
                    if(buf[i-1].c=='I')
                        if(n>=buf[i-1].x && n<=buf[i-1].y)
                            n = buf[i-1].y + buf[i-1].x - n;
                    s+=n;
                }
            } else {
                s = (buf[i].y*buf[i].y + buf[i].y - buf[i].x*buf[i].x + buf[i].x)/2;
            }
            cout << s << endl;
        } else {
        }
    }

    return 0;
}
