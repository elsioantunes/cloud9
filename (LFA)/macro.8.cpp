#include <iostream>
#include <string>
using namespace std;


void printAfn(string s,string t,string r){
    cout << s.length() << " " << r.length() << " " << t.length() << " " << endl;
    if(s=="") s = "eps";
    if(t=="") t = "eps";
    if(r=="") r = "eps";
    //cout << s << " " << r << " " << t << " " << endl;
    
    
}

void constroi(string str){
    string s,r,t;
    for(int i=0; i<str.length();i++){
        // para cada prefixo s de str
        // fazemos r = s+'a'
        // e procuramos pelo sufixo de r
        // em outro prefixo de str, até o epslon. 
        // Analogo para t.
        s = str.substr(0, i);
        r = s+"a";
        while((r!=str.substr(0,r.length())))
            r = r.substr(1);
        t = s+"b";
        while((t!=str.substr(0,t.length())))
            t = t.substr(1);
        printAfn(s,t,r);
    }
    printAfn(str,str,str);
}

int main() {
    string str, r, s, t;
    int n;
    while (true){
        cin >> n;
        cout << endl << n << endl;
        if(!n)break;
        for(int i=0;i<n;i++)
            cin >> s >> r >> t;
            constroi(s);
    }
    
    return 0;
}
