#ifndef BST_H
#define BST_H

#include <iostream>

namespace aed2
{

// Forward declaration of BST class.
template<class T>
class BST;

///////////////////////////////////////////////////////////////////////////////
/// BST node.
///
/// Implements a binary search tree node.
///////////////////////////////////////////////////////////////////////////////
template <class T>
class BSTNode
{
    friend class BST<T>;

public:
    BSTNode(T& key);

    /// Node key getter.
    const T& key() const { return _key; }

protected:
    T _key; ///< Node key.
    BSTNode<T>* _parent; ///< Parent node.
    BSTNode<T>* _left;   ///< Left node.
    BSTNode<T>* _right;  ///< Right node.
    int _depth; ///< Node depth (0 to tree height).
    int _height; ///< Height of the subtree rooted at this node.

    void UpdateHeight();

private:
    int _nodeId; ///< Used by PrintDot.
};

///////////////////////////////////////////////////////////////////////////////
/// Constructor.
///
/// \param key Node key.
///
/// \remark Key type must implement a copy constructor.
///////////////////////////////////////////////////////////////////////////////

template <class T>
BSTNode<T>::BSTNode(T& key) : _parent(nullptr), _left(nullptr), _right(nullptr)
{
    _key = key; // Make a copy of the key
    _depth = 0;
    _height = 0;
    _nodeId = 0;    
}







///////////////////////////////////////////////////////////////////////////////
/// Updates the parameter _height of this node.
///
/// The height of this node is computed as the maximum height between its
/// left and right (non-leaf) subtrees, plus one. This is a O(1) operation.
///////////////////////////////////////////////////////////////////////////////
template <class T>
void BSTNode<T>::UpdateHeight()
{
    int hl = (_left ? _left->_height : 0);
    int hr = (_right ? _right->_height : 0);
    _height = (hl > hr ? hl : hr);

    if (_left || _right)
        _height++;
}

///////////////////////////////////////////////////////////////////////////////
/// BST class.
///
/// Implements a binary search tree.
///////////////////////////////////////////////////////////////////////////////
template <class T>
class BST
{
public:
    BST(std::ostream& stream = std::cout);

    void PrintInOrder();
    void PrintDot(bool printNodeHeight = false);

    BSTNode<T>* Search(const T& key);
    void Insert(BSTNode<T>* node);
    BSTNode<T>* Remove(BSTNode<T>* node);
    BSTNode<T>* Minimum(BSTNode<T>* node);
    BSTNode<T>* Maximum(BSTNode<T>* node);
    BSTNode<T>* Successor(BSTNode<T>* node);
    BSTNode<T>* Predecessor(BSTNode<T>* node);

    /// Node key getter.
    int height() const { return _root->_height; }

protected:
    BSTNode<T>* _root; ///< Root node.

    std::ostream& _stream; ///< Output stream used by tree walks.

    void PrintInOrderRec(BSTNode<T>* node);
    void PrintDotNodeRec(BSTNode<T>* node, bool printNodeHeight);
    void PrintDotEdgeRec(BSTNode<T>* node);
    void DecreaseDepthRec(BSTNode<T>* node);
    void UpdateHeightUp(BSTNode<T>* node);

private:
    int _nullNodeCount; ///< Internal counter of PrintDot...
    int _nodeIdCount; ///< Internal counter of PrintDot...

    void UpdateIdRec(BSTNode<T>* node);
    void PrintDotNullNode();
    void PrintDotNullEdge(BSTNode<T>* node);
};

///////////////////////////////////////////////////////////////////////////////
/// Constructor.
///////////////////////////////////////////////////////////////////////////////
template <class T>
BST<T>::BST(std::ostream& stream) : _root(nullptr), _stream(stream)
{
}

///////////////////////////////////////////////////////////////////////////////
/// Searches the given key in the tree.
///
/// \param key Search key.
///
/// \return Pointer to the node found or nullptr if not found.
///////////////////////////////////////////////////////////////////////////////
template <class T>
BSTNode<T>* BST<T>::Search(const T& key)
{
    BSTNode<T>* node = _root;

    while (node && key != node->_key)
    {
        node = (key < node->_key) ? node->_left : node->_right;
    }

    return node;
}

///////////////////////////////////////////////////////////////////////////////
/// Inserts a given node in the tree.
///
/// \param node Pointer to the node to be inserted.
///////////////////////////////////////////////////////////////////////////////
template <class T>
void BST<T>::Insert(BSTNode<T>* z)
{
    if (!z)
        return;

    BSTNode<T>* x = _root;
    BSTNode<T>* y = nullptr;

    // Descend to a leaf
    while (x)
    {
        y = x;
        x = (z->_key < x->_key) ? x->_left : x->_right;
    }

    z->_parent = y;

    if (!y)
    {
        z->_depth = 0;
        _root = z; // Tree was empty
    }
    else
    {
        z->_depth = z->_parent->_depth + 1;
        if (z->_key < y->_key)
            y->_left = z;
        else
            y->_right = z;
    }

    UpdateHeightUp(z);
}

///////////////////////////////////////////////////////////////////////////////
/// Removes the given node from the tree.
///
/// \param node Pointer to the node to be removed.
///
/// \return Pointer to the removed node or nullptr if the removal has failed.
///////////////////////////////////////////////////////////////////////////////
template <class T>
BSTNode<T>* BST<T>::Remove(BSTNode<T>* z)
{
    if (!z)
        return nullptr;

    BSTNode<T>* y = (!z->_left || !z->_right) ? z : Successor(z);
    BSTNode<T>* x = (y->_left) ? y->_left : y->_right; // Child of y
    BSTNode<T>* r = z;

    // Case 1: y = z
    //         x = nil
    // Case 2: y = z
    //         x = y->_left | y->_right
    // Case 3: y = successor(z)
    //         x = y->_left | y->_right

    if (x)
    {
        x->_parent = y->_parent;
        // Decrease depth of x and below
        DecreaseDepthRec(x);
    }

    if (!y->_parent) // y doesn't have parent
    {
        _root = x;
    }
    else if (y == y->_parent->_left) // y is left child of its parent
    {
        y->_parent->_left = x;
    }
    else // y is right child its parent
    {
        y->_parent->_right = x;
    }

    // Case 3 only (move key from successor to z)
    if (y != z)
    {
        UpdateHeightUp(x);
        z->_key = y->_key;
        r = y;       
    }

    UpdateHeightUp(r);

    return r;
}

///////////////////////////////////////////////////////////////////////////////
/// Updates the height of the subtree rooted at the given node, all way up to
/// the tree root.
///
/// This is a O(h) operation.
///
/// \param node Pointer to root of the subtree to be updated.
///////////////////////////////////////////////////////////////////////////////
template <class T>
void BST<T>::UpdateHeightUp(BSTNode<T>* node)
{
    while (node)
    {
        node->UpdateHeight();
        node = node->_parent;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// Recursively decreases the depth of a subtree by one.
///
/// This is a O(h) operation.
///
/// \param node Pointer to root of the subtree.
///////////////////////////////////////////////////////////////////////////////
template <class T>
void BST<T>::DecreaseDepthRec(BSTNode<T>* node)
{
    if (node)
    {
        node->_depth--;
        DecreaseDepthRec(node->_left);
        DecreaseDepthRec(node->_right);
    }
}

///////////////////////////////////////////////////////////////////////////////
/// Returns the node with minimum key in the subtree of the given node.
///
/// This is a O(h) operation.
///
/// \param node Starting node.
///
/// \return Pointer to the node found.
///////////////////////////////////////////////////////////////////////////////
template <class T>
BSTNode<T>* BST<T>::Minimum(BSTNode<T>* node)
{
    while (node && node->_left)
    {
        node = node->_left;
    }

    return node;
}

///////////////////////////////////////////////////////////////////////////////
/// Returns the node with maximum key in the subtree of the given node.
///
/// This is a O(h) operation.
///
/// \param node Starting node.
///
/// \return Pointer to the node found.
///////////////////////////////////////////////////////////////////////////////
template <class T>
BSTNode<T>* BST<T>::Maximum(BSTNode<T>* node)
{
    while (node && node->_right)
    {
        node = node->_right;
    }

    return node;
}

///////////////////////////////////////////////////////////////////////////////
/// Returns the node with the successor key with respect to the key of the
/// given node.
///
/// This is a O(h) operation.
///
/// \param node Starting node.
///
/// \return Successor node or nullptr if not found.
///////////////////////////////////////////////////////////////////////////////
template <class T>
BSTNode<T>* BST<T>::Successor(BSTNode<T>* node)
{
    if (!node)
        return nullptr;

    if (node->_right)
        return Minimum(node->_right);

    BSTNode<T>* res = node->_parent;
    while (res && node == res->_right)
    {
        node = res;
        res = res->_parent;
    }

    return res;
}

///////////////////////////////////////////////////////////////////////////////
/// Returns the node with the predecessor key with respect to the key of the
/// given node.
///
/// This is a O(h) operation.
///
/// \param node Starting node.
///
/// \return Predecessor node or nullptr if not found.
///////////////////////////////////////////////////////////////////////////////
template <class T>
BSTNode<T>* BST<T>::Predecessor(BSTNode<T>* node)
{
    if (!node)
        return nullptr;

    if (node->_left)
        return Maximum(node->_left);

    BSTNode<T>* res = node->_parent;
    while (res && node == res->_left)
    {
        node = res;
        res = res->_parent;
    }

    return res;
}

///////////////////////////////////////////////////////////////////////////////
/// Prints the tree structure in dot format (GraphViz).
///
/// \param printNodeHeight Whether to show the node height below the key value.
///
/// Tip: use the online Graphviz visualizer: http://www.webgraphviz.com/
///////////////////////////////////////////////////////////////////////////////
template <class T>
void BST<T>::PrintDot(bool printNodeHeight)
{
    if (!_root)
        return;

    _stream << "digraph BST {" << std::endl;
    _stream << "\tnode [fontname=\"Helvetica\"];" << std::endl;

    // Update node ids
    _nodeIdCount = 0;
    UpdateIdRec(_root);

    // Print list of nodes
    _nullNodeCount = 0;
    PrintDotNodeRec(_root, printNodeHeight);

    // Print list of edges
    _nullNodeCount = 0;
    if (!_root->_left && !_root->_right)
        _stream << "\t" << _root->_key << std::endl;
    else
        PrintDotEdgeRec(_root);

    _stream << "}" << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
/// Recursively assigns an id to the nodes of a subtree.
///
/// \param node Root of the subtree.
///////////////////////////////////////////////////////////////////////////////
template <class T>
void BST<T>::UpdateIdRec(BSTNode<T>* node)
{
    if (node)
    {
        node->_nodeId = _nodeIdCount++;
        UpdateIdRec(node->_left);
        UpdateIdRec(node->_right);
    }
}

///////////////////////////////////////////////////////////////////////////////
/// Recursively prints the nodes of a subtree in dot format.
///
/// \param node Root of the subtree.
/// \param printNodeHeight Whether to show the node height below the key value.
///////////////////////////////////////////////////////////////////////////////
template <class T>
void BST<T>::PrintDotNodeRec(BSTNode<T>* node, bool printNodeHeight)
{
    if (node)
    {
        _stream << "\t" << node->_nodeId << " [";
        _stream << "label=\"" << node->_key;
        if (printNodeHeight)
            _stream << "\\n" << node->_height;
        _stream << "\"];" << std::endl;

        if (node->_left)
            PrintDotNodeRec(node->_left, printNodeHeight);
        else
            PrintDotNullNode();

        if (node->_right)
            PrintDotNodeRec(node->_right, printNodeHeight);
        else
            PrintDotNullNode();
    }
}

///////////////////////////////////////////////////////////////////////////////
/// Recursively prints the edges of a subtree in dot format.
///
/// \param node Root of the subtree.
///////////////////////////////////////////////////////////////////////////////
template <class T>
void BST<T>::PrintDotEdgeRec(BSTNode<T>* node)
{
    if (node)
    {
        if (node->_left)
        {
            _stream << "\t" << node->_nodeId << " -> " << node->_left->_nodeId;
            _stream << " [dir=none];" << std::endl;
            PrintDotEdgeRec(node->_left);
        }
        else
            PrintDotNullEdge(node);

        if (node->_right)
        {
            _stream << "\t" << node->_nodeId << " -> " << node->_right->_nodeId;
            _stream << " [dir=none];" << std::endl;
            PrintDotEdgeRec(node->_right);
        }
        else
            PrintDotNullEdge(node);
    }
}

///////////////////////////////////////////////////////////////////////////////
/// Prints in dot format a link from key to null.
///
/// This is used by PrintDotRec when a node points to a leaf.
///////////////////////////////////////////////////////////////////////////////
template <class T>
void BST<T>::PrintDotNullNode()
{
    _stream << "\tn" << _nullNodeCount;
    _stream << " [shape=square label=\"\" width=0.2];" << std::endl;
    _nullNodeCount++;
}

///////////////////////////////////////////////////////////////////////////////
/// Prints in dot format a link from key to null.
///
/// This is used by PrintDotRec when a node points to a leaf.
///
/// \param node Pointer to the node with a null child.
///////////////////////////////////////////////////////////////////////////////
template <class T>
void BST<T>::PrintDotNullEdge(BSTNode<T>* node)
{
    _stream << "\t" << node->_nodeId << " -> n" << _nullNodeCount;
    _stream << " [dir=none];" << std::endl;
    _nullNodeCount++;
}

///////////////////////////////////////////////////////////////////////////////
/// Prints the contents of the tree in order.
///////////////////////////////////////////////////////////////////////////////
template <class T>
void BST<T>::PrintInOrder()
{
    PrintInOrderRec(_root);
}

///////////////////////////////////////////////////////////////////////////////
/// Recursively walks the tree in order from the given node.
///
/// \param node Root of the subtree.
///////////////////////////////////////////////////////////////////////////////
template <class T>
void BST<T>::PrintInOrderRec(BSTNode<T>* node)
{
    if (node)
    {
        PrintInOrderRec(node->_left);
        _stream << node->_key << std::endl;
        PrintInOrderRec(node->_right);
    }
}

}

#endif // BST_H
