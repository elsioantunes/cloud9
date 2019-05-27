#include "mytrie.h"


int main (){
    Trie trie;

    
    int vec[] = {1,2,3,4,5};
    vector<int> v1(vec,vec+sizeof(vec)/4);
    trie.insert(v1);

    int vec2[] = {2,3,4,5,6};
    vector<int> v2(vec2,vec2+sizeof(vec2)/4);
    trie.insert(v2);

    int vec3[] = {3,4,5,7,5,4};
    vector<int> v3(vec3,vec3+sizeof(vec3)/4);
    trie.insert(v3);

    trie.list();
    
    
    
    return 0;
}