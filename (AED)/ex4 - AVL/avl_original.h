#ifndef AVL_H
#define AVL_H

#include <iostream>

namespace aed2
{

// Forward declaration of AVL class.
template<class T>
class AVL;

///////////////////////////////////////////////////////////////////////////////
/// AVL node.
///
/// Implements an AVL tree node.
///////////////////////////////////////////////////////////////////////////////
template <class T>
class AVLNode
{
    friend class AVL<T>;

public:
    AVLNode(T& key);

    /// Node key getter.
    const T& key() const { return _key; }

protected:
    T _key; ///< Node key.
    AVLNode<T>* _parent; ///< Parent node.
    AVLNode<T>* _left;   ///< Left node.
    AVLNode<T>* _right;  ///< Right node.
    int _depth; ///< Node depth (0 to tree height).
    int _height; ///< Height of the subtree rooted at this node.

    int BalanceFactor();
    void UpdateHeight();

private:
    int _nodeId; ///< Used by PrintDot.
};

///////////////////////////////////////////////////////////////////////////////
/// Constructor.
///
/// \param key Reference to the key.
///
/// \remark Key type must implement a copy constructor.
///////////////////////////////////////////////////////////////////////////////
template <class T>
AVLNode<T>::AVLNode(T& key) : _parent(nullptr), _left(nullptr), _right(nullptr)
{
    _key = key; // Make a copy of the key
    _depth = 0;
    _height = 0;
    _nodeId = 0;    
}

///////////////////////////////////////////////////////////////////////////////
/// Gets the balance factor of this node.
///
/// The balance factor is the difference between the height of the right and
/// the left subtrees.
/// If 0, the subtree is completely balanced.
/// If < 0, the left subtree is taller.
/// If > 0, the right subtree is taller.
/// This is a O(1) operation.
///
/// \return The balance factor.
///////////////////////////////////////////////////////////////////////////////
template <class T>
int AVLNode<T>::BalanceFactor()
{
    return (_right ? _right->_height + 1 : 0) - (_left ? _left->_height + 1 : 0);
}

///////////////////////////////////////////////////////////////////////////////
/// Updates the height attribute of this node based on the heights of
/// its subtrees.
///
/// The height of this node is computed as the maximum height between its
/// left and right subtrees, plus one. This is a O(1) operation.
///////////////////////////////////////////////////////////////////////////////
template <class T>
void AVLNode<T>::UpdateHeight()
{
    int hl = (_left ? _left->_height : 0);
    int hr = (_right ? _right->_height : 0);
    _height = (hl > hr ? hl : hr);

    if (_left || _right)
        _height++;
}

///////////////////////////////////////////////////////////////////////////////
/// AVL class.
///
/// Implements an AVL tree.
///////////////////////////////////////////////////////////////////////////////
template <class T>
class AVL
{
public:
    AVL(std::ostream& stream = std::cout);

    void PrintInOrder();
    void PrintDot(bool printNodeHeight = false);

    AVLNode<T>* Search(const T& key);
    void Insert(AVLNode<T>* node);
    AVLNode<T>* Remove(AVLNode<T>* node);
    AVLNode<T>* Minimum(AVLNode<T>* node);
    AVLNode<T>* Maximum(AVLNode<T>* node);
    AVLNode<T>* Successor(AVLNode<T>* node);
    AVLNode<T>* Predecessor(AVLNode<T>* node);

    /// Node key getter.
    int height() const { return _root->_height; }

protected:
    AVLNode<T>* _root; ///< Root node.

    std::ostream& _stream; ///< Output stream used by tree walks.

    void PrintInOrderRec(const AVLNode<T>* node);
    void PrintDotNodeRec(AVLNode<T>* node, bool printNodeHeight);
    void PrintDotEdgeRec(const AVLNode<T>* node);
    void DecreaseDepthRec(AVLNode<T>* node);
    AVLNode<T>* RotateRight(AVLNode<T>* p);
    AVLNode<T>* RotateLeft(AVLNode<T>* q);
    AVLNode<T>* Balance(AVLNode<T>* p);
    void BalanceUp(AVLNode<T>* node);

private:
    int _nullNodeCount; ///< Internal counter of PrintDot.
    int _nodeIdCount; ///< Internal counter of PrintDot.

    void UpdateIdRec(AVLNode<T>* node);
    void PrintDotNullNode();
    void PrintDotNullEdge(const AVLNode<T>* node);
};

///////////////////////////////////////////////////////////////////////////////
/// Constructor.
///////////////////////////////////////////////////////////////////////////////
template <class T>
AVL<T>::AVL(std::ostream& stream) : _root(nullptr), _stream(stream)
{
}

///////////////////////////////////////////////////////////////////////////////
/// Prints the tree structure in dot format (GraphViz).
///
/// \param printNodeHeight Whether to show the node height below the key value.
///
/// Use the online Graphviz: http://www.webgraphviz.com/
///////////////////////////////////////////////////////////////////////////////
template <class T>
void AVL<T>::PrintDot(bool printNodeHeight)
{  
    if (!_root)
        return;

    _stream << "digraph AVL {" << std::endl;
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
        //_stream << "\t" << _root->_key << std::endl;
        _stream << std::endl;
    else
        PrintDotEdgeRec(_root);

    _stream << "}" << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
/// Recursively assigns an id to the nodes of the subtrees.
///
/// Id starts at _nodeIdCount and increments in a pre-order traversal.
///
/// \param node Root of the subtrees.
///////////////////////////////////////////////////////////////////////////////
template <class T>
void AVL<T>::UpdateIdRec(AVLNode<T>* node)
{
    if (node)
    {
        node->_nodeId = _nodeIdCount++;
        UpdateIdRec(node->_left);
        UpdateIdRec(node->_right);
    }
}

///////////////////////////////////////////////////////////////////////////////
/// Recursively prints the nodes of the subtrees in dot format.
///
/// \param node Root of the subtrees.
/// \param printNodeHeight Whether to show the node height below the key value.
///////////////////////////////////////////////////////////////////////////////
template <class T>
void AVL<T>::PrintDotNodeRec(AVLNode<T>* node, bool printNodeHeight)
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
/// Recursively prints the edges of the subtrees in dot format.
///
/// \param node Root of the subtrees.
///////////////////////////////////////////////////////////////////////////////
template <class T>
void AVL<T>::PrintDotEdgeRec(const AVLNode<T>* node)
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
void AVL<T>::PrintDotNullNode()
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
void AVL<T>::PrintDotNullEdge(const AVLNode<T>* node)
{
    _stream << "\t" << node->_nodeId << " -> n" << _nullNodeCount;
    _stream << " [dir=none];" << std::endl;
    _nullNodeCount++;
}

///////////////////////////////////////////////////////////////////////////////
/// Prints the contents of the tree in order.
///////////////////////////////////////////////////////////////////////////////
template <class T>
void AVL<T>::PrintInOrder()
{
    PrintInOrderRec(_root);
}

///////////////////////////////////////////////////////////////////////////////
/// Recursively walks the tree in order from the given node.
///
/// \param node Root of the subtrees.
///////////////////////////////////////////////////////////////////////////////
template <class T>
void AVL<T>::PrintInOrderRec(const AVLNode<T>* node)
{
    if (node)
    {
        PrintInOrderRec(node->_left);
        _stream << node->_key << std::endl;
        PrintInOrderRec(node->_right);
    }
}

///////////////////////////////////////////////////////////////////////////////
/// Searches the given key in the tree.
///
/// \param key Search key.
///
/// \return Pointer to the node found or nullptr if not found.
///////////////////////////////////////////////////////////////////////////////
template <class T>
AVLNode<T>* AVL<T>::Search(const T& key)
{
    AVLNode<T>* node = _root;

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
void AVL<T>::Insert(AVLNode<T>* z) {
    if (!z) return;

    AVLNode<T>* x = _root;
    AVLNode<T>* y = nullptr;

    while (x){
        y = x;
        x = (z->_key < x->_key)? x->_left : x->_right;
    }

    z->_parent = y;

    if (!y){
        z->_depth = 0;
        _root = z; 
    
        
    }else{
        z->_depth = z->_parent->_depth + 1;
        if (z->_key < y->_key)
            y->_left = z;
        else
            y->_right = z;
    }

    BalanceUp(z);
}

///////////////////////////////////////////////////////////////////////////////
/// Removes the given node from the tree.
///
/// \param node Pointer to the node to be removed.
///
/// \return Pointer to the removed node or nullptr if the removal has failed.
///////////////////////////////////////////////////////////////////////////////
template <class T>
AVLNode<T>* AVL<T>::Remove(AVLNode<T>* z)
{
    if (!z)
        return nullptr;

    AVLNode<T>* y = (!z->_left || !z->_right) ? z : Successor(z);
    AVLNode<T>* x = (y->_left) ? y->_left : y->_right; // Child of y
    AVLNode<T>* r = z;

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
        BalanceUp(y);
        z->_key = y->_key;
        r = y;       
    }
    else
        BalanceUp(r);

    return r;
}

///////////////////////////////////////////////////////////////////////////////
/// Recursively decreases the depth of the subtrees by one.
///
/// This is a O(h) operation.
///
/// \param node Pointer to root of the subtrees.
///////////////////////////////////////////////////////////////////////////////
template <class T>
void AVL<T>::DecreaseDepthRec(AVLNode<T>* node)
{
    if (node)
    {
        node->_depth--;
        DecreaseDepthRec(node->_left);
        DecreaseDepthRec(node->_right);
    }
}

///////////////////////////////////////////////////////////////////////////////
/// Rotates a subtree to the right.
///
/// This is a O(1) operation.
///
/// |     p          q     |
/// |    / \        / \    |
/// |   q   C  ->  A   p   |
/// |  / \            / \  |
/// | A   B          B   C |
///
/// \param p Pointer to root of the subtree to be rotated. It must have
///          non-null lef and right children.
///
/// \return Pointer to the new root of the rotated subtree.
///////////////////////////////////////////////////////////////////////////////
template <class T>
AVLNode<T>* AVL<T>::RotateRight(AVLNode<T>* p){
    AVLNode<T>* q = p->_left;

    p->_left = q->_right;
    
    if (p->_left)
        p->_left->_parent = p;
    
    q->_right = p;
    q->_parent = p->_parent;
    
    if (q->_parent){
        if (q->_parent->_left == p)
            q->_parent->_left = q;
        else
            q->_parent->_right = q;
    }
    
    p->_parent = q;

    if (_root == p)
        _root = q;

    p->UpdateHeight();
    q->UpdateHeight();

    return q;
}

///////////////////////////////////////////////////////////////////////////////
/// Rotates a subtree to the left.
///
/// This is a O(1) operation.
///
/// |     p          q     |
/// |    / \        / \    |
/// |   q   C  <-  A   p   |
/// |  / \            / \  |
/// | A   B          B   C |
///
/// \param q Pointer to root of the subtree to be rotated. It must have
///          non-null lef and right children.
///
/// \return Pointer to the new root of the rotated subtree.
///////////////////////////////////////////////////////////////////////////////
template <class T>
AVLNode<T>* AVL<T>::RotateLeft(AVLNode<T>* q)
{
    AVLNode<T>* p = q->_right;

    q->_right = p->_left;
    if (q->_right)
        q->_right->_parent = q;
    p->_left = q;
    p->_parent = q->_parent;
    if (p->_parent)
    {
        if (p->_parent->_left == q)
            p->_parent->_left = p;
        else
            p->_parent->_right = p;
    }
    q->_parent = p;

    if (_root == q)
        _root = p;

    q->UpdateHeight();
    p->UpdateHeight();

    return p;
}

///////////////////////////////////////////////////////////////////////////////
/// Balances the subtree rooted at the given node.
///
/// A balance is required when the balance factor is 2 or -2. After the
/// balance, the balance factor is in the range [-1,1].
///
/// This is a O(1) operation.
///
/// \param p Pointer to root of the subtree to be balanced.
///
/// \return Pointer to the new root of the balanced subtree.
///////////////////////////////////////////////////////////////////////////////
template <class T>
AVLNode<T>* AVL<T>::Balance(AVLNode<T>* p)
{
    p->UpdateHeight();

    if (p->BalanceFactor() == 2) // Heavier to the right?
    {
        // Right child heavier to the left?
        if (p->_right && p->_right->BalanceFactor() < 0)
        {
            p->_right = RotateRight(p->_right);
        }

        return RotateLeft(p);
    }
    else if (p->BalanceFactor() == -2) // Heavier to the left?
    {
        // Left child heavier to the right?
        if (p->_left && p->_left->BalanceFactor() > 0)
        {
            p->_left = RotateLeft(p->_left);
        }

        return RotateRight(p);
    }

    return p;
}

///////////////////////////////////////////////////////////////////////////////
/// Balances the subtree rooted at the given node, all way up to the root.
///
/// This is a O(h) operation.
///
/// \param node Pointer to root of the subtree to be balanced.
///////////////////////////////////////////////////////////////////////////////
template <class T>
void AVL<T>::BalanceUp(AVLNode<T>* node)
{
    while (node)
    {
        node = Balance(node);
        node = node->_parent;
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
AVLNode<T>* AVL<T>::Minimum(AVLNode<T>* node)
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
AVLNode<T>* AVL<T>::Maximum(AVLNode<T>* node)
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
/// \param node Starting node
///
/// \return Successor node or nullptr if not found.
///////////////////////////////////////////////////////////////////////////////
template <class T>
AVLNode<T>* AVL<T>::Successor(AVLNode<T>* node)
{
    if (!node)
        return nullptr;

    if (node->_right)
        return Minimum(node->_right);

    AVLNode<T>* res = node->_parent;
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
/// \param node Starting node
///
/// \return Predecessor node or nullptr if not found.
///////////////////////////////////////////////////////////////////////////////
template <class T>
AVLNode<T>* AVL<T>::Predecessor(AVLNode<T>* node)
{
    if (!node)
        return nullptr;

    if (node->_left)
        return Maximum(node->_left);

    AVLNode<T>* res = node->_parent;
    while (res && node == res->_left)
    {
        node = res;
        res = res->_parent;
    }

    return res;
}

}

#endif // AVL_H
