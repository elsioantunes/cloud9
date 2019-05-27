#ifndef TRIE_H
#define TRIE_H

#define ALPHABET_SIZE 26 // Size of the alphabet (a..z lower case)

#include <vector>
#include <string>
#include <stack>

namespace aed2{

// Forward declaration of Trie class
class Trie;

///////////////////////////////////////////////////////////////////////////////
/// Trie node.
///
/// Implements a Trie node.
///////////////////////////////////////////////////////////////////////////////
class TrieNode
{
    friend class Trie;

public:
    TrieNode(bool isEnd = false, int prefixCount = 0);

protected:
    bool _isEnd; ///< Whether this is an end of a string.
    /// Number of strings from the root to this node with the given prefix.
    int _prefixCount;
    std::vector<TrieNode*> _child; ///< Array of children.

private:
    int _nodeId; ///< Used by PrintDot...
};

///////////////////////////////////////////////////////////////////////////////
/// Constructor.
///
/// \param isEnd Whether this node is an end of a string.
/// \param prefixCount Number of strings from the root to this node with the
///        prefix given from the root to this node.
///////////////////////////////////////////////////////////////////////////////
TrieNode::TrieNode(bool isEnd, int prefixCount)
{
    _isEnd = isEnd;
    _prefixCount = prefixCount;
    _child.resize(ALPHABET_SIZE);
    _nodeId = 0;
}

///////////////////////////////////////////////////////////////////////////////
/// Trie class.
///
/// Implements a Trie (prefix tree) for strings composed of lower case
/// characters from a to z.
///////////////////////////////////////////////////////////////////////////////
class Trie
{
public:
    Trie(std::ostream& stream = std::cout);

    void PrintPreOrder();
    void PrintDot();

    bool Search(const std::string key);
    bool Insert(const std::string key);
    int WordsWithPrefix(const std::string prefix);
    bool Remove(const std::string key);

protected:
    TrieNode* _root; ///< Root node.

    std::ostream& _stream; ///< Output stream used by tree walks.

    void PrintPreOrderRec(TrieNode* node, std::string prefix);

    void PrintDotNodeRec(TrieNode* node);
    void PrintDotEdgeRec(TrieNode* node);

private:
    int _nodeIdCount; ///< Internal counter of PrintDot...

    void UpdateIdRec(TrieNode* node);
};

///////////////////////////////////////////////////////////////////////////////
/// Constructor.
///////////////////////////////////////////////////////////////////////////////
Trie::Trie(std::ostream& stream) : _stream(stream)
{
    _root = new TrieNode();
}

///////////////////////////////////////////////////////////////////////////////
/// Searches the given key in the trie.
///
/// \param key Search key.
///
/// \return TRUE if the key was found, FALSE otherwise.
///////////////////////////////////////////////////////////////////////////////
bool Trie::Search(const std::string key)
{
    TrieNode* current = _root;

    for (const char& ch : key)
    {
        int letter = (int)ch - (int)'a';
        if (!current->_child[letter])
        {
            return false;
        }
        current = current->_child[letter];
    }

    return current->_isEnd;
}

///////////////////////////////////////////////////////////////////////////////
/// Inserts a given key in the trie.
///
/// \param key String key to be inserted.
/// \return TRUE if the key was insert, FALSE otherwise.
///////////////////////////////////////////////////////////////////////////////
bool Trie::Insert(const std::string key)
{
    if (Search(key))
    {
        return false;
    }

    TrieNode* current = _root;
    current->_prefixCount++;

    for (const char& ch : key)
    {
        int letter = (int)ch - (int)'a';        
        if (!current->_child[letter])
        {
            current->_child[letter] = new TrieNode();
        }
        current->_child[letter]->_prefixCount++;
        current = current->_child[letter];
    }

    current->_isEnd = true;

    return true;
}

///////////////////////////////////////////////////////////////////////////////
/// Removes the given key from the trie.
///
/// \param key String key to be removed.
/// \return TRUE if the key was removed, FALSE otherwise.
///////////////////////////////////////////////////////////////////////////////
bool Trie::Remove(const std::string key)
{
    if (!Search(key))
    {
        return false;
    }

    TrieNode* current = _root;
    current->_prefixCount--;

    // Stack of nodes with child nodes to be released
    std::stack<TrieNode*> nodesToDelete;

    for (const char& ch : key)
    {
        int letter = (int)ch - (int)'a';        
        TrieNode* child = current->_child[letter];
        child->_prefixCount--;

        if (child->_prefixCount == 0)
        {
            nodesToDelete.push(child);
            current->_child[letter] = nullptr;
        }
        current = child;
    }

    current->_isEnd = false;

    // Delete non-root nodes with prefixCount = 0
    while (!nodesToDelete.empty())
    {
        delete nodesToDelete.top();
        nodesToDelete.pop();
    }

    return true;
}

///////////////////////////////////////////////////////////////////////////////
/// Returns the number of strings in the trie which has 'prefix' as prefix.
///
/// \param prefix Prefix to be searched.
///////////////////////////////////////////////////////////////////////////////
int Trie::WordsWithPrefix(const std::string prefix)
{
    TrieNode* current = _root;

    for (const char& ch : prefix)
    {
        int letter = (int)ch - (int)'a';
        if (!current->_child[letter])
        {
            return 0;
        }
        else
        {
            current = current->_child[letter];
        }
    }

    return current->_prefixCount;
}

///////////////////////////////////////////////////////////////////////////////
/// Prints the trie in dot format (GraphViz).
///
/// Tip: use the online Graphviz visualizer: http://www.webgraphviz.com/
///////////////////////////////////////////////////////////////////////////////
void Trie::PrintDot()
{
    _stream << "digraph Trie {" << std::endl;
    _stream << "\tedge [fontname=\"Helvetica\" dir=none];" << std::endl;
    _stream << "\tnode [fontname=\"Helvetica\" shape=circle width=0.2];";
    _stream << std::endl;

    // Update node ids
    _nodeIdCount = 0;
    UpdateIdRec(_root);

    // Print list of nodes
    PrintDotNodeRec(_root);

    // Print list of edges
    PrintDotEdgeRec(_root);

    _stream << "}" << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
/// Recursively assigns an id to the nodes of a subtree.
///
/// \param node Root of the subtree.
///////////////////////////////////////////////////////////////////////////////
void Trie::UpdateIdRec(TrieNode* node)
{
    if (node)
    {
        node->_nodeId = _nodeIdCount++;
        for (int i = 0; i < ALPHABET_SIZE; ++i)
        {
            UpdateIdRec(node->_child[i]);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
/// Recursively prints the nodes of a subtree in dot format.
///
/// \param node Root of the subtree.
///////////////////////////////////////////////////////////////////////////////
void Trie::PrintDotNodeRec(TrieNode* node)
{
    if (node)
    {
        _stream << "\t" << node->_nodeId;

        _stream << " [label=\"" << node->_prefixCount << "\"";

        if (node->_isEnd)
        {
            _stream << " fontcolor=white fillcolor=black style=filled";
        }

        _stream << "];" << std::endl;
        for (int i = 0; i < ALPHABET_SIZE; ++i)
        {
            PrintDotNodeRec(node->_child[i]);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
/// Recursively prints the edges of a subtree in dot format.
///
/// \param node Root of the subtree.
///////////////////////////////////////////////////////////////////////////////
void Trie::PrintDotEdgeRec(TrieNode* node)
{
    if (node)
    {
        for (int i = 0; i < ALPHABET_SIZE; ++i)
        {
            if (node->_child[i])
            {
                _stream << "\t" << node->_nodeId;
                _stream << " -> ";
                _stream << node->_child[i]->_nodeId;
                _stream << " [label = \" ";
                _stream << (char)(i + (int)'a');
                _stream << "\"];" << std::endl;
                PrintDotEdgeRec(node->_child[i]);
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
/// Prints the contents of the trie in non decreasing order (pre-order).
///////////////////////////////////////////////////////////////////////////////
void Trie::PrintPreOrder()
{
    PrintPreOrderRec(_root, "");
}

///////////////////////////////////////////////////////////////////////////////
/// Recursively walks the tree in pre-order from the given node.
///
/// \param node Non-null root of the subtree.
/// \param prefix Prefix composed of ancestors.
///////////////////////////////////////////////////////////////////////////////
void Trie::PrintPreOrderRec(TrieNode* node, std::string prefix)
{
    if (node->_isEnd)
    {
        _stream << prefix << std::endl;
    }

    for (int i = 0; i < ALPHABET_SIZE; ++i)
    {
        if (node->_child[i] != nullptr)
        {
            std::string newPrefix = prefix + (char)(i + (int)'a');
            PrintPreOrderRec(node->_child[i], newPrefix);
        }
    }
}

}

#endif // TRIE_H
