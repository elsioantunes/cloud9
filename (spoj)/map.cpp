#include <iostream>
#include <map>
using namespace std;


string ddd(string n){
    map <string, string>mp;
    mp["61"] = "Brasilia";
    mp["11"] = "Sao Paulo";
    mp["71"] = "Salvador";
    mp["21"] = "Rio de Janeiro";
    mp["32"] = "Juiz de Fora";
    mp["19"] = "Campinas";
    mp["27"] = "Vitoria";
    mp["31"] = "Belo Horizonte";
    
    if(mp.find(n) == mp.end()) return "DDD nao cadastrado";
    return mp[n];
}

int main(){
    string n, s;
    cin >> n;
    cout << ddd(n) << endl;
    return 0;
}


