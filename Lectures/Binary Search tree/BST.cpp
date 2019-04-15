template<class T>
class BST {
	class Node {
	public:
		T val; //T is given when declare 
		Node* left;
		Node* right;
		Node* parent;

		Node(T el) {
			this-> val = el;
			this->left = nullptr;
			this->right = nullptr;
			this->parent = nullptr; // set when u insert because we know the parent to insert
		}

		Node(const Node &other){
			val = other.val;
			if(other.left = nullptr)
				left = nullptr;
			else
				left = new Node(*(other.left));
			if(other.right = nullptr)
				right = nullptr;
			else
				right = new Node(*(other.right));
		}
		~Node(){
			delete left; // invokes destructor
			delete right; //invokes destructor
		}
	}
//-----------------------------------------------------------//

	Node* root;
	void copy(const BST & other) { //helper function
		root = new Node(*(other.root));
	}
	void destroy() { //helper function
		delete root;
	}

	Node* findMin() const {
		Node* current = root;
		if(root == nullptr)
			return nullptr;
		else {
			current = n->parent;
			while(current != nullptr && current->left != n) {
				n = current;
				current = current->parent;
			} 
		}
	}

	Node* successor(Node *n) { //find next largest value 
		//if have right subtree -> next largest = left most element subtree of the right
		//else if no right subtree -> first parent from the left side 
		//to make feasible -> need to be able to back track a node in the BST
		if(n == nullptr){return nullptr;}

		Node* current = n;
		if(current->right!=nullptr){
			current = current->right;
			while(current->left != nullptr) {
				current = current->left;
			}
			return current;
		} else {
			while(current->parent->left != current){
				current = current->parent;
			}
			return current;
		}

	}

	public:
		BST() : root(nullptr) {} //constructor -> set root to null
		~BST() {destroy();} //invokes destructor of the element (recursive delete) 

		BST(const BST &other){ // copy constructor 
			copy(other);
		}

		BST& opperator=(const BST &other) {
			if(this == &other) {
				return this;
			}
			destroy(this);
			copy(other);
		}

		//returns true if el is in the tree
		bool find (T el) const {
			Node current = root;
			while(current != nullptr) { //traverse through the tree structure 
				if(current.val == el)
					return true;
				else if (current.val < el)
					current = current->left; 
				else
					current = current->right;
			}
			return false;
		}

		//inserts a new element into the tree
		void insert(T el) {
			Node* n = new Node(el);
			Node* current = root;
			Node* prev = nullptr;
			if(current == nullptr) {
				root = n;
			}
			else{
				while(current != nullptr) {
					if (current->val < el) {
						prev = current;
						current = current->right; 
					}
					else {
						prev = current;
						current = current->left;
					}
				}
				if(prev->val > el)
					prev->left = n;
				else
					prev->right = n;
				n->parent = prev;
			}
		}
		void remove(Node* n){}; 
		/*
		3 cases
			case 1: node is leaf
				set parent to null and delete node
			case 2: 1 child
				set parent to point to nect child
			case 3: 2 child
				set successor to current element and link
		*/
}