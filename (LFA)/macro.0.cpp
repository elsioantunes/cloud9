#include <iostream>
using namespace std;

int main() {

    string s;
    string str[200];
    
    
    int k=0;
    while(cin >> s){
        if(s=="1"||s=="0"){
        }else{
            cout << s << " ";
            k++;
            if(k%3==0)cout << endl;
        }
        
    };
    
    return 0;
}
