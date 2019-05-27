#include <iostream>
using namespace std;


class Trie{
    private:
        struct Node{
            int n, chave;
            bool existe;
            Node *nums; 
            Node(){
                n = 0;
                chave = -1;
                existe = false;
                nums = new int[256];            
            }
        };
        
        Node raiz;
        int *out, indice, chave; 
        bool existe;

    public:
       Trie(){}
       void inserir(int *arr){
           Node atual = this->raiz;
           atual->n ++;
           
       }
};


class LZW{
    LZW(){}
    int *decode(int *code){
    }
};