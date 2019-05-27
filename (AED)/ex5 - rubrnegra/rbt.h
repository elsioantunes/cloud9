// RBTNode<T>* Minimum(RBTNode<T>* node);
// RBTNode<T>* Maximum(RBTNode<T>* node);

// RBTNode<T>* Successor(RBTNode<T>* node);
// RBTNode<T>* Predecessor(RBTNode<T>* node);


#ifndef RBT_H
#define RBT_H
#include <iostream>

namespace aed2{
    enum Color { RED, BLACK };

    template <class T>
    class RBTNode{
        public:
            RBTNode(T& key, bool isNil = false){
                _isNil = isNil;
                if (_isNil){
                    _parent = _child[0] = _child[1] = this;
                }else{
                    _parent = nullptr;
                    _child[0] = _child[1] = nullptr;
                }
                _key = key;
                _color = BLACK;
                _nodeId = 0;    
            }
            const T& key() const { return _key; }
            bool isNil() { return _isNil; }
        
            T _key;
            RBTNode<T>* _parent;
            RBTNode<T>* _child[2];
            bool _isNil;
            Color _color;
        
            int _nodeId;
    };
    

    





    
    
    
    
    
    template <class T>
    class RBT{
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
            RBTNode<T>* _root; 
            RBTNode<T>* _nil;
            RBTNode<T>* _tio;
        
            std::ostream& _stream;
        
            void PrintInOrderRec(RBTNode<T>* node);
            void PrintDotNodeRec(RBTNode<T>* node);
            void PrintDotEdgeRec(RBTNode<T>* node);
            void InsertFixUp(RBTNode<T>* z);
            void DeleteFixUp(RBTNode<T>* x);
            void Rotate(RBTNode<T>* p, bool toLeft = true);
        
        private:
            int _nullNodeCount;
            int _nodeIdCount;
            void UpdateIdRec(RBTNode<T>* node);
            void PrintDotNullNode();
            void PrintDotNullEdge(RBTNode<T>* node);
    };
    

    template <class T> 
    RBT<T>::RBT(T nilKey, std::ostream& stream) : _stream(stream){
        _nil = new RBTNode<T>(nilKey, true);
        _root = _nil;
    }

    template <class T>
    void RBT<T>::Insert(RBTNode<T>* z){

        RBTNode<T>* y = _nil;
        RBTNode<T>* x = _root;
    
        while (!x->isNil())
            y = x, 
            x = (z->_key < x->_key)?
                x->_child[0] : x->_child[1];

        z->_parent = y;
    
        if (y->isNil()) 
            _root = z; 
        else 
            if (z->_key < y->_key)
                y->_child[0] = z;
            else
                y->_child[1] = z;

        z->_child[0] = _nil;
        z->_child[1] = _nil;
        z->_color = RED;
    
        InsertFixUp(z);
    }
    
    template <class T>
    void RBT<T>::InsertFixUp(RBTNode<T>* z){
        
        while(z->_parent->_color == RED){ // we have a violation, uh!

            // detector de lado
            int lado = (z->_parent == z->_parent->_parent->_child[0])?1:0; 

            _tio = z->_parent->_parent->_child[lado];
            
            if(_tio->_color == RED){ // tio Red?
                z->_parent->_color = BLACK;
                      _tio->_color = BLACK;
                z->_parent->_parent->_color = RED;
                z = z->_parent->_parent; // bubble!

            }else{ // tio preto
                
                if(z == z->_parent->_child[lado])
                    z = z->_parent, Rotate(z, lado); // abre joelho

                // recolor and rotate
                z->_parent->_color = BLACK;
                z->_parent->_parent->_color = RED;
                Rotate(z->_parent->_parent, 1-lado);
            }
        }
        _root->_color = BLACK;
    }

    template <class T>
    void RBT<T>::Rotate(RBTNode<T>* x, bool toLeft) {
        int left=0,right=1;
        if(!toLeft){left=1,right=0;}
        
        RBTNode<T>* y = x->_child[right];
        x->_child[right] = y->_child[left];
        y->_child[left]->_parent = x;
        y->_parent = x->_parent;

        if (x->_parent->isNil())
            _root = y;
        else
            if(x == x->_parent->_child[left])
                x->_parent->_child[left] = y;
            else
                x->_parent->_child[right] = y;

        y->_child[left] = x;
        x->_parent = y;
    }

    template <class T>
    RBTNode<T>* RBT<T>::Minimum(RBTNode<T>* node) {
    
    }
    
    template <class T>
    RBTNode<T>* RBT<T>::Maximum(RBTNode<T>* node){
    
    }
    
    template <class T>
    RBTNode<T>* RBT<T>::Successor(RBTNode<T>* node) {
    
    }
    
    template <class T>
    RBTNode<T>* RBT<T>::Predecessor(RBTNode<T>* node) {
    
    }

    template <class T>
    void RBT<T>::DeleteFixUp(RBTNode<T>* x){
    
    }

    template <class T>
    RBTNode<T>* RBT<T>::Remove(RBTNode<T>* z){
    
    }

    template <class T>
    RBTNode<T>* RBT<T>::Search(const T& key){
        
    }

    template <class T> 
    RBT<T>::~RBT() {
        if (_nil)
            delete _nil;
    }


    
    // Use the online Graphviz: http://www.webgraphviz.com/
    template <class T>
    void RBT<T>::PrintDot(){  
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
    
    
    template <class T>
    void RBT<T>::UpdateIdRec(RBTNode<T>* node){
        if (!node->isNil()){
            node->_nodeId = _nodeIdCount++;
            UpdateIdRec(node->_child[0]);
            UpdateIdRec(node->_child[1]);
        }
    }
    
    template <class T> 
    void RBT<T>::PrintDotNodeRec(RBTNode<T>* node){
        if (!node->isNil()){
            _stream << "\t" << node->_nodeId << " [";
            _stream << "label=\"" << node->_key;
            _stream << "\"";
            _stream << " style=filled fillcolor=";
            if (node->_color == RED)
                _stream << "indianred1";
            else
                _stream << "lightgray";
            _stream << "];" << std::endl;
    
            for (int i = 0; i < 2; ++i){
                if (!node->_child[i]->isNil())
                    PrintDotNodeRec(node->_child[i]);
                else
                    PrintDotNullNode();
            }
        }
    }
    
    template <class T>
    void RBT<T>::PrintDotEdgeRec(RBTNode<T>* node){
        if (node && !node->isNil()){
            for (int i = 0; i < 2; ++i){
                if (!node->_child[i]->isNil()){
                    _stream << "\t" << node->_nodeId << " -> " << node->_child[i]->_nodeId;
                    _stream << " [dir=none];" << std::endl;
                    PrintDotEdgeRec(node->_child[i]);
                
                    
                }else
                    PrintDotNullEdge(node);
            }
        }
    }
    
    
    template <class T>
    void RBT<T>::PrintDotNullNode(){
        _stream << "\tn" << _nullNodeCount;
        _stream << " [shape=square label=\"\" width=0.2];" << std::endl;
        _nullNodeCount++;
    }
    
    template <class T>
    void RBT<T>::PrintDotNullEdge(RBTNode<T>* node){
        _stream << "\t" << node->_nodeId << " -> n" << _nullNodeCount;
        _stream << " [dir=none];" << std::endl;
        _nullNodeCount++;
    }
    
    template <class T>
    void RBT<T>::PrintInOrder(){
        PrintInOrderRec(_root);
    }
    
    template <class T>
    void RBT<T>::PrintInOrderRec(RBTNode<T>* node){
        if (!node->isNil()){
            PrintInOrderRec(node->_child[0]);
            _stream << node->_key << std::endl;
            PrintInOrderRec(node->_child[1]);
        }
    }
}

#endif // RBT_H
