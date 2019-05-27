#include <iostream>
using namespace std;

int main() {
    string s1, s2, s3;
    int n;
    while(1) {
        cin >> n;
        if(!n)break;
        cout << n << endl;
        for(int i=0; i<n; i++) {
            cin >> s1 >> s2 >> s3;
            cout << s2 << " " << s3 << endl;
        }
        cout << endl;
    }
    return 0;
}
