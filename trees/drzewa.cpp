//Anna Jasielec, gr. 4
//lab_4

#include <iostream>
#include <stdlib.h>

using namespace std;

//wskaznikowa implementacja elementu drzewa
struct BSTNode {
	int key;		
	BSTNode* Left;	
	BSTNode* Right;
	BSTNode* Parent;

	static BSTNode* Insert(BSTNode* node, int key);
	static void printTreePreOrder(BSTNode* node);
	static void printTreePostOrder(BSTNode* node);
	static void printTreeInOrder(BSTNode* node);

	static BSTNode* min(BSTNode* root);
	static BSTNode* max(BSTNode* root);

	static int treeHeight(BSTNode* root);

	static BSTNode* inOrderSuccessor(BSTNode* n);
	static BSTNode* inOrderPredeccessor(BSTNode* n);
};


//insert function
BSTNode* BSTNode::Insert(BSTNode* node, int key)
{
	if (node == NULL)
	{
		node = new BSTNode;
		node->key = key;
		node->Left = NULL;
		node->Right = NULL;
		node->Parent = NULL;
	}
	else if (node->key < key) {
		node->Right = Insert(node->Right, key);
		node->Right->Parent = node;
	}
	else
	{
		node->Left = Insert(node->Left, key);
		node->Left->Parent = node;
	}

	return node;

}

//=====================ZADANIE 1=========================//
//function to print pre order
void BSTNode::printTreePreOrder(BSTNode* node) {
	
	if (node != NULL) {
		cout << node->key << " ";
		printTreePreOrder(node->Left);
		printTreePreOrder(node->Right);
	}
}

//function to print post order
void BSTNode::printTreePostOrder(BSTNode* node) {
	if (node != NULL) {
		printTreePostOrder(node->Left);
		printTreePostOrder(node->Right);
		cout << node->key << " ";
	}
}

//function to print in order
void BSTNode::printTreeInOrder(BSTNode* node) {
	if (node != NULL) {
		printTreeInOrder(node->Left);
		cout << node->key << " ";
		printTreeInOrder(node->Right);
	}
}


//=====================ZADANIE 2=========================//
//function to find minimum
BSTNode* BSTNode::min(BSTNode* root) {
	while (root -> Left!=NULL) {
		root = root->Left;
	}
	return root;
}

//function to find minimum
BSTNode* BSTNode::max(BSTNode* root) {
	while (root -> Right!=NULL) {
		root = root->Right;
	}
	return root;
}

//==================ZADANIE 3=====================//
//function calculating height of the tree
int BSTNode::treeHeight(BSTNode* root) {
	int left_height = 0;
	int right_height = 0;

	if (root != NULL) {
		left_height = treeHeight(root->Left);
		right_height = treeHeight(root->Right);
		if (left_height > right_height) {
			return left_height + 1;
		}
		else return right_height + 1;
	}
}


//==================ZADANIE 4=====================//
//function to find successor
BSTNode* BSTNode::inOrderSuccessor(BSTNode* n) {
	if (n->Right != NULL) {		//jesli jest prawe poddrzewo
		return min(n->Right);	//najmniejszy na prawo
	}
	BSTNode* p = n->Parent;
	while (p != NULL && n == p->Right) {	//cofamy się do góry
		n = p;
		p = p->Parent;
	}
	return p;
}

//function to find predeccessor
BSTNode* BSTNode::inOrderPredeccessor(BSTNode* n) {
	if (n->Left != NULL) {		//jesli jest lewe poddrzewo
		return max(n->Left);	//najwiekszy na lewo
	}
	BSTNode* p = n->Parent;
	while (p != NULL && n == p->Left) {	//cofamy sie do gory
		n = p;
		p = p->Parent;
	}
	return p;
}

//==================ZADANIE 5=====================//
//function to insert node
void insertBST(BSTNode*& root, BSTNode* x) {
	if (!root) {
		root = x;
		exit;
	}
	BSTNode* p = 0;		//parent
	BSTNode* s = root;		//son
	while (s) {
		p = s;
		if (p->key > x->key)	s = p->Left;
		else 					s = p->Right;
	}
	x->Parent = p;
	if (p->key > x->key)		p->Left = x;		//x lewym synem
	else						p->Right = x;		//x prawym synem
}

//function to delete node
void removeBST(BSTNode*& root, BSTNode* z) {
	BSTNode* y;
	if (z->Left && z->Right) 
		y = BSTNode::inOrderSuccessor(z);	//do usuniecia
	else 
		y = z;
	
	BSTNode* x;
	if (y->Left)		//czy y ma lewego syna
		x = y->Left;
	else 
		x = y->Right;
	
	if (x)
		x->Parent = y->Parent;
	
	if (y->Parent) {
		if (y == y->Parent->Left)
			y->Parent->Left = x;
		else
			y->Parent->Right = x;
	}
	else 
		root = x;
	if (y != z)
		z->key = y->key;
	delete y;
}


int main() {

	BSTNode* root = NULL;  // Creating an empty tree
	BSTNode* min_node = NULL;
	BSTNode* max_node = NULL;
	BSTNode* succ_node = NULL;
	BSTNode* pred_node = NULL;

	root = BSTNode::Insert(root, 15);
	root = BSTNode::Insert(root, 10);
	root = BSTNode::Insert(root, 20);
	root = BSTNode::Insert(root, 25);
	root = BSTNode::Insert(root, 8);
	root = BSTNode::Insert(root, 12);

	//zad 1
	//a) print pre order
	cout << "Zadanie 1." << endl;
	cout << "a) Pre-Order traversal of the BST: ";
	BSTNode::printTreePreOrder(root);

	//b) print post order
	cout << "\nb) Post-Order traversal of the BST: ";
	BSTNode::printTreePostOrder(root);

	//c) print in order
	cout << "\nc) In-Order traversal of the BST: ";
	BSTNode::printTreeInOrder(root);

	//zad 2
	cout << "\n\nZadanie 2." << endl;
	//a) find minimum
	min_node = BSTNode::min(root);
	cout << "a) minimum: " << min_node->key << endl;
	//b) find maximum
	max_node = BSTNode::max(root);
	cout << "b) maksimum: " << max_node->key << endl;

	//zad 3
	//tree height
	cout << "\nZadanie 3." << endl;
	cout << "Wysokosc drzewa: " << BSTNode::treeHeight(root)-1 << endl;

	//zad 4
	//a) successor
	BSTNode* temp = root->Left;
	succ_node = BSTNode::inOrderSuccessor(temp);
	cout << "\nZadanie 4." << endl;
	cout << "a) Nastepnikiem " << temp->key <<" jest " << succ_node->key;

	//b) predeccessor
	temp = root->Right->Right;
	pred_node = BSTNode::inOrderPredeccessor(temp);
	cout << "\nb) Poprzednikiem " << temp->key << " jest " << pred_node->key << endl;

	//zad 5
	//a) insert node
	BSTNode* aux = NULL;
	aux = BSTNode::Insert(aux, 14);
	insertBST(root, aux);
	cout << "\nZadanie 5." << endl << "a) Drzewo po dodaniu wezla " << aux->key << ": ";
	BSTNode::printTreePreOrder(root);
	
	//b) delete node
	aux = root->Left;
	cout << "\nb) Drzewo po usunieciu wezla " << aux->key << ": ";
	removeBST(root, aux);
	BSTNode::printTreePreOrder(root);
	cout << endl;

	return 0;
}