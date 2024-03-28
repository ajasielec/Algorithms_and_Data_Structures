#include <iostream>
#include <cstdlib>
using namespace std;

//====================LISTA==========================//
struct NODE {
	int val;    //ustaw typ
	NODE* next;
}*head = NULL;

//wstawianie na poczatek listy
void insertHead(NODE*& head, int x) {
	NODE* tmp = new NODE;
	tmp->val = x;
	tmp->next = head;
	head = tmp;
}

//wypisywanie listy
void displayList(NODE* head) {
	NODE* tmp = head;
	while (tmp != nullptr) {
		int p;
		p = tmp->val;
		cout << p << " ";
		tmp = tmp->next;
	}
}

//======================STOS============================//
struct StackNode {
	int data; //wstaw typ
	StackNode* next;
}*root = NULL;

StackNode* newNode(int data) {
	StackNode* tmp = new StackNode();
	tmp->data = data;
	tmp->next = NULL;
	return tmp;
}

//funkcja sprawdzajaca czy stos jest pusty
bool isEmpty(StackNode* root) {
	return !root;
}

//funkcja odkladajaca element na stos
void push(StackNode** root, int new_data) {
	StackNode* tmp = newNode(new_data);
	tmp->next = *root;
	*root = tmp;
}

//funkcja zdejmujaca element ze stosu
int pop(StackNode** root) {
	if (!isEmpty(*root)) {
		StackNode* tmp = *root;
		*root = (*root)->next;
		int popped = tmp->data;
		delete tmp;
		return popped;
	}
}

//funkcja wyswietlajaca stos
void displayStack(StackNode* root) {
	StackNode* tmp = root;
	while (tmp != nullptr) {
		cout << tmp->data << endl;
		tmp = tmp->next;
	}
}


//=====================KOLEJKA=====================//
//implementacja tablicowa
struct Queue {
	int myqueue[10]; //tu wstaw w³asny typ
	int front;
	int rear;

	//konstruktor kolejki
	Queue() {
		front = -1;
		rear = -1;
	}

	//metoda sprawdzaj?ca, czy kolejka jest pe?na
	bool isFull() {
		if (front == 0 && rear == 9) {
			return true;
		}
		return false;
	}

	//metoda sprawdzaj?ca, czy kolejka jest pusta
	bool isEmpty() {
		if (front == -1) return true;
		else return false;
	}

	//metoda wstawiaj?ca element do kolejki (na koniec kolejki)
	void enqueue(int val) {
		if (isFull()) {
			cout << endl << "Queue is full!\n";
		}
		else {
			if (front == -1) front = 0;
			rear++;
			myqueue[rear] = val;
		}
	}

	//metoda usuwaj?ca element z kolejki (z pocz?tku kolejki)
	int dequeue() {
		int val = 0;
		if (isEmpty()) {
			cout << "Queue is empty!\n";
			return val;
		}
		else {
			val = myqueue[front];
			if (front >= rear) {
				front = -1;
				rear = -1;
			}
			else {
				front++;
			}
			cout << endl << "Deleted: " << val;
			return val;
		}
	}

	//metoda wyswietlajaca zawartosc kolejki
	void display() {
		int i;
		if (isEmpty()) {
			cout << "Queue is empty!" << endl;
		}
		else {
			for (int i = front; i <= rear; i++) {
				cout << myqueue[i] << " ";
			}
		}
	}
};


//przeciazenie operatora <<
ostream& operator << (ostream& os, const Produkt& p) {
	return os << p.nazwa << ": " << p.cena << "zl, " << p.kalorycznoœæ << "kcal ";
}

int main() {

	return 0;
}