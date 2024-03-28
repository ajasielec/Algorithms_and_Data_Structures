//Anna Jasielec
// AiSD, lab2, z.4-5
//lista i kolejka

#include <iostream>
#include <cstdlib>
#define MAX_SIZE 100

using namespace std;

//LISTA, IMPLEMENTACJA WSKAZNIKOWA (do zadania 4)
struct NODE {
	int val;
	NODE* next;
}*head = NULL;

//wstawianie na poczatek listy
void insertHead(NODE*& head, int x) {
	NODE* tmp = new NODE;
	tmp->val = x;
	tmp->next = head;
	head = tmp;
}

//czyszczenie listy
void deleteList(NODE** head) {
	NODE* tmp = *head;
	NODE* next;
	while (tmp != nullptr) {
		next = tmp->next;
		delete tmp;
		tmp = next;
	}
	*head = NULL;
}

//wypisywanie listy
void displayList(NODE* head) {
	NODE* tmp = head;
	while (tmp != nullptr) {
		cout << tmp->val << ' ';
		tmp = tmp->next;
	}
}


//KOLEJKA, IMPLEMENTACJA TABLICOWA (do zadania 5):
struct Queue {
	int myqueue[MAX_SIZE];
	int front;
	int rear;

	//konstruktor kolejki
	Queue() {
		front = -1;
		rear = -1;
	}

	//metoda sprawdzaj�ca, czy kolejka jest pe�na
	bool isFull() {
		if (front == 0 && rear == MAX_SIZE - 1) {
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

	//metoda usuwaj�ca element z kolejki (z pocz�tku kolejki)
	int dequeue() {
		int val;
		if (isEmpty()) {
			cout << "Queue is empty!\n";
			return -1;
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

//===========================ZADANIA=====================================//
/*
	4. Po��cz dwie listy (implementacja wska�nikowa) w nast�puj�cy spos�b: el_listy1, el_listy2,
	el_listy1, el_listy2, itd. Wynik po��czenia powinien znajdowa� si� w li�cie pierwszej. Lista
	druga po zako�czeniu ��czenia powinna by� pusta. Je�li druga lista oka�e si� d�u�sza ni�
	pierwsza, do��cz pozosta�e elementy listy drugiej na koniec listy pierwszej.
*/

void polacz(NODE** head1, NODE** head2) {
	//stworzenie listy zapasowej
	NODE* head_tmp = nullptr;
	NODE* tmp;
	NODE* next;

	//uzupelnienie listy tmp na przemian elementami z listy 1 i 2
	NODE* tmp1 = *head1;
	NODE* next1;
	NODE* tmp2 = *head2;
	NODE* next2;

	while (tmp1 != nullptr && tmp2 != nullptr) {
		insertHead(head_tmp, tmp1->val);
		insertHead(head_tmp, tmp2->val);
		next1 = tmp1->next;
		tmp1 = next1;
		next2 = tmp2->next;
		tmp2 = next2;
	}

	//dodanie na koniec listy pozostalych elementow z listy 2
	while (tmp2 != nullptr) {
		insertHead(head_tmp, tmp2->val);
		next2 = tmp2->next;
		tmp2 = next2;
	}

	//usuniecie zawartosci list
	deleteList(head1);
	deleteList(head2);

	//umieszczenie l_tmp w l_1
	tmp = head_tmp;
	while (tmp != nullptr) {
		insertHead(*head1, tmp->val);
		next = tmp->next;
		tmp = next;
	}
}




/*
	ZADANIE 5. Napisz funkcj� Usu�X, kt�ra z kolejki prostej usunie element o warto�ci x, 
		je�li taki element w kolejce si� znajduje.
*/
void UsunX(Queue* q, int x) {
	int rear = q->rear;
	int front = q->front;

	//przechodzenie przez kolejke:
	for (int i = front; i <= rear; i++) {
		//sprawdzanie czy w kolejce jest element x
		if (q->myqueue[i] == x) {
			//usuwanie elementu x
			for (int j = i; j <= rear; j++) {
			q->myqueue[j] = q->myqueue[j + 1];
			}
			(q->rear)--;
		}
	}
}


int main() {
	/*
		Zadanie 4.
	*/
	cout << "Zadanie 4.\n";

	//utworzenie dw�ch list
	NODE* head1 = nullptr;
	NODE* head2 = nullptr;

	//wprowadzenie element�w do listy 1 i wy�wietlenie jej
	for (int i = 0; i < 4; i++) {
		insertHead(head1, i + 1);
	}
	cout << "Lista 1: ";
	displayList(head1);

	//wprowadzenie element�w do listy 2 i wy�wietlenie jej
	for (int i = 0; i < 5; i++) {
		insertHead(head2, i + 4);
	}
	cout << "\nLista 2: ";
	displayList(head2);

	//wywolanie funkcji laczacej dwie listy
	polacz(&head1, &head2);

	//wypisanie listy 1 po polaczeniu
	cout << "\nLista 1 po polaczeniu: ";
	displayList(head1);

	//wypisanie listy 2 po polaczeniu
	cout << "\nLista 2 po polaczeniu: ";
	displayList(head2);




	/*
		Zadanie 5.
	*/
	cout << "\n\nZadanie 5. ";
	//utworzenie kolejki
	Queue q;

	//uzupelnienie kolejki
	for (int i = 0; i < 5; i++) {
		q.enqueue(i+1);
		q.enqueue(i + 3);
	}

	//wyswietlenie kolejki
	cout << "\nKolejka: ";
	q.display();

	//podanie elementu do usuniecia
	int x = 0;
	cout << "\nPodaj liczbe, ktora chcesz usunac z kolejki: ";
	cin >> x;

	//wywo�anie funkcji usuwajacej element x
	UsunX(&q, x);

	//wyswietlenie kolejki po usunieciu elementu x
	cout << "Kolejka po usunieciu elementu " << x << ": ";
	q.display();
	cout << endl;

	return 0;
}