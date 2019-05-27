#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <cmath>

#include "avl.h"

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
    for (int i = 1; i <= NUM_KEYS; ++i)
        v.push_back(i);
    shuffle(v.begin(), v.end(), rndGen);

    // Create avl
    aed2::AVL<int> avl;
    for (int i = 0; i < (int)v.size(); ++i)
    {
        aed2::AVLNode<int> *node = new aed2::AVLNode<int>(v.at(i));
        avl.Insert(node);
    }

    // Perform several rounds of random removals followed by random insertions
    // For each round, half the keys are inserted and removed
    vector<int> vcopy = v;

    for (int i = 0; i < NUM_ROUNDS; ++i)
    {
        vector<int> removedKeys;
        shuffle(vcopy.begin(), vcopy.end(), rndGen);

        cout << endl;
        cout << "Round #" << i << endl;

        // Remove half the keys
        for (int j = 0; j < (int)vcopy.size() / 2; ++j)
        {

            int key = vcopy.at(j);
            aed2::AVLNode<int> *node = avl.Search(key);
            if (node)
            {
                removedKeys.push_back(key);
                delete avl.Remove(node);
            }
        }

        // Insert removed keys in a different order
        shuffle(removedKeys.begin(), removedKeys.end(), rndGen);
        for (int j = 0; j < (int)removedKeys.size(); ++j)
        {
            int key = removedKeys.at(j);
            aed2::AVLNode<int> *node = new aed2::AVLNode<int>(key);
            avl.Insert(node);
        }

        cout << "AVL height: " << avl.height();
        cout << "\t Optimal height: " << (int)log2(v.size()) << endl;
    }

    cout << endl;

    avl.PrintDot(true);

    avl.PrintInOrder();

    return 0;
}