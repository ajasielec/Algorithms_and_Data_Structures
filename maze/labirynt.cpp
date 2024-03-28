//Anna Jasielec, gr.4

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <limits>

using namespace std;

//deklaracje
void fillArray(string path, char** tab, int rows, int columns);
const int MAXINT = -INT_MAX;

//klasa labirynt
class Maze {
public:
	int rows;
	int columns;
	char** tab;
	int start_x, start_y, exit_x, exit_y;

	Maze() {}
	//konstruktor 
	Maze(string path, int r, int c) {
		rows = r;
		columns = c;

		// stworzenie dynamicznej tablicy dwuwymiarowej
		tab = new char* [rows];
		for (int i = 0; i < rows; i++) {
			tab[i] = new char[columns];
		}

		// wype³nianie tablicy
		fillArray(path, tab, rows, columns);

		//ustawienie poczatkowej pozycji i koncowej
		findStartAndExit();

	}

	//metoda znajdujaca poczatek i koniec
	void findStartAndExit() {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				if (tab[i][j] == 'S') {
					start_x = j;
					start_y = i;
				}
				if (tab[i][j] == 'E') {
					exit_x = j;
					exit_y = i;
				}
			}
		}
	}

	//metoda wypisujaca labirynt
	void wypiszLabirynt() {
		cout << endl;
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				cout << tab[i][j];
			}
			cout << endl;
		}
	}

	//funkcja sprawdzaj¹ca, czy dany ruch jest dozwolony
	bool isValidMove(int x, int y) {
		if (tab[x][y] == ' ' || tab[x][y] == 'E') {
			return true;
		}
		else return false;
	}

	// algorytm brute force
	bool solveMazeBruteForce(int x, int y);

	// algorytm BFS
	void solveMazeBFS();
	void piszL();

	//destruktor
	~Maze() {
		// zwolnienie pamieci
		for (int i = 0; i < rows; i++) {
			delete[] tab[i];
		}
		delete[] tab;
	}
};

// odczytywanie danych z pliku i umieszczanie w tablicy
void fillArray(string path, char** tab, int rows, int columns) {
	string line;
	ifstream myfile(path);

	if (myfile.is_open()) {
		for (int i = 0; i < rows; i++) {
			getline(myfile, line);

			for (int j = 0; j < columns; j++) {
				tab[i][j] = line[j];
			}
		}
		myfile.close();
	}
	else    cout << "Unable to open file" << endl;
}

//====================================== ALGORYTM BRUTE FORCE ====================================//
bool Maze :: solveMazeBruteForce(int x, int y) {

	//sprawdz czy znaleziono wyjscie
	if (tab[x][y] == 'E') {
		wypiszLabirynt();
		return true;
	}

	//sprawdŸ, czy mo¿na przejœæ w prawo
	if (isValidMove(x, y + 1)) {
		tab[x][y] = '.';

		//rekurencyjnie w prawo
		if (solveMazeBruteForce(x, y + 1)) {
			return true;
		}
		// jeœli ruch w prawo nie powiód³ siê, cofnij siê
		tab[x][y] = ' ';
	}

	//sprawdz czy mozna isc w dol
	if (isValidMove(x + 1, y)) {
		tab[x][y] = '.';

		if (solveMazeBruteForce(x + 1, y)) {
			return true;
		}
		tab[x][y] = ' ';
	}

	//sprawdz czy mozna isc w lewo
	if (isValidMove(x, y - 1)) {
		tab[x][y] = '.';

		if (solveMazeBruteForce(x, y - 1)) {
			return true;
		}
		tab[x][y] = ' ';
	}

	//sprawdz czy mozna isc w gore
	if (isValidMove(x - 1, y)) {
		tab[x][y] = '.';
		if (solveMazeBruteForce(x - 1, y)) {
			return true;
		}
		tab[x][y] = ' ';
	}

	return false; //nie znaleziono wyjscia
}


//====================================== ALGORYTM BFS ====================================//

struct Node {
	Node* next;
	int val;
};

//definicja kolejki:
struct queue {
private:
	Node* head;
	Node* tail;

public:
	queue() {
		head = tail = NULL;
	}
	bool isEmpty() {
		return !head;
	}
	int front() {
		if (head) return head->val;
		else return -MAXINT;
	}

	void push(int val) {
		Node* p = new Node;
		p->next = NULL;
		p->val = val;
		if (tail) tail->next = p;
		else head = p;
		tail = p;
	}

	void pop() {
		if (head) {
			Node* p = head;
			head = head->next;
			if (!head) tail = NULL;
			delete p;
		}
	}

	~queue() {
		while (head) pop();
	}
};

//rozwiazanie labiryntu metoda BFS
void Maze::solveMazeBFS() {
	queue Q;
	int current_row, current_column;
	int i, j;

	//wierzcholek startowy:
	Q.push(start_x);
	Q.push(start_y);

	while (!Q.isEmpty()) {
		current_row = Q.front();
		Q.pop();
		current_column = Q.front();
		Q.pop();

		//czy dotarlismy do wyjscia
		if (current_row == exit_y && current_column == exit_x) {
			//wypiszLabirynt();
			break;
		}

		//przeglad sasiadow
		for (i = -1; i <= 1; ++i) {
			for (j = -1; j <= 1; ++j) {
				if ((i != j) && (!i || !j)) {
					if (current_row + i > rows - 1 || current_column + j > columns - 1) {
						continue;
					}
					if (current_row + i < 0 || current_column + j < 0) {
						continue;
					}

					if (tab[current_row + i][current_column + j] == ' ') {
						//zapisujemy skad przyszlismy
						if (i == -1) tab[current_row + i][current_column + j] = 'd';
						else if (i == 1) tab[current_row + i][current_column + j] = 'g';
						else if (j == -1) tab[current_row + i][current_column + j] = 'p';
						else             tab[current_row + i][current_column + j] = 'l';

						//sasiad do kolejki
						Q.push(current_row + i);
						Q.push(current_column + j);
					}
				}
			}
		}
	}
}

void Maze::piszL() {
	int i = 0, j = 0;
	char c;

	if (tab[exit_y][exit_x] != ' ') {
		i = exit_y - 1;
		j = exit_x - 1;

		start_y = 0;
		start_x = 0;

		while ((i != start_y) || (j != start_x)) {
			c = tab[i][j];
			tab[i][j] = '.';
			switch (c) {
			case 'd': i++; break;
			case 'g': i--; break;
			case 'p': j++; break;
			case 'l': j--; break;
			}
		}
	}

	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < columns; j++) {

			switch (tab[i][j])
			{
			case 'g':;
			case 'd':;
			case 'p':;
			case 'l': tab[i][j] = ' ';
			}
			cout << tab[i][j];
		}
		cout << endl;
	}
	cout << endl;
}


//========================================= MAIN ============================================//
int main() {

	clock_t start, stop;
	float time;

	//stworzenie obiektow klasy labirynt
	Maze labirynt1("labirynt1.txt", 21, 31);
	Maze labirynt2("labirynt2.txt", 7, 10);
	Maze labirynt3("labirynt3.txt", 7, 10);

	//wypisanie labiryntow
	//cout << "Labirynt 1:" << endl;
	//labirynt1.wypiszLabirynt();
	//cout << "\nLabirynt 2:" << endl;
	//labirynt2.wypiszLabirynt();
	//cout << "\nLabirynt 3:" << endl;
	//labirynt3.wypiszLabirynt();


	//rozwiazanie labiryntow algorytmem brute force z pomiarem czasu
	cout << "Rozwiazania labiryntow algorytmem brute force:" << endl;

	cout << "\nLabirynt 1:";
	start = clock();
	labirynt1.solveMazeBruteForce(0, 0);
	stop = clock();
	time = (long double)(stop - start) / CLOCKS_PER_SEC;
	cout << "czas: " << time << endl;

	cout << "\nLabirynt 2:";
	start = clock();
	labirynt2.solveMazeBruteForce(0, 0);
	stop = clock();
	time = (long double)(stop - start) / CLOCKS_PER_SEC;
	cout << "czas: " << time << endl;

	cout << "\nLabirynt 3:";
	start = clock();
	labirynt3.solveMazeBruteForce(0, 0);
	stop = clock();
	time = (long double)(stop - start) / CLOCKS_PER_SEC;
	cout << "czas: " << time << endl;


	//zresetowanie labiryntow
	fillArray("Labirynt1.txt", labirynt1.tab, labirynt1.rows, labirynt1.columns);
	fillArray("Labirynt2.txt", labirynt2.tab, labirynt2.rows, labirynt2.columns);
	fillArray("Labirynt3.txt", labirynt3.tab, labirynt3.rows, labirynt3.columns);


	// rozwiazywanie labiryntow metoda BFS z pomiarem czasu
	cout << "\n\nRozwiazania labiryntow algorytmem BFS (Breadth-First Search):" << endl;

	cout << "\nLabirynt 1:\n";
	start = clock();
	labirynt1.solveMazeBFS();
	labirynt1.piszL();
	stop = clock();
	time = (long double)(stop - start) / CLOCKS_PER_SEC;
	cout << "czas: " << time << endl;

	cout << "\nLabirynt 2:\n";
	start = clock();
	labirynt2.solveMazeBFS();
	labirynt2.piszL();
	stop = clock();
	time = (long double)(stop - start) / CLOCKS_PER_SEC;
	cout << "czas: " << time << endl;

	cout << "\nLabirynt 3:\n";
	start = clock();
	labirynt3.solveMazeBFS();
	labirynt3.piszL();
	stop = clock();
	time = (long double)(stop - start) / CLOCKS_PER_SEC;
	cout << "czas: " << time << endl;


	return 0;
}