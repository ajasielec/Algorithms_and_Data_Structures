#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <iostream>

using namespace std;

#ifdef __cplusplus
int max(int value1, int value2);
int max(int value1, int value2)
{
	return ((value1 > value2) ? value1 : value2);
}
#endif

void main(void)
{
	char wzorzec[100];
	char tekst[2000];
	int m, n, i, j, t;
	int P[100];//maksymalna dlugosc wzorca to 100 symboli
	
	cout << "Podaj tekst\n";
	cin >> tekst;
	
	cout << "Podaj wzorzec\n";
	cin >> wzorzec;
	
	n = strlen(tekst);
	m = strlen(wzorzec);
	printf("Indeksy poczatku wzorca w tekscie\n");

	//obliczenie tablicy P
	P[0] = 0; P[1] = 0; t = 0;
	for (j = 2; j <= m; j++)
	{
		while ((t > 0) && (wzorzec[t] != wzorzec[j - 1])) t = P[t];
		if (wzorzec[t] == wzorzec[j - 1]) t++;
		P[j] = t;
	}

	//algorytm KMP
	i = 1; j = 0;
	while (i <= n - m + 1)
	{
		j = P[j];
		while ((j < m) && (wzorzec[j] == tekst[i + j - 1])) j++;
		if (j == m) printf("%d\n", i);
		i = i + max(1, j - P[j]);
	}
	getch();
	return;
}