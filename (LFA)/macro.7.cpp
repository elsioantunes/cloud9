#include <iostream>
#include <string>
using namespace std;


void printAfn(string s,string t,string r){
    if(s=="") s = "eps";
    if(t=="") t = "eps";
    if(r=="") r = "eps";
    cout << s << " " << r << " " << t << " " << endl;
}

void constroi(string str){
    string s,r,t;
    for(int i=0; i<str.length();i++){
        s = str.substr(0, i);
        r = s+"a";
        while((r!=str.substr(0,r.length())))
            r = r.substr(1);
        t = s+"b";
        while((t!=str.substr(0,t.length())))
            t = t.substr(1);
        printAfn(s,t,r);
    }
    printAfn(s,s,s);
}

int main() {
    string str, r, s, t;
    constroi("abbbbbabab");
    return 0;
}
