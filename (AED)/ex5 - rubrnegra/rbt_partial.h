// Partial implementation of the red-black tree.
// The following method definitions are missing:
//
// RBTNode<T>* Search(const T& key);
// void Insert(RBTNode<T>* node);
// RBTNode<T>* Remove(RBTNode<T>* node);
// RBTNode<T>* Minimum(RBTNode<T>* node);
// RBTNode<T>* Maximum(RBTNode<T>* node);
// RBTNode<T>* Successor(RBTNode<T>* node);
// RBTNode<T>* Predecessor(RBTNode<T>* node);
// void InsertFixUp(RBTNode<T>* z);
// void DeleteFixUp(RBTNode<T>* x);
// void Rotate(RBTNode<T>* p, bool toLeft = true);


#ifndef RBT_H
#define RBT_H

#include <iostream>

namespace aed2
{

// Forward declaration of RBT class.
template<class T>
class RBT;

/// Color enumeration for the red-black nodes.
enum Color { RED, BLACK };

///////////////////////////////////////////////////////////////////////////////
/// RBT node.
///
/// Implements a red-black tree node.
///////////////////////////////////////////////////////////////////////////////
template <class T>
class RBTNode
{
    friend class RBT<T>;

public:
    RBTNode(T& key, bool isNil = false);

    /// Node key getter.
    const T& key() const { return _key; }

    /// Nil sentinel flag getter.
    bool isNil() { return _isNil; }

protected:
    T _key; ///< Node key.
    RBTNode<T>* _parent; ///< Parent node.
    RBTNode<T>* _child[2];   ///< Left node [0] and right node [1].
    bool _isNil; ///< Whether this is a sentinel "nil" node.
    Color _color; ///< Node color (RED or BLACK).

private:
    int _nodeId; ///< Used by PrintDot...
};

///////////////////////////////////////////////////////////////////////////////
/// Constructor.
///
/// \param key Reference to the key.
/// \param isNil Whether this node is a sentinel node (leaf nil node).
///
/// \remark The key must implement a copy constructor.
///////////////////////////////////////////////////////////////////////////////
template <class T>
RBTNode<T>::RBTNode(T& key, bool isNil)
{
    _isNil = isNil;

    if (_isNil)
    {
        _parent = _child[0] = _child[1] = this;
    }
    else
    {
        _parent = nullptr;
        _child[0] = _child[1] = nullptr;
    }
    _key = key;
    _color = BLACK;
    _nodeId = 0;    
}

///////////////////////////////////////////////////////////////////////////////
/// RBT class.
///
/// Implements a red-black tree.
///////////////////////////////////////////////////////////////////////////////
template <class T>
class RBT
{
public:
    RBT(T nilKey = 0, std::ostream& stream = std::cout);
    ~RBT();

    void PrintInOrder();
    void PrintDot();

    RBTNode<T>* Search(const T& key);
    void Insert(RBTNode<T>* node);
    RBTNode<T>* Remove(RBTNode<T>* node);
    RBTNode<T>* Minimum(RBTNode<T>* node);
    RBTNode<T>* Maximum(RBTNode<T>* node);
    RBTNode<T>* Successor(RBTNode<T>* node);
    RBTNode<T>* Predecessor(RBTNode<T>* node);

protected:
    RBTNode<T>* _root; ///< Root node.
    RBTNode<T>* _nil; ///< Sentinel used as commom nil leaf node.

    std::ostream& _stream; ///< Output stream used by tree walks.

    void PrintInOrderRec(RBTNode<T>* node);
    void PrintDotNodeRec(RBTNode<T>* node);
    void PrintDotEdgeRec(RBTNode<T>* node);
    void InsertFixUp(RBTNode<T>* z);
    void DeleteFixUp(RBTNode<T>* x);
    void Rotate(RBTNode<T>* p, bool toLeft = true);

private:
    int _nullNodeCount; ///< Internal counter of PrintDot...
    int _nodeIdCount; ///< Internal counter of PrintDot...

    void UpdateIdRec(RBTNode<T>* node);
    void PrintDotNullNode();
    void PrintDotNullEdge(RBTNode<T>* node);
};

///////////////////////////////////////////////////////////////////////////////
/// Constructor.
///
/// \param nilKey Key value for the sentinel node. Default is 0.
/// \param stream Output stream used by Print... methods.
///////////////////////////////////////////////////////////////////////////////
template <class T>
RBT<T>::RBT(T nilKey, std::ostream& stream) : _stream(stream)
{
    _nil = new RBTNode<T>(nilKey, true);
    _root = _nil;
}

///////////////////////////////////////////////////////////////////////////////
/// Destructor.
///////////////////////////////////////////////////////////////////////////////
template <class T>
RBT<T>::~RBT()
{
    if (_nil)
        delete _nil;
}

///////////////////////////////////////////////////////////////////////////////
/// Prints the tree structure in dot format (GraphViz).
///
/// Use the online Graphviz: http://www.webgraphviz.com/
///////////////////////////////////////////////////////////////////////////////
template <class T>
void RBT<T>::PrintDot()
{  
    if (!_root)
        return;

    _stream << "digraph RBT {" << std::endl;
    _stream << "\tnode [fontname=\"Helvetica\"];" << std::endl;

    // Update node ids
    _nodeIdCount = 0;
    UpdateIdRec(_root);

    // Print list of nodes
    _nullNodeCount = 0;
    PrintDotNodeRec(_root);

    // Print list of edges
    _nullNodeCount = 0;
    if (_root->_child[0]->isNil() && _root->_child[1]->isNil())
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
void RBT<T>::UpdateIdRec(RBTNode<T>* node)
{
    if (!node->isNil())
    {
        node->_nodeId = _nodeIdCount++;
        UpdateIdRec(node->_child[0]);
        UpdateIdRec(node->_child[1]);
    }
}

///////////////////////////////////////////////////////////////////////////////
/// Recursively prints the nodes of a subtree in dot format.
///
/// \param node Root of the subtree.
///////////////////////////////////////////////////////////////////////////////
template <class T>
void RBT<T>::PrintDotNodeRec(RBTNode<T>* node)
{
    if (!node->isNil())
    {
        _stream << "\t" << node->_nodeId << " [";
        _stream << "label=\"" << node->_key;
        _stream << "\"";
        _stream << " style=filled fillcolor=";
        if (node->_color == RED)
            _stream << "indianred1";
        else
            _stream << "lightgray";
        _stream << "];" << std::endl;

        for (int i = 0; i < 2; ++i)
        {
            if (!node->_child[i]->isNil())
                PrintDotNodeRec(node->_child[i]);
            else
                PrintDotNullNode();
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
/// Recursively prints the edges of a subtree in dot format.
///
/// \param node Root of the subtree.
///////////////////////////////////////////////////////////////////////////////
template <class T>
void RBT<T>::PrintDotEdgeRec(RBTNode<T>* node)
{
    if (node && !node->isNil())
    {
        for (int i = 0; i < 2; ++i)
        {
            if (!node->_child[i]->isNil())
            {
                _stream << "\t" << node->_nodeId << " -> " << node->_child[i]->_nodeId;
                _stream << " [dir=none];" << std::endl;
                PrintDotEdgeRec(node->_child[i]);
            }
            else
                PrintDotNullEdge(node);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
/// Prints in dot format a link from key to null.
///
/// This is used by PrintDotRec when a node points to a leaf.
///////////////////////////////////////////////////////////////////////////////
template <class T>
void RBT<T>::PrintDotNullNode()
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
void RBT<T>::PrintDotNullEdge(RBTNode<T>* node)
{
    _stream << "\t" << node->_nodeId << " -> n" << _nullNodeCount;
    _stream << " [dir=none];" << std::endl;
    _nullNodeCount++;
}

///////////////////////////////////////////////////////////////////////////////
/// Prints the contents of the tree in order.
///////////////////////////////////////////////////////////////////////////////
template <class T>
void RBT<T>::PrintInOrder()
{
    PrintInOrderRec(_root);
}

///////////////////////////////////////////////////////////////////////////////
/// Recursively walks the tree in order from the given node.
///
/// \param node Root of the subtree.
///////////////////////////////////////////////////////////////////////////////
template <class T>
void RBT<T>::PrintInOrderRec(RBTNode<T>* node)
{
    if (!node->isNil())
    {
        PrintInOrderRec(node->_child[0]);
        _stream << node->_key << std::endl;
        PrintInOrderRec(node->_child[1]);
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
RBTNode<T>* RBT<T>::Search(const T& key)
{
    
}

///////////////////////////////////////////////////////////////////////////////
/// Inserts a given node in the tree.
///
/// \param node Pointer to the node to be inserted.
///////////////////////////////////////////////////////////////////////////////
template <class T>
void RBT<T>::Insert(RBTNode<T>* z)
{

}

///////////////////////////////////////////////////////////////////////////////
/// Fix the inserted node z and its ancestors according to the rules of the
/// red-black tree.
///
/// \param z Pointer to the node to be fixed.
///////////////////////////////////////////////////////////////////////////////
template <class T>
void RBT<T>::InsertFixUp(RBTNode<T>* z)
{

}

///////////////////////////////////////////////////////////////////////////////
/// Removes the given node from the tree.
///
/// \param z Pointer to the node to be removed.
///
/// \return Pointer to the removed node or nullptr if the removal has failed.
///////////////////////////////////////////////////////////////////////////////
template <class T>
RBTNode<T>* RBT<T>::Remove(RBTNode<T>* z)
{

}

///////////////////////////////////////////////////////////////////////////////
/// Fix the deleted node z and its ancestors according to the rules of the
/// red-black tree.
///
/// \param x Pointer to the node to be fixed.
///////////////////////////////////////////////////////////////////////////////
template <class T>
void RBT<T>::DeleteFixUp(RBTNode<T>* x)
{

}

///////////////////////////////////////////////////////////////////////////////
/// Rotates a subtree to the left or to right
///
/// This is a O(1) operation.
///
/// To the left:
/// |     p          q     |
/// |    / \        / \    |
/// |   q   C  <-  A   p   |
/// |  / \            / \  |
/// | A   B          B   C |
///
/// To the right:
/// |     p          q     |
/// |    / \        / \    |
/// |   q   C  ->  A   p   |
/// |  / \            / \  |
/// | A   B          B   C |
///
/// \param x Pointer to root of the subtree to be rotated. It must have
///          non-null lef and right children.
/// \param toLeft Whether the rotation is to the left or to the right.
///
/// \return Pointer to the new root of the rotated subtree.
///////////////////////////////////////////////////////////////////////////////
template <class T>
void RBT<T>::Rotate(RBTNode<T>* x, bool toLeft)
{

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
RBTNode<T>* RBT<T>::Minimum(RBTNode<T>* node)
{

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
RBTNode<T>* RBT<T>::Maximum(RBTNode<T>* node)
{

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
RBTNode<T>* RBT<T>::Successor(RBTNode<T>* node)
{

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
RBTNode<T>* RBT<T>::Predecessor(RBTNode<T>* node)
{

}

}

#endif // RBT_H
