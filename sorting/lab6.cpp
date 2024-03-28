//Anna Jasielec
//grupa 4

#include <algorithm>
#include <iostream>
#include <math.h>
#include <time.h>

using namespace std;

//=====================IMPLEMENTACJA ROZNYCH SPOSOBOW SORTOWANIA========================//

//sortowanie b¹belkowe
void sortowanieBabelkowe(int* tab, int n) {
	long long counter = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 1; j < n - i; j++) {
			if (tab[j - 1] > tab[j]) {
				swap(tab[j - 1], tab[j]); 
				counter++;
			}
			counter++;
		}
		counter++;
	}
	cout <<"\tilosc operacji: " << counter << ", ";
}

//sortowanie przez wstawianie
void sortowaniePrzezWstawianie(int* tab, int n) {
	int pom, j;
	long long counter = 0;
	for (int i = 1; i < n; i++) {
		pom = tab[i];
		j = i - 1;

		while (j >= 0 && tab[j] > pom) {
			tab[j + 1] = tab[j];
			--j;
			counter += 3;
		}
		tab[j + 1] = pom;
		counter += 4;
	}
	cout << "\tilosc operacji: " << counter << ", ";
}

//sortowanie przez selekcje
void sortowaniePrzezSelekcje(int* tab, int n) {
	int index;
	long long counter = 0;
	for (int i = 0; i < n - 1; i++) {
		index = i;
		for (int j = i + 1; j < n; j++) {	
			if (tab[j] < tab[index]) {
				index = j;
				counter++;
			}
			counter++;
		}
		swap(tab[i], tab[index]);
		counter += 3;
	}
	cout << "\tilosc operacji: " << counter << ", ";
}

//sortowanie grzebieniowe
void sortowanieGrzebieniowe(int* tab, int n) {
	long long counter = 0;
	int gap = n;
	bool replace = true;

	while (gap > 1 || replace) {
		gap = gap * 10 / 13;
		if (gap == 0) {
			gap = 1;
			counter++;
		}

		replace = false;
		for (int i = 0; i + gap < n; i++) {
			if (tab[i + gap] < tab[i]) {
				swap(tab[i], tab[i + gap]);
				replace = true;
				counter += 2;
			}
			counter++;
		}
		counter += 3;
	}
	cout << "\tilosc operacji: " << counter << ", ";
}

//sortowanie shella
void sortowanieShella(int* tab, int n) {
	long long counter = 0;
	for (int gap = n / 2; gap > 0; gap /= 2) {
		for (int i = gap; i < n; i++) {
			int temp = tab[i];
			
			int j;
			for (j = i; j >= gap && tab[j - gap] > temp; j -= gap) {
				tab[j] = tab[j - gap];
				counter += 2;
			}
			tab[j] = temp;
			counter += 3;
		}
		counter++;
	}
	cout << "\tilosc operacji: " << counter << ", ";
}

int main() {
	srand(time(NULL));

	//zmienne do pomiaru czasu
	clock_t start, stop;
	long double czas;

	//tablica losowych elementow
	int n = 100000;
	cout << "Rozmiar tablicy: " << n << endl;
	int* tab = new int[n];

	//wczytanie liczb (wartosci od 0 do 1000)
	for (int i = 0; i < n; i++) {
		tab[i] = rand() % 1001;
	}

	//tablica uzywana do sortowania
	int* tab_posortowana = new int[n];
	for (int i = 0; i < n; i++) {
		tab_posortowana[i] = tab[i];
	}

	//SORTOWANIE BABELKOWE
	cout << "\nSortowanie babelkowe:\t ";
	start = clock();
	sortowanieBabelkowe(tab_posortowana, n);
	stop = clock();
	czas = (long double)(stop - start) / CLOCKS_PER_SEC;
	cout << "\tczas: " << czas << " s\n";
	
	//przywrocenie wartosci nieposortowanych do tablicy
	for (int i = 0; i < n; i++) {
		tab_posortowana[i] = tab[i];
	}

	//SORTOWANIE PRZEZ WSTAWIANIE
	cout << "Sortowanie przez wstawianie: ";
	start = clock();
	sortowaniePrzezWstawianie(tab_posortowana, n);
	stop = clock();
	czas = (long double)(stop - start) / CLOCKS_PER_SEC;
	cout << "\tczas: " << czas << " s\n";

	//przywrocenie wartosci nieposortowanych do tablicy
	for (int i = 0; i < n; i++) {
		tab_posortowana[i] = tab[i];
	}

	//SORTOWANIE PRZEZ SELEKCJE
	cout << "Sortowanie przez selekcje: ";
	start = clock();
	sortowaniePrzezSelekcje(tab_posortowana, n);
	stop = clock();
	czas = (long double)(stop - start) / CLOCKS_PER_SEC;
	cout << "\tczas: " << czas << " s\n";
	
	//przywrocenie wartosci nieposortowanych do tablicy
	for (int i = 0; i < n; i++) {
		tab_posortowana[i] = tab[i];
	}

	//SORTOWANIE GRZEBIENIOWE
	cout << "Sortowanie grzebieniowe: ";
	start = clock();
	sortowanieGrzebieniowe(tab_posortowana, n);
	stop = clock();
	czas = (long double)(stop - start) / CLOCKS_PER_SEC;
	cout << "\tczas: " << czas << " s\n";

	//przywrocenie wartosci nieposortowanych do tablicy
	for (int i = 0; i < n; i++) {
		tab_posortowana[i] = tab[i];
	}

	//SORTOWANIE METODA SHELLA
	cout << "Sortowanie metoda shella: ";
	start = clock();
	sortowanieShella(tab_posortowana, n);
	stop = clock();
	czas = (long double)(stop - start) / CLOCKS_PER_SEC;
	cout << "\tczas: " << czas << " s\n";


	return 0;
}