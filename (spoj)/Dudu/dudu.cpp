// Dudu Faz Serviço (Dudu Service Maker)
// https://www.urionlinejudge.com.br/judge/pt/problems/view/1610
 
#include <iostream>
using namespace std;

int n;
bool *adj, *v *r;


bool dfs(int j){
    v[j] = true;
    r[j] = true;
    for(int i=0;i<n;i++){
        if(adj[j*n+i]){
            if(!v[i]){
                dfs(i);
            }else if(r[i]){
                return true;
            }
        }
    }
    r[j] = false;


    return false;
}

bool loop(){
    for(int i=0;i<n;i++)
        v[i]=false;

    for(int i=0;i<n;i++)
        r[i]=false;
    
    for(int i=0;i<n;i++)
        if(dfs(i))
            return true;
    return false;
}

int main() {
    int T, m, x, y;

    cin >> T;
    for(int t=0;t<T;t++){

        cin >> n >> m;

        adj = new bool[n*n];
        v = new bool[n];
        r = new bool[n];
        for(int i=0;i<n*n;i++)
            adj[i]=false;
            
        for(int i=0;i<m;i++){
            cin >> x >> y;
            x--;y--;
            adj[x*n+y]=true;
        }
        
        cout << (loop()?"SIM":"NAO") << endl;
    }
    return 0;
}


 