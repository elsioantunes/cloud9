#include <iostream>
#include <vector>
using namespace std;

class Trie{
    private:
        struct Node{
            int key;
            bool end;
            vector<Node*> child;
            Node(){
                child.resize(32);
                key = 0;
                end = false;
            }
        };
        Node *root = new Node;

    public:
        Trie(){
            //root = new Node;
        }
        
        void insert(vector<int> arr){
            Node *current = root;
            for(int i=0; i<arr.size(); i++){
                if(!current->child[arr[i]])
                    current->child[arr[i]] = new Node();
                current = current->child[arr[i]];
            }
            current->end = true;
        }
        

        void list(){
            vector<int> l;
            list(root, l);
        }
        
        void list(Node *node, vector<int> arr){
            if(node->end)
                printArr(arr);

            for(int i=0; i<32; i++)
                if(node->child[i])
                    list(node->child[i], merge(arr, i));
        }
        
        vector<int> merge(vector<int> arr, int i){
            vector<int >aux = arr;
            aux.push_back(i);
            return aux;
        }
        
        void printArr(vector<int> arr){
            for(int i=0; i<arr.size(); i++)
                cout << arr[i] << " ";
            cout << endl;
        }

};