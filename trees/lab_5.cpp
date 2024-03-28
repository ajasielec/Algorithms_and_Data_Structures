//Anna Jasielec, gr. 4
//lab_5

#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <thread>

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

//function to find minimum
BSTNode* BSTNode::min(BSTNode* root) {
	while (root->Left != NULL) {
		root = root->Left;
	}
	return root;
}

//function to find minimum
BSTNode* BSTNode::max(BSTNode* root) {
	while (root->Right != NULL) {
		root = root->Right;
	}
	return root;
}

//function to find successor
BSTNode* BSTNode::inOrderSuccessor(BSTNode* n) {
	if (n->Right != NULL) {		//jesli jest prawe poddrzewo
		return min(n->Right);	//najmniejszy na prawo
	}
	BSTNode* p = n->Parent;
	while (p != NULL && n == p->Right) {	//cofamy siê do góry
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

//function to insert node
void insertBST(BSTNode*& root, BSTNode* x) {
	if (!root) {
		root = x;
		//exit;
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

//funkcja sprawdzajaca czy podany czas nie koliduje z innymi w drzewie
bool czyNieMaKolizji(BSTNode* root, int val) {
	if (root != NULL) {
		if (root->key - val <=3 && root->key - val >= -3) {
			return false;
		}
		else {
			czyNieMaKolizji(root->Left, val);
			czyNieMaKolizji(root->Right, val);
		}
	}
	//return true;
}

//funkcja sprawdzajaca czy mozna wyladowac
bool czyMoznaLadowac(BSTNode* root, int ile_do_ladowania, int czas_aktualny) {
	bool war1=1;
	bool war2=1;

	//jesli czas aktualny jest mniejszy od podanego to mozna
	if (czas_aktualny > ile_do_ladowania) {
		war1 = false;
		cout << "Czas mniejszy niz aktualny. ";
	}
	else war1 = true;

	//jesli inne ladowania nie sa +/-3 to mozna
	war2 = czyNieMaKolizji(root, ile_do_ladowania);
	if (war2 == false) {
		cout << "Koliduje z innym ladowaniem. ";
	}

	//oba warunki musza byc spelnione aby wyladowac
	if (war1 && war2) return true;
	else return false;
}

//funkcja zmiejszajaca wartosc kazdego wezla o 1
void zmiejszCzas(BSTNode*& root) {
	if (root != NULL) {
		root->key -= 1;
		zmiejszCzas(root->Left);
		zmiejszCzas(root->Right);
	}
}

//funkcja usuwajaca elementy ktore juz wyladowaly
void UsunWyladowanych(BSTNode*& root, BSTNode*& node) {
	if (node != NULL) {
		if (node->key == 0) {
			removeBST(root, node);
			}
		UsunWyladowanych(root, node->Left);
		UsunWyladowanych(root, node->Right);
	}
}

int main() {
	cout << "W wyswietlanej liscie zdarzen pierwsza liczba to ilosc iteracji, nastepne to czasy do kolejnych ladowan" << endl;
	int czas_do_ladowania;
	int czas_aktualny = 37;
	time_t czas_start;
	
	bool mozna_ladowac;

	//lista oczekiwanych zdarzen
	BSTNode* root = NULL;
	root = BSTNode::Insert(root, 0);
	root = BSTNode::Insert(root, 41);
	root = BSTNode::Insert(root, 47);
	root = BSTNode::Insert(root, 50);
	root = BSTNode::Insert(root, 58);

	//lista planowanych ladowan
	cout << "\nLista planowanych ladowan: ";
	BSTNode::printTreeInOrder(root);


	//jedna iteracja petli = 1 minuta
	while (true) {
		czas_start = time(NULL);

		//wypisanie aktualnego czasu:
		cout << "Aktualny czas: " << czas_aktualny;

		//rezerwacja (3 zdarzenia na raz)
		for (int i = 0; i < 3; i++) {
			cout << "\nPodaj ile czasu zostalo do ladowania:";
			cin >> czas_do_ladowania;
			mozna_ladowac = czyMoznaLadowac(root, czas_do_ladowania, czas_aktualny);
			if (mozna_ladowac) {
				root = BSTNode::Insert(root, czas_do_ladowania);
				cout << "Pomyslnie dodano." << endl;
			}
			else {
				cout << "Nie mozna wyladowac." << endl;
			}
		}

		//pobieranie czasu aktualnego z systemu
		czas_aktualny = time(NULL) - czas_start;

		//zmiejszanie wszystkich wartosci o 1
		zmiejszCzas(root);

		//usuwanie z listy zdarzen, tych co juz wyladowali
		UsunWyladowanych(root, root);

		//lista planowanych ladowan
		cout << "\nLista planowanych ladowan: ";
		BSTNode::printTreeInOrder(root);
		cout << endl;

		}

	return 0;
}
