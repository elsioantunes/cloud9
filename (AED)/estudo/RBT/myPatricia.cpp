#include <iostream>
using namespace std;

class RBT{
    private:
        struct Node{
            bool sentinela;
            int n, cor, id;
            Node *pai, *esq, *dir;
            Node(){
                n = cor = 0;
                pai = esq = dir = NULL;
                sentinela = true;
            }
        };
        Node *root, *NIL;
        int cont;

    public:
        RBT(){
            NIL = new Node();
            root = NIL;
        };

        void insert(int val){
            Node *pai = NIL, *atual = root;
            while(!atual->sentinela){
                pai = atual;
                atual = (val<atual->n)?
                    atual->esq:atual->dir;
            }
            Node *novo = new Node();
            novo->n = val;
            novo->pai = pai;
            novo->cor = 1;
            novo->esq = NIL;
            novo->dir = NIL;
            novo->sentinela = false;
            if(!pai->sentinela)
                if(val<pai->n) 
                    pai->esq = novo;
                else 
                    pai->dir = novo;
            else
                root = novo;
            
            insertFixUp(novo);
        }
        
        void insertFixUp(Node *novo){
            while(novo->pai->cor){ // we have a violation, uh!
                if(novo->pai==novo->pai->pai->esq){
                    if(novo->pai->pai->dir->cor){ // tio red?
                        novo->pai->cor = 0;
                        novo->pai->pai->dir->cor = 0;
                        novo->pai->pai->cor = 1;
                        novo = novo->pai->pai;
                    }else{
                        if(novo==novo->pai->dir){  // joelho
                            novo = novo->pai;
                            rotateLeft(novo);
                        }
                        novo->pai->cor = 0;
                        novo->pai->pai->cor = 1;
                        rotateRight(novo->pai->pai);
                    }
                    
                }else{
                    if(novo->pai->pai->esq->cor){ // tio red?
                        novo->pai->cor = 0;
                        novo->pai->pai->esq->cor = 0;
                        novo->pai->pai->cor = 1;
                        novo = novo->pai->pai;
                    }else{
                        if(novo==novo->pai->esq){  // joelho
                            novo = novo->pai;
                            rotateRight(novo);
                        }
                        novo->pai->cor = 0;
                        novo->pai->pai->cor = 1;
                        rotateLeft(novo->pai->pai);
                    }
                }
            }
            root->cor = 0;
        }
        
        void rotateLeft(Node *x){
            Node *y = x->dir;
            x->dir = y->esq;
            y->esq->pai = x->pai;
            y->pai = x->pai;
            if(x->pai->sentinela)
                root = y;
            else
                if(x==x->pai->esq)
                    x->pai->esq=y;
                else
                    x->pai->dir=y;
            y->esq = x;
            x->pai = y;
        }

        void rotateRight(Node *x){
            Node *y = x->esq;
            x->esq = y->dir;
            y->dir->pai = x->pai;
            y->pai = x->pai;
            if(x->pai->sentinela)
                root = y;
            else
                if(x==x->pai->dir)
                    x->pai->dir=y;
                else
                    x->pai->esq=y;
            y->dir = x;
            x->pai = y;
        }


        Node *maximo(Node *y){
            while(!y->dir->sentinela)
                y = y->dir;
            return y;
        }
        
        Node *minimo(Node *y){
            while(!y->esq->sentinela)
                y = y->esq;
            return y;
        }
        
        Node *sucessor(Node *z){
            return maximo(z->esq);
        }
        
        Node *predecessor(Node *z){
            return minimo(z->dir);
        }
        
        void removeNode(Node *z){

            Node *x, *y;
            if(z->esq->sentinela || z->dir->sentinela){
                y = z;
            }else{
                y = sucessor(z);
            }
            

            x = (y->esq->sentinela)?
                y->dir : y->esq;
            

            x->pai = y->pai;
            

            if(y->pai->sentinela){
                root = x;
            }else{
                if(y == y->pai->esq)
                    y->pai->esq = x;
                else
                    y->pai->dir = x;
            }
            
            z->n = y->n;
            
            if(!y->cor)
                deleteFixup(x);
            
            delete y;
        }
        
        void deleteFixup(Node *x){
            while(x!=root && !x->cor){
                if(x == x->pai->esq){
                    Node *w = x->pai->dir;   // irmão
                    if(w->cor){              // se vermelho
                        w->cor = 0;          // então  irmão preto
                        x->pai->cor = 1;     // e pai vermelho
                        rotateLeft(x->pai);  // gira pai pra esquerda
                        w = x->pai->dir;     // 
                    }
                    if(!w->esq->cor && !w->dir->cor){ // se sobrinhos pretos
                        w->cor = 1;                   // então irmão vermelho 
                        x = x->pai;                   // x aponta pra pai de x

                    }else{
                        if(!w->dir->cor){     //sobrinho esquerdo preto
                            w->esq->cor = 0;
                            w->cor = 1;
                            rotateRight(w);
                            w = x->pai->dir;
                        }
                        w->cor = x->pai->cor;
                        w->pai->cor = 0;
                        rotateLeft(x->pai);
                        x = root;
                    }

                }else{
                    Node *w = x->pai->esq;
                    if(w->cor){           
                        w->cor = 0;       
                        x->pai->cor = 1;  
                        rotateRight(x->pai);
                        w = x->pai->dir;    
                    }
                    if(!w->esq->cor && !w->dir->cor){
                        w->cor = 1;                  
                        x = x->pai;                  

                    }else{
                        if(!w->esq->cor){     
                            w->dir->cor = 0;
                            w->cor = 1;
                            rotateLeft(w);
                            w = x->pai->esq;
                        }
                        w->cor = x->pai->cor;
                        w->pai->cor = 0;
                        w->esq->cor = 0;
                        rotateRight(x->pai);
                        x = root;
                    }
                }
            }
            x->cor = 0;
        }
        
        
        Node *search(int val){
            Node *atual = root;
            while(!atual->sentinela)
                if(val == atual->n)
                    return atual;
                else
                    atual = val>atual->n?
                        atual->dir: atual->esq;
            return NULL;
        }
        
        int maximo(){
            return maximo(root)->n;
        }

        int minimo(){
            return minimo(root)->n;
        }
        
        void mostra(){
            cont = 0;
            cout << "digraph {" << endl;
            bfs_vert(root);
            bfs_arest(root);
            cout << "}" << endl;
        }
        
        void bfs_vert(Node *no){
            if(!no->sentinela){
                no->id = cont++;
                cout << "\t" <<  no->id;
                cout << " [label=\"" << no->n<<"/"<<no->id; 
                cout << "\" style=filled fillcolor=";
                cout << (no->cor?"indianred1]":"lightgray]") << endl;
                bfs_vert(no->esq);
                bfs_vert(no->dir);
            }
        }

        void bfs_arest(Node *no){
            if (!no->sentinela){
                if (!no->esq->sentinela){
                    cout << "\t" << no->id << " -> " << no->esq->id << " [dir=none];" << endl;
                    bfs_arest(no->esq);
                }
                if (!no->dir->sentinela){
                    cout << "\t" << no->id << " -> " << no->dir->id << " [dir=none];" << endl;
                    bfs_arest(no->dir);
                }
            }
        }
        
};

int main(){
    RBT rbt;
    
    //for(int i=0;i<100;i++) rbt.insert(i);
    
    
    int n, v;
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> v;
        rbt.insert(v);
    };
    
    //rbt.removeNode(rbt.search(4));
    
    

    rbt.mostra();
    
    cout << rbt.minimo() << endl;
    
    
    
    return 0;
}












