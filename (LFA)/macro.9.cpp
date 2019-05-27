#include <iostream>
#include <string>
using namespace std;

int adj[100000][26];
int len;

void printAfn(string s,string t,string r){
    adj[s.length()][0] = r.length();
    adj[s.length()][1] = t.length();
    if(s=="") s = "eps";
    if(t=="") t = "eps";
    if(r=="") r = "eps";
    cout << s << " " << r << " " << t << " " << endl;
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
    len = str.length();
}

int percorre(string w){
    int q = 0;
    for(unsigned int i=0;i<w.length();i++)
        q = adj[q][w[i]-97];
    return (q==len?1:0);
};

int main() {
    string w;
    int n;
    cin >> w >> n;
    constroi(w);
    getline(cin, w);
    for(int i=0;i<n;i++){
        getline(cin, w);
        cout << percorre(w) << endl;
    }
    return 0;
}
