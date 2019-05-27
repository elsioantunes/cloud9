#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main() {
    srand(time(0));
    cout << 10 << " " << 10 << endl;
    for(int i=0;i<10;i++){
        int x=0, y=0, p;
        while(x==y){
            x = rand()%10+1;
            y = rand()%10+1;
            p = rand()%15+5;
        }
        cout << x << " " << y << " " << p << endl;
    }

    return 0;
}
