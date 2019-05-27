#include <iostream>
#include <vector>
#include <string>
#include <stack>
using namespace std;

class Patricia{
    private:
        struct Node{
            int i;
            string str;
            Node *pai, *esq, *dir;
            Node(){
                str = "";
                i = 0;
                pai = NULL;
                esq = NULL;
                dir = NULL;
            }
        };
        Node *root;

    public:
        Patricia(){
            root = new Node();
        };
        


        bool busca(string str){
            Node *atual = root;
            while (atual->esq){
                atual = (str[16 - 1 - atual->i] - '0')?
                    atual->dir : atual->esq;
            }
            return str == atual->str;
        }
        
        
        
        void inserir(string str){
            //if(busca(str)) return;
            cout << atual->str << endl;
            Node *atual = root;
            
            while (atual->esq){
                atual = (str[16-1-atual->i]-'0')?
                    atual->dir : atual->esq;
            }

            if(!atual->pai && atual->str==""){
                atual->str = str;

            }else{

                int i = 0;
                while(i<16 && atual->str[16-1-i] == str[16-1-i])
                    i++;
                
                if(i==16) return; // already exists!

                bool daEsq;
                Node *pai = atual->pai;
        

                if(pai)
                    daEsq = (atual == pai->esq);

                
                while(pai && pai->i > i){
                    if(pai->pai)
                        daEsq = (pai == pai->pai->esq);
                    atual = pai;
                    pai = pai->pai;
                }
                
                Node *novo = new Node();
                novo->i = i;
                novo->pai = pai;


                if(!pai){
                    root = novo;

                }else{
                    if(daEsq){
                        pai->esq = novo;
                    }else{
                        pai->dir = novo;
                    }
                }
                
                
                Node *folha = new Node();
                      folha->str = str;
                      folha->pai = novo;
                
                atual->pai = novo; 
                
                if(folha->str[16-1-i]-'0'){
                    novo->esq = atual;
                    novo->dir = folha;
                }else{
                    novo->esq = folha;
                    novo->dir = atual;
                }
            }
            return;
        }
        

        void mostra(Node *no){
            if(no){
                if(no->dir){
                    mostra(no->esq);
                    mostra(no->dir);
                }else{
                    cout << ":"<< no->str <<endl;
                }
            }
        }
        
        void mostra(){
            mostra(root);
        }
};

int main(){
    Patricia pt;
    
    //pt.inserir("0");
    //pt.inserir("10");
    //pt.inserir("1");
    //pt.inserir("11");
    //pt.inserir("01");
    //pt.inserir("011");
    pt.inserir("0111110");
    pt.inserir("0110000");
    pt.inserir("01101");
    //pt.inserir("01101");

    pt.mostra();
    
    cout << endl;
    cout <<"0 "<< (pt.busca("0")?"ok": "não encontrado")<< endl;
    cout <<"1 "<< (pt.busca("1")?"ok": "não encontrado")<< endl;
    cout <<"10 "<< (pt.busca("10")?"ok": "não encontrado")<< endl;
    cout <<"11 "<< (pt.busca("11")?"ok": "não encontrado")<< endl;
    cout <<"01 "<< (pt.busca("01")?"ok": "não encontrado")<< endl;
    cout <<"011 "<< (pt.busca("011")?"ok": "não encontrado")<< endl;
    cout <<"0111110 "<< (pt.busca("0111110")?"ok": "não encontrado")<< endl;
    cout <<"0110000 "<< (pt.busca("0110000")?"ok": "não encontrado")<< endl;
    cout <<"01101 "<< (pt.busca("01101")?"ok": "não encontrado")<< endl;

    return 0;
}












