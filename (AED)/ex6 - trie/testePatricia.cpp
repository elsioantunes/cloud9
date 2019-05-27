#include <iostream>
#include <vector>
#include <string>
#include <stack>
using namespace std;

#include "patricia.h"

int main(){
    Patricia<16> pt = new Patricia(16);
    
    //pt.inserir("0");
    //pt.inserir("10");
    //pt.inserir("1");
    //pt.inserir("11");
    //pt.inserir("01");
    //pt.inserir("011");
    pt.inserir("0111110");
    pt.inserir("0110000");
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












