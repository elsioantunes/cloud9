#ifndef PATRICIA_H
#define PATRICIA_H

#include <bitset>

namespace aed2 {
    template<size_t N>
    class Patricia;
    
    template<size_t N>
    class PatriciaNode {
            friend class Patricia<N>;
        
        public:
            PatriciaNode();
        
            /// Node key getter.
            const std::bitset<N>* key() const { return _key; }
        
        protected:        
            size_t _bitIndex; ///< Index of the comparison bit.
            std::bitset<N>* _key; ///< Bitset key.
        
            PatriciaNode *_parent; ///< Parent node.
            PatriciaNode *_left; ///< Left child (0).
            PatriciaNode *_right; ///< Right child (1).
        
        private:
            int _nodeId; ///< Used by PrintDot.
    };
    

    PatriciaNode<N>::PatriciaNode() : _key(nullptr) {
        _bitIndex = 0;
        _parent = nullptr;
        _left = nullptr;
        _right = nullptr;
        _nodeId = 0;
    }
    


    template<size_t N>
    class Patricia {
        public:
            Patricia(std::ostream& stream = std::cout);
            ~Patricia();
        
            void Print();
            void PrintDot();
        
            bool Search(const std::bitset<N>& key);
            bool Insert(const std::bitset<N>& key);
            bool Remove(const std::bitset<N>& key);
        
        protected:
            PatriciaNode<N>* _root; ///< Root node.
        
            std::ostream& _stream; ///< Output stream used by tree walks.
        
            void PrintRec(const PatriciaNode<N>* node);
            void PrintDotNodeRec(const PatriciaNode<N>* node);
            void PrintDotEdgeRec(const PatriciaNode<N>* node);
        
        private:
            int _nodeIdCount; ///< Internal counter of PrintDot...
        
            void UpdateIdRec(PatriciaNode<N>* node);
    };
    
    
    
    
    
    
    template<size_t N>
    Patricia<N>::Patricia(std::ostream& stream) : _stream(stream) {
        _root = new PatriciaNode<N>();
    }
    
    template<size_t N>
    Patricia<N>::~Patricia() {
        delete _root;
    }
    

    template<size_t N>
    bool Patricia<N>::Search(const std::bitset<N>& key) {
        PatriciaNode<N>* current = _root;
    
        while (current->_left) {
            if (!key.test(N - 1 - current->_bitIndex)) 
                current = current->_left;
            else
                current = current->_right;
        }
    
        if (key == *current->_key)
            return true;
        return false;
    }
    

    template<size_t N>
    bool Patricia<N>::Insert(const std::bitset<N>& key) {
        PatriciaNode<N>* current = _root;
    
        while (current->_left){
            if (!key.test(N - 1 - current->_bitIndex))            
                current = current->_left;
            else
                current = current->_right;
        }
    


        if (!current->_parent && !current->_key){
            current->_key = new std::bitset<N>(key);
        
        }else{
            // Get first differing bit (from left to right)
            size_t diffBit = 0;

            while (     diffBit < N &&    
                        current->_key->test(N - 1 - diffBit) ==  key.test(N - 1 - diffBit))

                diffBit++;

            if (diffBit == N)
                return false; // Key already exists
    

            // Ascend the tree while diffbit is lower than bit index of
            // visited nodes
            PatriciaNode<N> *parent = current->_parent;
            bool fromLeft;

            
            if (parent) 
                fromLeft = (parent->_left == current) ? 
                    true : false;

            
            while (parent && parent->_bitIndex > diffBit) {
                if (parent->_parent)
                    fromLeft = (parent == parent->_parent->_left) ? 
                        true : false;

                current = parent;
                parent = parent->_parent;
            }
    
            // New node with new bit index
            PatriciaNode<N> *newNode = new PatriciaNode<N>();
            newNode->_bitIndex = diffBit;
            newNode->_parent = parent;

            if (parent){
                if (fromLeft)
                    parent->_left = newNode;
                else
                    parent->_right = newNode;

            }else{
                _root = newNode;
            }
            
    
            PatriciaNode<N> *newLeaf = new PatriciaNode<N>();
            newLeaf->_key = new std::bitset<N>(key);
            newLeaf->_parent = newNode;
            current->_parent = newNode;
    
            if (!newLeaf->_key->test(N - 1 - diffBit)) {
                newNode->_left = newLeaf;
                newNode->_right = current;

            }else {
                newNode->_left = current;
                newNode->_right = newLeaf;
            }
        }
    
        return true;
    }
    
    
    
    template<size_t N>
    bool Patricia<N>::Remove(const std::bitset<N>& key)
    {
        PatriciaNode<N>* current = _root;
    
        while (current->_left)
        {
            if (!key.test(N - 1 - current->_bitIndex))
            {
                current = current->_left;
            }
            else
            {
                current = current->_right;
            }
        }
    
        if (!current->_parent) // Root
        {
            if (!current->_key) // Empty tree
            {
                return false;
            }
    
            delete current->_key;
            current->_key = nullptr;
        }
        else
        {
            PatriciaNode<N> *parent = current->_parent;
            PatriciaNode<N> *sibling;
    
            if (parent->_left == current)
            {
                sibling = parent->_right;
            }
            else
            {
                sibling = parent->_left;
            }
    
            if (parent->_parent)
            {
                if (parent->_parent->_left == parent)
                {
                    parent->_parent->_left = sibling;
                }
                else
                {
                    parent->_parent->_right = sibling;
                }
                sibling->_parent = parent->_parent;
            }
            else
            {
                sibling->_parent = nullptr;
                _root = sibling;
            }
    
            delete parent;
            delete current->_key;
            delete current;
        }
    
        return true;
    }
    
    ///////////////////////////////////////////////////////////////////////////////
    /// Prints the patricia in dot format (GraphViz).
    ///
    /// Tip: use the online Graphviz visualizer: http://www.webgraphviz.com/
    ///////////////////////////////////////////////////////////////////////////////
    template<size_t N>
    void Patricia<N>::PrintDot()
    {
        _stream << "digraph Patricia {" << std::endl;
        _stream << "\tedge [fontname=\"Helvetica\" dir=none];" << std::endl;
        _stream << "\tnode [fontname=\"Helvetica\" shape=circle];" << std::endl;
    
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
    template<size_t N>
    void Patricia<N>::UpdateIdRec(PatriciaNode<N>* node)
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
    ///////////////////////////////////////////////////////////////////////////////
    template<size_t N>
    void Patricia<N>::PrintDotNodeRec(const PatriciaNode<N>* node)
    {
        if (node)
        {
            if (!node->_left && !node->_right)
            {
                if (node->_key)
                {
                    _stream << "\t" << node->_nodeId;
                    _stream << " [label=\"";
                    _stream << node->_key->to_string();
                    _stream << "\" shape=box];" << std::endl;
                }
            }
            else
            {
                _stream << "\t" << node->_nodeId;
                _stream << " [label=\"" << node->_bitIndex << "\"];" << std::endl;
            }
    
            PrintDotNodeRec(node->_left);
            PrintDotNodeRec(node->_right);
        }
    }
    
    ///////////////////////////////////////////////////////////////////////////////
    /// Recursively prints the edges of a subtree in dot format.
    ///
    /// \param node Root of the subtree.
    ///////////////////////////////////////////////////////////////////////////////
    template<size_t N>
    void Patricia<N>::PrintDotEdgeRec(const PatriciaNode<N>* node)
    {
        if (node)
        {
            if (node->_left)
            {
                _stream << "\t" << node->_nodeId;
                _stream << " -> ";
                _stream << node->_left->_nodeId;
                _stream << " [label = \"0\"];" << std::endl;
                PrintDotEdgeRec(node->_left);
            }
    
            if (node->_right)
            {
                _stream << "\t" << node->_nodeId;
                _stream << " -> ";
                _stream << node->_right->_nodeId;
                _stream << " [label = \"1\"];" << std::endl;
                PrintDotEdgeRec(node->_right);
            }
        }
    }
    
    ///////////////////////////////////////////////////////////////////////////////
    /// Prints the contents of the trie in non decreasing order.
    ///////////////////////////////////////////////////////////////////////////////
    template<size_t N>
    void Patricia<N>::Print()
    {
        PrintRec(_root);
    }
    
    ///////////////////////////////////////////////////////////////////////////////
    /// Recursively walks the tree in post-order from the given node.
    ///
    /// \param node Non-null root of the subtree.
    ///////////////////////////////////////////////////////////////////////////////
    template<size_t N>
    void Patricia<N>::PrintRec(const PatriciaNode<N>* node)
    {
        if (node)
        {
            PrintRec(node->_left);
            PrintRec(node->_right);
            if (!node->_left && node->_key)
            {
                _stream << node->_key->to_string() <<  std::endl; // Leaf
            }
        }
    }
    
}

#endif // PATRICIA_H
