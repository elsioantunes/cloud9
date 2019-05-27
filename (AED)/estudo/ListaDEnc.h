template <typename tipo>
class ListaDEnc{
public:
    // construtor
    ListaDEnc(){
        ini = new Celula;
        ini->prox=ini;
        ini->ant=ini;
        nelem = 0;
        cursor = 0;
    };

    // destrutor
    ~ListaDEnc(){
        Celula *aux;
        while(ini!=ini->ant){
            aux = ini->ant;
            ini->ant = ini->ant->ant;
            delete aux;
        }
        delete ini;
    };

    // insere um item no fnal da lista
    void insere(const tipo &elem){
        Celula *nova = new Celula;
        nova->el = elem;
        nova->prox = ini;
        nova->ant = ini->ant;
        ini->ant->prox = nova;
        ini->ant = nova;
        nelem++;
        cursor = nelem;
    };

    // retorna o elemento da posição pos.
    tipo elemento(int pos){
        Celula *aux = ini->prox;
        for(int i=0;i<pos;i++)
            aux=aux->prox;
        return aux->el;
    };

    // retorna o numero de elementos da lista
    int tamanho(){
        return nelem;
    };

    // insere um item numa posição específica
    void insere_pos(const tipo &elem, int pos){
        if(pos>nelem||pos<0) return;
        Celula *aux = ini->prox;
        for(int i=0;i<pos;i++)
            aux=aux->prox;
        Celula *nova = new Celula;
        nova->el = elem;
        nova->prox = aux;
        nova->ant = aux->ant;
        nova->ant->prox = nova;
        nova->prox->ant = nova;
        nelem++;
    };

    // remove um item numa posição específica
    bool remove_pos(int pos){
        if(pos>=nelem||pos<0)return false;
        Celula *aux = ini->prox;
        for(int i=0;i<pos;i++)
            aux = aux->prox;
        aux->ant->prox = aux->prox;
        aux->prox->ant = aux->ant;
        delete aux;
        nelem--;
        return true;
    };

    // retorna a posição de um elemento da lista. -1 se não encontrar.
    int pesquisa(const tipo &elem){
        Celula *aux = ini->prox;
        for(int i=0;i<nelem;i++){
            if(aux->el==elem)return i;
            aux = aux->prox;
        }
        return -1;
    };

    // remove elem da lista
    bool remove(const tipo &elem){
        Celula *aux = ini->prox;
        for(int i=0;i<nelem;i++){
            if(aux->el==elem){
                aux->ant->prox = aux->prox;
                aux->prox->ant = aux->ant;
                delete aux;
                nelem--;
                return true;
            }
            aux = aux->prox;
        }
        return false;
    };

    void volta_cursor(){
        cursor = 0;
    };

    bool tem_proximo(){
        return cursor<nelem;
    };

    tipo proximo(){
        cursor++;
        Celula *aux = ini->prox;
        for(int i=0;i<cursor;i++)
            aux=aux->prox;
        return aux->el;
    };

private:
    struct Celula{
        tipo el;
        Celula *prox, *ant;
    };
    Celula *ini;
    int nelem, cursor;
};
