#include <bits/stdc++.h>

using namespace std;

template<class T>
struct Info {
	T subtreeMaxKey;
	int subtreeSize;
};
template<class T>
struct Node {
	Node<T>(){}
	Node<T> *leftc, *rightc, *parent;
    bool red;
	T key;
	Info<T> info;
	void Maintain();
	
};
template<class T>
struct RedBlackTree {
	Node<T> *leaf, *root;
	RedBlackTree();
	Node<T>* NewNode(T key);
	Node<T>* RotateLeft(Node<T> *child);
	Node<T>* RotateRight(Node<T> *child);
	Node<T>* Insert(Node<T> *is);
	Node<T>* Insert(T key);
	Node<T>* Find(T key);
	Node<T>* Findkth(int k);
	bool isLeaf(Node<T>* node);
	bool isLeftChild(Node<T>* node);
	bool isRightChild(Node<T>* node);
	Node<T>* GetSibling(Node<T>* node);
	Node<T>* RotateUp(Node<T> *node);
	Node<T>* InsertFixUp(Node<T> *node);
	Node<T>* Successor(Node<T> *node);
	Node<T>* LowerBound(T key);
	Node<T>* UpperBound(T key);
	Node<T>* Delete(T key);
	Node<T>* DeleteFixUp(Node<T>*);
	bool operator == (const T &k1, const T &k2);
	bool operator <= (const T &k1, const T &k2);
};
template<class T>
struct Tester {
	RedBlackTree<T>* tree;
	Tester<T>();
	void PrintTree(RedBlackTree<T>*);
	void Test(const char* inputfile);
};
template<class T>
bool RedBlackTree<T>::isLeftChild(Node<T>* node) {
	assert(node->parent != leaf);
	return node->parent->leftc == node;
}
template<class T>
bool RedBlackTree<T>::isRightChild(Node<T>* node) {
	assert(node->parent != leaf);
	return node->parent->rightc == node;
}

template<class T>
bool RedBlackTree<T>::isLeaf(Node<T>* node) {
	return node == leaf;
}
template<class T>
void Node<T>::Maintain() {
	info.subtreeSize = leftc->info.subtreeSize + rightc->info.subtreeSize;
	info.subtreeMaxKey = max(key,
			max(leftc->info.subtreeMaxKey, rightc->info.subtreeMaxKey));
}
template<class T>
Node<T>* RedBlackTree<T>::RotateUp(Node<T>* node) {
	assert(node->parent != leaf);
	if(isLeftChild(node))
		return RotateRight(node);
	else
		return RotateLeft(node);
}
template<class T>
Node<T>* RedBlackTree<T>::GetSibling(Node<T> *node) {
	assert(node->parent != leaf);
	Node<T> *p = node->parent;
	if(p->leftc == node) return p->rightc;
	else return p->leftc;
}
template<class T>
Tester<T>::Tester() {
	tree = new RedBlackTree<T>();
}
template<class T>
void Tester<T>::PrintTree(RedBlackTree<T>* Tree) {
	puts("Start PrintTree");
	puts("---------------------------");
	queue<Node<T>*> que;
	que.push(Tree->root);
	while(!que.empty()) {
		auto v = que.front();
		que.pop();
		printf("Node: %d, color: %d, leftc: %d, rightc: %d, parent: %d\n",
				v->key, v->red, v->leftc->key, v->rightc->key, v->parent->key);
		if(!Tree->isLeaf(v->leftc)) que.push(v->leftc);
		if(!Tree->isLeaf(v->rightc)) que.push(v->rightc);
	}
	puts("End PrintTree");
	puts("----------------------------");
}
template<class T>
void Tester<T>::Test(const char* inputfile) {
	ifstream in(inputfile);
	if(!in.is_open()) {
		puts("openfile error");
		return;
	}
	int cases;
	in >> cases;
	for(int i = 0; i < cases; i++) {
		string op;
		in >> op;
		int x;
		in >> x;
		if(op == "Insert") {
			tree->Insert(x);
		} else if(op == "RotateLeft"){
			auto p = tree->Find(x);
			tree->RotateLeft(p);
		} else if(op == "RotateRight") {
			auto p = tree->Find(x);
			tree->RotateRight(p);
		}
		puts("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
		printf("end operation %d\n", i + 1);
		PrintTree(tree);
	}
	puts("end operation");
	PrintTree(tree);
	Node<T>* c = tree->Find(1);
	while(c != tree->leaf) {
		cout << c->key << endl;
		c = tree->Successor(c);
	}
	in.close();
}
template<class T>
Node<T>* RedBlackTree<T>::Insert(T key) {
	Node<T>* is = NewNode(key);
	is->key = key;
	Insert(is);
}
template<class T>
Node<T>* RedBlackTree<T>::NewNode(T key) {
	Node<T>* p = new Node<T>();
	p->parent = p->leftc = p->rightc = leaf;
	p->red = 1;
	p->info.subtreeSize = 1;
	p->info.subtreeMaxKey = key;
	return p;
}
template<class T>
RedBlackTree<T>::RedBlackTree() {
	leaf = new Node<T>();
	leaf->key = -1;
	leaf->red = 0;
	leaf->parent = leaf->leftc = leaf->rightc = leaf;
	leaf->info.subtreeSize = 0;
	leaf->info.subtreeMaxKey = 0;
	root = leaf;
}
template<class T>
Node<T>* RedBlackTree<T>::Insert(Node<T> *is) {
	Node<T>* now = root, *p = leaf;
	while(now != leaf) {
		assert(now->key != is->key);
		p = now;
		if(now->key > is->key) now = now->leftc;
		else now = now->rightc;
	}
	if(p == leaf) {
		is->red = 0;
		return root = is;
	}
	else {
		if(p->key > is->key) p->leftc = is;
		else p->rightc = is;
		is->parent = p;
		is = InsertFixUp(is);
		return is;
	}
}
template<class T>
Node<T>* RedBlackTree<T>::Find(T key) {
	Node<T>* now = root;
	while(now != leaf) {
		if(now->key == key) return now;
		if(now->key > key) now = now->leftc;
		else now = now->rightc;
	}
	return leaf;
}
template<class T>
Node<T>* RedBlackTree<T>::RotateLeft(Node<T> *child) {
	Node<T> *p = child->parent;
	assert(p != 0);
	assert(child != p->leftc);
	Node<T> *x = p->leftc;
	Node<T> *y = child->leftc;
	Node<T> *z = child->rightc;
	Node<T> *pp = p->parent;
	swap(*p, *child);
	p->rightc = z;
	p->leftc = child;
	p->parent = pp;
	child->parent = p;
	child->rightc = y;
	child->leftc = x;
	x->parent = child;
	z->parent = p;
	child->Maintain();
	p->Maintain();
	return p;
}
template<class T>
Node<T>* RedBlackTree<T>::RotateRight(Node<T> *child) {
	Node<T> *p = child->parent;
	assert(p != 0);
	assert(child != p->rightc);
	Node<T> *x = child->leftc;
	Node<T> *y = child->rightc;
	Node<T> *z = p->rightc;
	Node<T> *pp = p->parent;
	swap(*p, *child);
	p->rightc = child;
	p->leftc = x;
	p->parent = pp;
	child->parent = p;
	child->rightc = z;
	child->leftc = y;
	x->parent = p;
	z->parent = child;
	child->Maintain();
	p->Maintain();
	return p;
}
template<class T>
Node<T>* RedBlackTree<T>::InsertFixUp(Node<T> *node) {
	while(true) {
		// node is root
		if(node->parent == leaf) {
			root = node;
			root->red = 0;
			break;
		}
		// parent is black
		if(node->parent->red == 0) {
			break;
		}
		// case 1: uncle is red
		if(GetSibling(node->parent)->red == 1) {
			node = RotateUp(node);
			node = RotateUp(node);
			node->rightc->red = node->leftc->red = 0;
		}
		// case 2: uncle is black
		else {
			Node<T>* p;
			if((isLeftChild(node) && isRightChild(node->parent))
				|| isRightChild(node) && isLeftChild(node->parent)) {
				node = RotateUp(node);
				p = RotateUp(node);
			} else {
				p = RotateUp(node->parent);
			}
			p->red = 0;
			p->leftc->red = p->rightc->red = 1;
			break;
		}
	}
	return node;
}
template<class T>
Node<T>* RedBlackTree<T>::Successor(Node<T> *node) {
	int key = node->key;
	while(true) {
		if(node->info.subtreeMaxKey <= key) {
			if(node != root) {
				node = node->parent;
				continue;
			}
			else {
				break;
			}
		}
		else {
			if(node->leftc->info.subtreeMaxKey > key) node = node->leftc;
			else if(node->key > key) {
				break;
			}
			else {
				node = node->rightc;
			}
		}
	}
	if(node->key <= key) return leaf;
	return node;
}
template<class T>
Node<T>* RedBlackTree<T>::LowerBound(T key) {
	Node<T>* node = root;
	while(true) {
		if(node->key == key) break;
		if(key <= node->leftc->key) node = node->leftc;
		else node = node->rightc;
	}
	return node;
}
template<class T>
Node<T>* RedBlackTree<T>::UpperBound(T key) {
	
}
int main() {

	Tester<int> tester = Tester<int>();
	tester.Test("/home/thyrix/Data/RedBlackTreeTest/InsertTestCase1");
	//tester.Test("/home/thyrix/Data/RedBlackTreeTest/RotateTestCase1");

	return 0;
}
