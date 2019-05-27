#include <iostream>
#include "trie.h"
using namespace std;

int main(){
    
    cout << "Trie." << endl;

    aed2::Trie trie;

    // Add strings to Trie
    trie.Insert("trie");
    trie.Insert("tree");
    trie.Insert("try");
    trie.Insert("trunk");
    trie.Insert("tap");
    trie.Insert("train");
    trie.Insert("trainee");
    trie.Insert("tray");
    trie.Insert("tram");
    trie.Insert("trait");
    trie.Insert("traitor");
    trie.Insert("data");
    trie.Insert("date");
    trie.Insert("datum");

    //trie.PrintPreOrder();
    trie.PrintDot();

    return 0;
}

