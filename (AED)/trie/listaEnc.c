//https://www.ime.usp.br/~pf/algoritmos/aulas/lista.html
#include <stdio.h>
#include <stdlib.h>


typedef struct Node Node;
struct Node{
    int n;
    Node *next;
};

Node *lista;

Node *newnode(){
    Node *p;
    p = malloc(sizeof(Node));
    p->next = NULL;
    return p;
}

void inserir(int n){
    Node *p;
    p = newnode();
    p->n = n;
    p->next = lista->next;
    lista->next = p;
}

void imprime(){
    Node *p;
    for(p = lista->next; p; p = p->next)
        printf("%d\n", p->n);
}

void imprime2(Node *p){
    if(p){
        imprime2(p->next);
        printf("%d\n", p->n);
    }
}

int main(){
    int i;
    
    lista = newnode();
    
    inserir(1);
    inserir(2);
    inserir(69);
    imprime2(lista);
    
    return 0;
}
