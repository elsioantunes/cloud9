#include <iostream>
#include <vector>
using namespace std;

class Cyk{
    private:                                                   
        int S, regraSize, inicial, kt, kr, n, *pin;
        bool  eps, *itens;
        struct Regra{int A, B, C, a;};
        Regra *regra;

    public:
        Cyk(int n){
            eps = false;
            kt = 0; kr = 0;
            regraSize = n;
            regra = new Regra[n];
        };
        
        void setS(int i, int j, int v){itens[26*(j*n+i)+v-65] = true;}
        bool getS(int i, int j, int v){return itens[26*(j*n+i)+v-65];}

        void setGrammar(string r){
            if(!kt&&!kr) S = r[0];
            if(!r[1]){eps = true;}
            else if(!r[2]) {
                regra[regraSize-kt-1].A = r[0];
                regra[regraSize-kt-1].a = r[1];
                kt++;

            }else {
                regra[kr].A = r[0];
                regra[kr].B = r[1];
                regra[kr].C = r[2];
                kr++;
            }
        };

        bool parse(string w){
            if(w=="") return eps; 
            n = w.length();
            
            itens = new bool[n*n*26];
            for(int i=0;i<n*n*26;i++)
                itens[i]=false;
                
            for(int i=0;i<n;i++)
                for(int j=regraSize-kt;j<regraSize;j++)
                    if(w[i]==regra[j].a)
                        setS(i,i,regra[j].A);

            for(int l=1; l<n; l++)
                for(int i=0; i+l<n; i++) 
                    for(int k=i; k<i+l; k++)
                        for(int A=0;A<kr;A++)
                            if(getS(i,k,regra[A].B) && getS(k+1,i+l,regra[A].C))
                                setS(i,i+l,regra[A].A);

            if(getS(0,n-1,S)) 
                return true;
            return false;
        };
};

int main(){
    int n; string w, r;
    cin >> n; 
    Cyk p(n);
    for(int i=0;i<n;i++)
        cin >> r,
        p.setGrammar(r);

    getline(cin,w);
    while(getline(cin,w))
        cout << (p.parse(w)?"SIM":"NAO")<< endl;

    return 0;
}

