#include <iostream>
using namespace std;

int n, m;
bool *itens;
struct Regra{int A, B, C, a;};
Regra *regra;

bool getS(int i, int j, int v){return itens[26*(j*n+i)+v];}


int main(){
    string w, r;
    bool ret = false;
    int kr = 0;
    
    cin >> n;
    regra = new Regra[n];
    for(int i=0;i<n;i++){
        cin >> r;
        if(!r[1]){ret = true;}
        regra[kr].A = r[0]-'A';
        regra[kr].a = r[1];
        regra[kr].B = r[1]-'A';
        regra[kr].C = r[2]-'A';
        kr++;
    }

    getline(cin,w);
    while(getline(cin,w)){
        if(w!=""){ 
            n = w.length();
            itens = new bool[n*n*26];
            for(int i=0;i<n*n*26;i++)itens[i]=0;
            for(int i=0;i<n;i++)
                for(int j=0;j<kr;j++)
                    if(w[i]==regra[j].a)
                        itens[26*(i*n+i)+regra[j].A] = true;


            int k26 = 26;
            int n26 = n*k26;
            
            int L26 = 0;
            int L26n = 0;
            for(int l=1; l<n; l++){
                L26 += k26;
                L26n += n26;
                int i26 = -k26;
                int i26n = -n26;
                for(int i=0; i<n-l; i++) {
                    i26 += k26;
                    i26n += n26;
                    int bb =        i26;
                    int aa = i26n + i26 + L26n;
                    int cc = i26n       + L26n + k26;
                    for(int A=0;A<kr;A++){
                        int kn = i26n;
                        for(int k=i26; k < i26 + L26; k+=k26){
                            itens[aa +        regra[A].A] |= 
                            itens[bb + kn  +  regra[A].B] && 
                            itens[cc + k    + regra[A].C];
                            kn += n26 ; 
                        }
                    }
                }
            }
    
            ret = false;
            for(int A=0;A<26;A++)
                if(itens[26*((n-1)*n)+A] && A==regra[0].A)
                    ret = true;
        }
        cout << (ret?"SIM":"NAO") << endl;
    }
    return 0;
}

