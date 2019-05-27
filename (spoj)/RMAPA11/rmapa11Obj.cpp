// Estradas Escuras (versao lista adjacencia)
// https://www.urionlinejudge.com.br/judge/pt/problems/view/1152
// adaptado de "Reduzindo detalhes em um mapa"
//              http://br.spoj.com/problems/RMAPA11/
// algoritmo  "Prim" 
// Video que ajudou: https://www.youtube.com/watch?v=rsIlC0VeHew
// relacionado: br.spoj.com/problems/REDOTICA/ (resolvido com kruskal)

#include <iostream>
using namespace std;

class Prim{
    private:
        struct vert{
            int 
        }
    
    public:
        Prim(){};
        
};


int main() {
    int m, n, x, y, p;

    cin >> n >> m;
    Prim P;
    for(int i=0;i<m;i++){
        cin >> x >> y >> p;
        P.in(x,y,p);
    }
    
    cout << P.sum() << endl;
    return 0;
}
