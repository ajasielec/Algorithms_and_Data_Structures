//Anna Jasielec
//AiSD, lab3

#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

//==============IMPLEMENTACJA KLASY, LISTY, STOSU I KOLEJKI=================//

//KLASA, przechowujaca pary liczb calkowitych
class Para {
	friend ostream& operator << (ostream& os, const Para& p);
	int x;
	int y;
public:
	Para() : x(0), y(0) {
	}
	Para(int x, int y) {
		this->x = x;
		this->y = y;
	}

	int getX() { return x; }
	int getY() { return y; }
	int getSuma() { return x + y; }

	//przeciazenie operatora +=
	Para& operator += (const Para& p) {
		this->x += p.x;
		this->y += p.y;
		return *this;
	}

	//przeciazenie operatora /
	Para operator / (const int& d) {
		Para ret;
		ret.x = this->x / d;
		ret.y = this->y / d;
		return ret;
	}
};

//przeciazenie operatora <<
ostream& operator << (ostream& os, const Para& p) {
	return os << "(" << p.x << ", " << p.y << ")  ";
}


//DO ZADANIA 1:
//IMPLEMENTACJA LISTY (wskaznikowo)
struct NODE {
	Para val;
	NODE* next;
}*head = NULL;

//wstawianie na poczatek listy
void insertHead(NODE*& head, Para x) {
	NODE* tmp = new NODE;
	tmp->val = x;
	tmp->next = head;
	head = tmp;
}

//wypisywanie listy
void displayList(NODE* head) {
	NODE* tmp = head;
	while (tmp != nullptr) {
		Para p;
		p = tmp->val;
		cout << "(" << p.getX() << ", " << p.getY() << ")  ";
		tmp = tmp->next;
	}
}


//DO ZADANIA 2:
//IMPLEMENTACJA STOSU (wskaznikowo)
struct StackNode {
	Para data;
	StackNode* next;
}*root = NULL;

StackNode* newNode(Para data) {
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
void push(StackNode** root, Para new_data) {
	StackNode* tmp = newNode(new_data);
	tmp->next = *root;
	*root = tmp;
}

//funkcja zdejmujaca element ze stosu
Para pop(StackNode** root) {
	if (!isEmpty(*root)) {
		StackNode* tmp = *root;
		*root = (*root)->next;
		Para popped = tmp->data;
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

//DO ZADANIA 3:
//KOLEJKA, IMPLEMENTACJA TABLICOWA (do zadania 5):
struct Queue {
	Para myqueue[10];
	int front;
	int rear;

	//konstruktor kolejki
	Queue() {
		front = -1;
		rear = -1;
	}

	//metoda sprawdzaj�ca, czy kolejka jest pe�na
	bool isFull() {
		if (front == 0 && rear == 9) {
			return true;
		}
		return false;
	}

	//metoda sprawdzaj�ca, czy kolejka jest pusta
	bool isEmpty() {
		if (front == -1) return true;
		else return false;
	}

	//metoda wstawiaj�ca element do kolejki (na koniec kolejki)
	void enqueue(Para val) {
		if (isFull()) {
			cout << endl << "Queue is full!\n";
		}
		else {
			if (front == -1) front = 0;
			rear++;
			myqueue[rear] = val;
		}
	}

	//metoda usuwaj�ca element z kolejki (z pocz�tku kolejki)
	Para dequeue() {
		Para val(0, 0);
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




//==========================FUNKCJE DO ZADAN============================//
/*
	ZADANIE 1.
*/
//funkcja wypisujaca sume wszystkich elementow i dodająca srednia elementow na koniec listy
void sumaISrednia(NODE** head) {
	Para suma(0, 0);
	NODE* tmp = *head;
	//obliczanie sumy
	while (tmp != nullptr) {
		suma += tmp->val;
		tmp = tmp->next;
	}
	cout << "Suma elementow listy: " << suma;

	//obliczanie sredniej
	Para srednia = suma / 10;

	//wstawianie sredniej do listy
	insertHead(*head, srednia);
}

/*
	ZADANIE 2.
*/
//funkcja, która usuwa ze stosu element maksymalny
void deleteMax(StackNode** root) {
	int n = 1;			//pozycja
	int max_n = 0;		//pozycja elementu maksymalnego
	int val = 0;		//wartosc elementow
	int max_val = 0;	//maksymalna wartosc
	Para pmax;			//element maksymalny
	StackNode* tmp = *root;

	//wyszukanie pozycji maksymalnego elementu
	while (tmp != nullptr) {
		val = tmp->data.getX() + tmp->data.getY();
		if (max_val < val) {
			max_val = val;
			pmax = tmp->data;
			max_n = n;
		}
		tmp = tmp->next;
		n++;
	}
	cout << "\nmax: " << pmax;

	//przeniesienie elementow, wystepujacych nad el. max. do innego stosu
	StackNode* zapasowy;
	tmp = *root;
	for (int i = 0; i < max_n - 1; i++) {
		push(&zapasowy, pop(root));
	}

	//usuniecie elementu maksymalnego
	pop(root);

	//ustawienie spowrotem reszty elementow na stos
	for (int i = 0; i < max_n - 1; i++) {
		push(root, pop(&zapasowy));
	}
}

/*
ZADANIE 3.
*/
//funkcja liczaca sume par liczb i sortujaca je rosnaco
void sumaISortuj(Queue* q) {

	//liczenie sumy i wlozenie jej w tablicy
	int suma = 0;
	int sumy[10];
	cout << "\nSumy par liczb:" << endl;
	for (int i = 0; i < 10; i++) {
		suma = q->myqueue[i].getX() + q->myqueue[i].getY();
		sumy[i] = suma;
		cout << suma << "\t";
	}

	//sortowanie elementow
	int i, j;
	bool swapped;
	for (i = 0; i < 9; i++) {
		swapped = false;
		for (j = 0; j < 9 - i; j++) {
			if (q->myqueue[j].getSuma() > q->myqueue[j + 1].getSuma()) {
				swap(q->myqueue[j], q->myqueue[j + 1]);
				swapped = true;
			}
		}
		if (swapped == false) break;
	}
}


int main() {

	//=========================ZADANIE 1==========================//
	srand(time(NULL));
`	NODE* head = nullptr;

	//tworzenie losowej pary liczby i umieszczanie jej w liscie
	for (int i = 0; i < 10; i++) {
		Para p(rand() % 100, rand() % 100);
		insertHead(head, p);
	}

	//wyswietlenie listy
	cout << "ZADANIE 1.\nLista na poczatku:\n ";
	displayList(head);
	cout << endl;

	//wywolanie funkcji wypisujacej sume
	sumaISrednia(&head);


	//wyswietlenie listy (11 elementow, nowy element to srednia)
	cout << "\nLista po dodaniu elementu, ktory jest srednia poprzednich elementow:\n ";
	displayList(head);


	//=========================ZADANIE 2==========================//
	//przeniesienie listy do stosu
	StackNode* root = NULL;
	NODE* tmp = head;
	for (int i = 0; i < 11; i++) {
		push(&root, tmp->val);
		tmp = tmp->next;
	}

	//wyswietlenie utworzonego stosu:
	cout << "\n\nZADANIE 2.\n Stos:" << endl;
	displayStack(root);

	//usuniecie maksymalnego elementu
	deleteMax(&root);

	//po usunieciu
	cout << "\nStos po usunieciu elementu max:" << endl;
	displayStack(root);


	//=========================ZADANIE 3==========================//
	cout << "\n\nZADANIE 3.\n";

	//przeniesienie stosu do kolejki
	Queue kolejka;
	for (int i = 0; i < 10; i++) {
		kolejka.enqueue(pop(&root));
	}

	//wyswietlenie kolejki
	cout << "Kolejka:" << endl;
	kolejka.display();

	//obliczenie sumy i posortowanie kolejki
	sumaISortuj(&kolejka);
	cout << "\nKolejka po sortowaniu:" << endl;
	kolejka.display();



	return 0;
}