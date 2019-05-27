#include <iostream>
using namespace std;

int main() {
    string s1, s2;
    int n, buf[100][2];
    while(1) {
        cin >> n;
        if(!n)break;

        for(int i=0; i<n; i++) {
            cin >> s1 >> s2;
            if(s1=="eps") 
                buf[i][0] = 0;
            else
                buf[i][0] = s1.length();

            if(s2=="eps") 
                buf[i][1] = 0;
            else
                buf[i][1] = s2.length();
        }
        
        cout << n << endl;
        cout << s1 << endl;
        for(int i=0; i<n; i++) {
            cout << buf[i][0] << " " << buf[i][1] << endl; 
        }
    }
    cout << 0<<endl;
    return 0;
}
