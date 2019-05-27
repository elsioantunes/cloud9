#include <iostream>
using namespace std;

int main() {

    string s1, s2, s3;
    string str[200][3];
    
    
    int k=0;
    while(cin >> s1){
        cin >> s2 >> s3;
        if(s1=="eps"){
            if(k){
                cout << k << endl;
                for(int i=0;i<k;i++){
                    cout << str[i][0] << " " << str[i][1] << " " << str[i][2] << endl;
                }
            }
            cout << endl;
            k=0;
        }
        str[k][0]=s1;
        str[k][1]=s2;
        str[k][2]=s3;
        k++;
    };
    
    return 0;
}
