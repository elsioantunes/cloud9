#include <iostream>
#include <string>
using namespace std;

string f(string s,string r){};

int main() {
    string str, r, s, t;
    
    
    str = "abbbabbaa";


    s = "abbb";

    r = s+"a";
    while(1){
        if(r==str.substr(0,r.length())) break;
        r = r.substr(1);
    }
    
    t = s+"b";
    while(1){
        if(t==str.substr(0,t.length())) break;
        t = t.substr(1);
    }
    
    cout << ":" << r << " " << t << ":" << endl;
    
    
    
    
    

    
    
    
    
    
    return 0;
    
    
    
    int n;
    while(cin >> str) {
        for(int i=0; i<str.length(); i++) {
            r = str.substr(0,i);
            s = r + 'a';
            t = r + 'b';
            cout << f(str, r) << " " << f(str, s) << " " << f(str, t) << endl;
        }
        cout << str << " " << str << " " << str << endl;
        cout << endl;
    }
    return 0;
}
