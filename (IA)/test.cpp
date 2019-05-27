#include <iostream>
using namespace std;

int lin = 7, col = 20, count=0, count2=1;
int buf[7*20], resp[(7-2)*(20-2)-1];

int draw(){
    // apenas lembre que 
    // a imagem está espelhada
    // horizontalmente
    cout << count << endl;
    for(int i=0;i<lin*col;i++){
        cout << buf[i] << " ";
        if(i%col==col-1) cout << endl;
    }
    cout << endl;
}

int wall(int i){
    return 
        i%col==col-1 || i%col==0 || 
        i<col || i>(lin-1)*col;
}

void reset(){
    for(int i=0;i<lin*col;i++)
        buf[i] = wall(i);
}

int vizinho(int i, int n){
    return (i==n+1|| i==n-1|| i==n+col|| i==n-col) && !wall(i);
}

int DFS(int n){
    buf[n] = 7;

    if(count == (lin-2)*(col-2)-1) 
        return true;

    count++;
    for(int i=0;i<lin*col;i++)
        if(vizinho(i,n) && buf[i]==0 && DFS(i)){
            resp[count2++] = i;
            return true;
        }
    count--;
    buf[n] = 0;
    return false;
}

int main(){
    reset();
    int v = lin*col/2;
    cout << v << endl;
    DFS(v);
    
    
    string card;
    int len = sizeof(resp)/4;

    for(int i=0;i<len;i++)
        cout << resp[len-i] << " ";
    cout << endl;

    /*
    for(int i=0;i<len;i++){
        int u = resp[len-i];
        if(v-u == col) card = "'North'";
        if(v-u == -col) card = "'South'";
        if(v-u == 1) card = "'East'";
        if(v-u == -1) card = "'West'";
        v = u;
        cout << card << ", ";
    }
    cout << endl;
    */
    
    
}