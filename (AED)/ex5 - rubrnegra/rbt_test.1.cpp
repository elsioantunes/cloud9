#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <cmath>

#include "rbt.h"

#define NUM_KEYS 63
#define NUM_ROUNDS 100

using namespace std;

int main()
{
    // Set up pseudorandom number generator
    int seed = (int) chrono::system_clock::now().time_since_epoch().count();
    default_random_engine rndGen(seed);

    // Fill vector of keys
    vector<int> v;

    // Increasing order
    for (int i = 1; i <= NUM_KEYS; ++i)
        v.push_back(i);

    // Decreasing order
    //for (int i = 1; i <= NUM_KEYS; ++i)
    //    v.push_back(NUM_KEYS - i + 1);

    // Zig-zag order
    //for (int i = 1; i <= NUM_KEYS / 2; ++i)
    //{
    //    v.push_back(i);
    //    v.push_back(NUM_KEYS - i + 1);
    //}

    //shuffle(v.begin(), v.end(), rndGen);

    // Create rbt
    aed2::RBT<int> rbt;
    for (int i = 0; i < (int)v.size(); ++i)
    {
        aed2::RBTNode<int> *node = new aed2::RBTNode<int>(v.at(i));
        rbt.Insert(node);
    }
/*
    // Perform several rounds of random removals followed by random insertions
    // For each round, half the keys are inserted and removed
    vector<int> vcopy = v;

    for (int i = 0; i < NUM_ROUNDS; ++i)
    {
        vector<int> removedKeys;
        shuffle(vcopy.begin(), vcopy.end(), rndGen);

        cout << "Round #" << i << endl;

        // Remove half the keys
        for (int j = 0; j < (int)vcopy.size() / 2; ++j)
        {

            int key = vcopy.at(j);
            aed2::RBTNode<int> *node = rbt.Search(key);
            if (node)
            {
                removedKeys.push_back(key);
                delete rbt.Remove(node);
            }
        }

        // Insert removed keys in a different order
        shuffle(removedKeys.begin(), removedKeys.end(), rndGen);
        for (int j = 0; j < (int)removedKeys.size(); ++j)
        {
            int key = removedKeys.at(j);
            aed2::RBTNode<int> *node = new aed2::RBTNode<int>(key);
            rbt.Insert(node);
        }
    }
*/
    cout << endl;

    rbt.PrintDot();

    rbt.PrintInOrder();

    return 0;
}
