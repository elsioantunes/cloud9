#include <iostream>
using namespace std;

class Cyk{
    private:                                                   
        int regraSize, inicial, kt, kr, n;
        bool *itens, eps;
        struct Regra{int A, B, C, a;};
        Regra *regra;
        string pog;

    public:
        Cyk(int n){
            eps = false;
            kt = 0; kr = 0;
            regraSize = n;
            regra = new Regra[n];
            pog = "";
        };

        void setS(int i, int j, int v){itens[26*(j*n+i)+v] = true;}
        bool getS(int i, int j, int v){return itens[26*(j*n+i)+v];}

        void setGrammar(string r){
            if(!r[1]){eps = true;}
            else if(!r[2]) {
                regra[regraSize-kt-1].A = r[0]-'A';
                regra[regraSize-kt-1].a = r[1];
                if(regra[regraSize-kt-1].A==regra[0].A)
                    pog = pog + r[1];
                kt++;
            }else {
                regra[kr].A = r[0]-'A';
                regra[kr].B = r[1]-'A';
                regra[kr].C = r[2]-'A';
                kr++;
            }
        };

        bool parse(string w){
            if(w=="") return eps;                    /// Caso especial
            if(w.length()==1) {                      //   eu sinceramente nao tenho ideia
                for(int i=0;i<pog.length();i++)      //   de como fazer esse trecho de um
                    if(w[0]==pog[i])return true;     //   jeito mais inteligente.
                return false; 
            }

            n = w.length();
            itens = new bool[n*n*26];
            for(int i=0;i<n*n*26;i++)itens[i]=0;
            for(int i=0;i<n;i++)
                for(int j=regraSize-kt;j<regraSize;j++)
                    if(w[i]==regra[j].a)
                        setS(i,i,regra[j].A);

            for(int l=1; l<n; l++)
                for(int i=0; i+l<n; i++) {
                    int j=i+l;
                    for(int k=i; k<j; k++)
                        for(int A=0;A<kr;A++)
                            if(getS(i,k,regra[A].B) && getS(k+1,j,regra[A].C))
                                setS(i,j,regra[A].A);
                }

            for(int A=0;A<26;A++)
                if(getS(0,n-1,A)!=0 && A==regra[0].A) 
                    return true;
            return false;
        };
};

int main(){
    int n;
    string r;
    cin >> n;
    Cyk p(n);
    for(int i=0;i<n;i++){
        cin >> r;
        p.setGrammar(r);
    }

    string w;
    getline(cin,w);
    while(getline(cin,w))
        cout << (p.parse(w)?"SIM":"NAO")<< endl;

    return 0;
}

