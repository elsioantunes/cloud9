#include <iostream>
using namespace std;
struct Regra{string A, B, C, a;};

int main(){
    Regra *regra;
    string r, w;
    int n, nr=-1;
    cin >> n;
    regra = new Regra[n];
    for(int i=0;i<n;i++){
        cin >> r;
        
        regra[++nr].A = r[0];
        if(!r[1]){
            // eps
            regra[nr].a = "";
            regra[nr].B = "";
            regra[nr].C = "";
        }else if(!r[2]){
            // terminal
            regra[nr].a = r[1];
            regra[nr].B = "";
            regra[nr].C = "";
        }else{
            // A --> BC
            regra[nr].a = "";
            regra[nr].B = r[1];
            regra[nr].C = r[2];
        }
    }
    
    for(int i=0;i<nr;i++){
        cout << regra[i].A << "-->" << regra[i].B << regra[i].a << regra[i].C << endl;
    }
    

    /*
    getline(cin,w);
    while(getline(cin,w)){
        cout << (ret?"SIM":"NAO") << endl;
    }
    */
    return 0;
}

