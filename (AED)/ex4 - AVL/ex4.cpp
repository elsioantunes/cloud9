#include <iostream>
#include <vector>
#include <algorithm>

#include "avl.h"

using namespace std;

int main()
{
    vector<int> v = { 7, 2, 4, 3, 8, 1, 0, 6, 9, 5 };
    sort(v.begin(), v.end());

    aed2::AVL<int> avl;

    // Insert keys in the avl
    for (int i = 0; i < (int)v.size(); ++i)
    {
        aed2::AVLNode<int> *node = new aed2::AVLNode<int>(v.at(i));
        avl.Insert(node);
    }

    // In order traversal
    avl.PrintInOrder();

    cout << endl;

    // Output AVL in DOT format
    avl.PrintDot(true);

    return 0;
}