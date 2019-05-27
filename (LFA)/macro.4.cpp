#include <iostream>
using namespace std;

int main() {
    string s;
    int n, a, b;
    while(1) {
        cin >> n;
        if(!n)break;
        cin >> s;
        //cout << n << endl << s <<endl;
        int s = 0;
        for(int i=0; i<n; i++) {
            cin >> a >> b;
            if(a==i+1){
                cout << b << " ";
                s+=b;
            }else{
                cout << a << " ";
                s+=a;
            }
        }
        cout << s << endl;
    }
    return 0;
}
