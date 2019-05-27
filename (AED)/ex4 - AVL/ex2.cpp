#include <iostream>
#include <vector>

#include "bst.h"
#include "avl.h"

using namespace std;

int main()
{
    vector<int> v = { 7, 2, 4, 3, 8, 1, 0, 6, 9, 5 };

    /*
    aed2::BST<int> bst;

    // Insert keys in the bst
    for (int i = 0; i < (int)v.size(); ++i){
        aed2::BSTNode<int> *node = new aed2::BSTNode<int>(v.at(i));
        bst.Insert(node);
    }

    // In order traversal
    // bst.PrintInOrder();


    // Output BST in DOT format
    bst.PrintDot(true);
    */
	

    aed2::AVL<int> avl;

    // Insert keys in the bst
    for (int i = 0; i < 21; ++i){
        aed2::AVLNode<int> *node = new aed2::AVLNode<int>(i);
        avl.Insert(node);
    }

    avl.PrintDot(true);
	
    return 0;
}

