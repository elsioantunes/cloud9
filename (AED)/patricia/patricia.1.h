    

			// Forward declaration of the Patricia class

				class Patricia;

			///////////////////////////////////////////////////////////////////////////////
			/// Patricia node.
			///
			/// Implements a Patricia node.
			///////////////////////////////////////////////////////////////////////////////

				class PatriciaNode {
					friend class Patricia ;

					public:
						PatriciaNode();

					/// Node key getter.
					bitset*key() {
						return _key;
					}

					protected:
						size_t _bitIndex; ///< Index of the comparison bit.
					bitset*_key; ///< Bitset key.

					PatriciaNode*_parent; ///< Parent node.
					PatriciaNode*_left; ///< Left child (0).
					PatriciaNode*_right; ///< Right child (1).

					private:
						int _nodeId; ///< Used by PrintDot.
				};

			///////////////////////////////////////////////////////////////////////////////
			/// Constructor.
			///////////////////////////////////////////////////////////////////////////////

				pat_PatriciaNode(): _key(nullptr) {
					_bitIndex = 0;
					_parent = nullptr;
					_left = nullptr;
					_right = nullptr;
					_nodeId = 0;
				}

			///////////////////////////////////////////////////////////////////////////////
			/// Patricia class.
			///
			/// Implements a Patricia (compact prefix tree) for bitset.
			///////////////////////////////////////////////////////////////////////////////

				class Patricia {
					public:
						Patricia(ostream & stream = cout);
						~Patricia();
						void Print();
						void PrintDot();

						bool Search(bitset & key);
						bool Insert(bitset & key);
						bool Remove(bitset & key);


					protected:
						PatriciaNode*_root; ///< Root node.
						ostream & _stream; ///< Output stream used by tree walks.
						void PrintRec(PatriciaNode*node);
						void PrintDotNodeRec(PatriciaNode*node);
						void PrintDotEdgeRec(PatriciaNode*node);

					private:
						int _nodeIdCount; ///< Internal counter of PrintDot...
						void UpdateIdRec(PatriciaNode*node);

				};


			///////////////////////////////////////////////////////////////////////////////
			/// Constructor.
			///////////////////////////////////////////////////////////////////////////////

				pat_Patricia(ostream & stream): _stream(stream) {
					_root = new PatriciaNode ();
				}

			///////////////////////////////////////////////////////////////////////////////
			/// Destructor.
			///////////////////////////////////////////////////////////////////////////////

				pat_~Patricia() {
					delete _root;
				}

			///////////////////////////////////////////////////////////////////////////////
			/// Searches the given key in the patricia.
			///
			/// \param key Search key.
			///
			/// \return TRUE if the key was found, FALSE otherwise.
			///////////////////////////////////////////////////////////////////////////////

				bool pat_Search(bitset &key) {
					PatriciaNode *current = _root;

					// Descend to leaf
					while (current->_left /* || current->_right*/ ) {
						if (!key.test(N - 1 - current->_bitIndex)) {
							current = current->_left;
						} else {
							current = current->_right;
						}
					}

					if (key == *current->_key) {
						return true;
					}

					return false;
				}

			///////////////////////////////////////////////////////////////////////////////
			/// Inserts a given key in the patricia.
			///
			/// \param key Bitset key to be inserted.
			/// \return TRUE if the key was insert, FALSE otherwise.
			///////////////////////////////////////////////////////////////////////////////

				bool pat_Insert(bitset & key) {
					PatriciaNode*current = _root;

					while (current->_left) {
						if (!key.test(N - 1 - current->_bitIndex)) {
							current = current->_left;
						} else {
							current = current->_right;
						}
					}

					if (!current->_parent && !current->_key) // Root
					{
						current->_key = new bitset (key);
					} else {
						// Get first differing bit (from left to right)
						size_t diffBit = 0;
						
						while (diffBit < N && current->_key->test(N - 1 - diffBit) == key.test(N - 1 - diffBit)) {
							diffBit++;
						}
						
						if (diffBit == N)
							return false; // Key already exists

						// Ascend the tree while diffbit is lower than bit index of
						// visited nodes
						PatriciaNode *parent = current->_parent;
						
						bool fromLeft;
						if (parent) {
							fromLeft = (parent->_left == current) ? true : false;
						}
						
						while (parent && parent->_bitIndex > diffBit) {
							if (parent->_parent) {
								fromLeft = (parent == parent->_parent->_left) ? true : false;
							}
							current = parent;
							parent = parent->_parent;
						}

						// New node with new bit index
						PatriciaNode*newNode = new PatriciaNode ();
						newNode->_bitIndex = diffBit;
						newNode->_parent = parent;
						
						if (parent) {
							if (fromLeft) {
								parent->_left = newNode;
							} else {
								parent->_right = newNode;
							}
						} else {
							_root = newNode;
						}

						PatriciaNode *newLeaf = new PatriciaNode ();
						newLeaf->_key = new bitset (key);
						newLeaf->_parent = newNode;
						current->_parent = newNode;

						if (!newLeaf->_key->test(N - 1 - diffBit)) {
							newNode->_left = newLeaf;
							newNode->_right = current;
						} else {
							newNode->_left = current;
							newNode->_right = newLeaf;
						}
					}

					return true;
				}

			///////////////////////////////////////////////////////////////////////////////
			/// Removes the given key from the patrica.
			///
			/// \param key Bitset key to be removed.
			/// \return TRUE if the key was removed, FALSE otherwise.
			///////////////////////////////////////////////////////////////////////////////

				bool pat_Remove(bitset & key) {
					PatriciaNode*current = _root;

					while (current->_left) {
						if (!key.test(N - 1 - current->_bitIndex)) {
							current = current->_left;
						} else {
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
					} else {
						PatriciaNode*parent = current->_parent;
						PatriciaNode*sibling;

						if (parent->_left == current) {
							sibling = parent->_right;
						} else {
							sibling = parent->_left;
						}

						if (parent->_parent) {
							if (parent->_parent->_left == parent) {
								parent->_parent->_left = sibling;
							} else {
								parent->_parent->_right = sibling;
							}
							sibling->_parent = parent->_parent;
						} else {
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

				void pat_PrintDot() {
					_stream << "digraph Patricia {" << endl;
					_stream << "\tedge [fontname=\"Helvetica\" dir=none];" << endl;
					_stream << "\tnode [fontname=\"Helvetica\" shape=circle];" << endl;

					// Update node ids
					_nodeIdCount = 0;
					UpdateIdRec(_root);

					// Print list of nodes
					PrintDotNodeRec(_root);

					// Print list of edges
					PrintDotEdgeRec(_root);

					_stream << "}" << endl;
				}

			///////////////////////////////////////////////////////////////////////////////
			/// Recursively assigns an id to the nodes of a subtree.
			///
			/// \param node Root of the subtree.
			///////////////////////////////////////////////////////////////////////////////

				void pat_UpdateIdRec(PatriciaNode*node) {
					if (node) {
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

				void pat_PrintDotNodeRec(PatriciaNode*node) {
					if (node) {
						if (!node->_left && !node->_right) {
							if (node->_key) {
								_stream << "\t" << node->_nodeId;
								_stream << " [label=\"";
								_stream << node->_key->to_string();
								_stream << "\" shape=box];" << endl;
							}
						} else {
							_stream << "\t" << node->_nodeId;
							_stream << " [label=\"" << node->_bitIndex << "\"];" << endl;
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

				void pat_PrintDotEdgeRec(PatriciaNode*node) {
					if (node) {
						if (node->_left) {
							_stream << "\t" << node->_nodeId;
							_stream << "->";
							_stream << node->_left->_nodeId;
							_stream << " [label = \"0\"];" << endl;
							PrintDotEdgeRec(node->_left);
						}

						if (node->_right) {
							_stream << "\t" << node->_nodeId;
							_stream << "->";
							_stream << node->_right->_nodeId;
							_stream << " [label = \"1\"];" << endl;
							PrintDotEdgeRec(node->_right);
						}
					}
				}

			///////////////////////////////////////////////////////////////////////////////
			/// Prints the contents of the trie in non decreasing order.
			///////////////////////////////////////////////////////////////////////////////

				void pat_Print() {
					PrintRec(_root);
				}

			///////////////////////////////////////////////////////////////////////////////
			/// Recursively walks the tree in post-order from the given node.
			///
			/// \param node Non-null root of the subtree.
			///////////////////////////////////////////////////////////////////////////////

				void pat_PrintRec(PatriciaNode*node) {
					if (node) {
						PrintRec(node->_left);
						PrintRec(node->_right);
						if (!node->_left && node->_key) {
							_stream << node->_key->to_string() << endl; // Leaf
						}
					}
				}

