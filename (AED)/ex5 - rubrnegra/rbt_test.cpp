#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <cmath>

#include "rbt.h"

#define NUM_KEYS 5
#define NUM_ROUNDS 100

using namespace std;

int main(){
    int seed = (int) chrono::system_clock::now().time_since_epoch().count();
    default_random_engine rndGen(seed);

    vector<int> v;

    for (int i = 1; i <= NUM_KEYS; ++i)
        v.push_back(NUM_KEYS-i);
    
    shuffle(v.begin(), v.end(), rndGen);


    aed2::RBT<int> rbt;
    for (int i = 0; i < (int)v.size(); ++i){
        aed2::RBTNode<int> *node = new aed2::RBTNode<int>(v.at(i));
        rbt.Insert(node);
    }
    cout << endl;

    rbt.PrintDot();

    //rbt.PrintInOrder();

    return 0;
}
