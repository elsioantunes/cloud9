#include <iostream>
#include <vector>
#include <string>
#include <stack>
using namespace std;

class Trie{
    private:
        struct Node{
            vector<Node*> filho;
            bool fim;
            int n;
            Node(){
                n = 0;
                fim = false;
                filho.resize(26);
            };
        };
        Node *root;

    public:
        Trie(){
            root = new Node();
        };
        


        bool busca(string str){
            Node *atual = root;
            for(int i=0;i<str.length();i++){
                int L = str[i] - 'a';
                if(!atual->filho[L]) return false;
                atual = atual->filho[L];
            }
            return atual->fim;
        }
        
        
        
        void inserir(string str){
            //if(busca(str)) return;
            Node *atual = root;
            atual->n++;
            for(int i=0;i<str.length();i++){
                int L = str[i] - 'a';
                if(!atual->filho[L])
                    atual->filho[L] = new Node();
                atual->filho[L]->n++;
                atual = atual->filho[L];
            }
            atual->fim = true;
            return;
        }
        
        
        void remover(){
            if(!busca(str)) return;
            Node *atual = root;
            atual->n--;
            for(int i=0;i<str.length();i++){
                int L = str[i] - 'a';
                atual->filho[L]->n--;
                if(!atual->filho[L]->n){
                    // deletar essa lista ligada
                    // sai desse loop!
                }else{
                    atual = atual->filho[L];    
                }
            }
            atual->fim = false;
            return;
        }
        
        
        void mostrar(Node *no, string str){
            if(no->fim) cout<< str << endl;
            for(int i=0;i<26;i++)
                if(no->filho[i])
                    mostrar(no->filho[i], str + (char)(i+'a'));
        }
        void mostrar(){
            mostrar(root, "");
        }
        

};

int main(){
    Trie trie;
    
    trie.inserir("trie");
    trie.inserir("tree");
    trie.inserir("try");
    trie.inserir("trunk");
    trie.inserir("tap");
    trie.inserir("train");
    trie.inserir("trainee");
    trie.inserir("tray");
    trie.inserir("tram");
    trie.inserir("trait");
    trie.inserir("traitor");
    trie.inserir("elsio");
    trie.inserir("data");
    trie.inserir("date");
    trie.inserir("datum");
    trie.inserir("elsio");

    trie.mostrar();
    trie.remover();
    
    
    
    cout << "datum: " << trie.busca("datum") << endl;
    cout << "elsio: " << trie.busca("elsio") << endl;
    cout << "train: " << trie.busca("train") << endl;
    cout << "traine: " << trie.busca("traine") << endl;
    cout << "trainee: " << trie.busca("trainee") << endl;
    
    
    
    return 0;
}












