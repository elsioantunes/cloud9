#include <iostream>
using namespace std;

int main() {
    string s;
    int n, a;
    while(1) {
        cin >> n;
        if(!n)break;

        cin >> s;
        for(int i=0; i<n; i++) {
            cin >> a;
            cout << s << endl;
        }
    }
    return 0;
}
