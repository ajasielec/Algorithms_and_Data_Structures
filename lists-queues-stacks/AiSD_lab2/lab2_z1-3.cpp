//Anna Jasielec
//lab 2
//zadania 1, 2, 3 - stosy

#include <iostream>
#include <cstdlib>
using namespace std;

#define MAX 1000 //max size for stack

//STOS, IMPLEMENTACJA WSKAZNIKOWA (do zadan 1, 2)
struct StackNode {
    int data;
    StackNode* next;
}*root=NULL;

StackNode* newNode(int data) {
    StackNode* tmp = new StackNode();
    tmp->data = data;
    tmp->next = NULL;
    return tmp;
}

//funkcje do obsługi stosu
//funkcja sprawdzajaca czy stos jest pusty
bool isEmpty(StackNode* root) {
    return !root;
}

//funkcja odkladajaca element na stos
void push(StackNode** root, int new_data) {
    StackNode* tmp = newNode(new_data);
    tmp->next = *root;
    *root = tmp;
    //cout << new_data << endl;
}

//funkcja zdejmujaca element ze stosu
int pop(StackNode** root) {
    if (isEmpty(*root))
        return -1;
    StackNode* tmp = *root;
    *root = (*root)->next;
    int popped = tmp->data;
    delete tmp;

    return popped;
}

//funkcja zwracajaca wierzcholek stosu
int peek(StackNode* root) {
    if (isEmpty(root))
        return -1;
    return root->data;
}

//funkcja wyswietlajaca stos
void displayStack(StackNode* root) {
    StackNode* tmp = root;
    while (tmp != nullptr) {
        cout << tmp->data << endl;
        tmp = tmp->next;
    }
}


//STOS, IMPLEMENTACJA TABLICOWA (do zadania 3)
struct Stack
{
    int top;
    int myStack[MAX]; //stack array

    //konstruktor stosu
    Stack() { top = -1; }

    //metoda odkladajaca element na stos
    bool push(int x) {
        if (top >= (MAX - 1)) {
            cout << "Stack overflow!";
            return false;
        }
        else {
            myStack[++top] = x;
            //cout << x << endl;
            return true;
        }
    }

    //metoda zdejmujaca element ze stosu
    int pop() {
        if (top < 0) {
            cout << "Stack underflow!";
            return 0;
        }
        else {
            int item = myStack[top--];
            return item;
        }
    }

    //metoda sprawdzajaca czy stos jest pusty
    bool isEmpty() {
        return (top < 0);
    }

    //metoda wyswietlajaca zawartosc stosu
    void display() {
        for (int i = 0; i <= top; i++) {
            cout << "[" << top - i + 1 << "] - " << myStack[i] << endl;
       }
    }
};

//=================ZADANIA=======================//
/*
    1. Funkcja StosL z ciągu liczb o długości M wybiera i
        odkłada na stos wszystkie te liczby, które są
        wielokrotnością liczby I
*/
StackNode* StosL(int tab[], int M, int I) {
    //tworze stos
    StackNode* root = nullptr;

    //dla liczb podzielnych przez I, push na stos
    for (int i = 0; i < M; i++) {
        if (tab[i] % I == 0) {
            push(&root, tab[i]);
        }
    }
    return(root);
}

/*=============================================
    2. Obracanie wartości stosu
*/
//a) za pomocą drugiego stosu
StackNode* ReverseA(StackNode* root) {
    StackNode* newRoot = nullptr;
    while (!isEmpty(root)) {
        push(&newRoot, pop(&root));
    }
    return(newRoot);
}

//b) za pomocą rekurencji
void insertAtBottom(StackNode** root, int x) {
    if (isEmpty(*root)) {
        push(root, x);
    }
    else {
        int top = pop(root);
        insertAtBottom(root, x);
        push(root, top);
    }
}

StackNode* ReverseB(StackNode** root) {
    if (!isEmpty(*root)) {
        int top = pop(root);
        ReverseB(root);
        insertAtBottom(root, top);
    }
    return (*root);
}

/*=================================================
    3. Funkcja usuwająca n-ty element, implementacja tablicowa stosu
*/
int remove(Stack* s, int n) {
    int top = s->top + 1;
    int usuniety = s->myStack[top - n];
    
    //zamiana elementów od n-tej pozycji do wierzchołka
    for (int i = 0; i < n - 1; i++) {
        s->myStack[top - n + i] = s->myStack[top - n + i + 1];
    }
    
    //zmiejszenie wartości wierzchołka
    s->top--;

    return usuniety;
}


int main() {

    /*
        ZADANIE 1.
    */
    int M = 4; //długość ciągu liczb
    int* tab = new int[M]; //tablica, w której będą umieszczane liczby
    int liczba = 0;
    int I = 5; //dla niej bedzie sprawdzana wielokrotnosc

    //podanie długości ciągu liczb
    cout << "Podaj dlugosc ciagu liczb: ";
    cin >> M;

    //umieszczenie liczb do tablicy
    cout << "Podaj ciag liczb o dlugosci " << M << endl;
    for (int i = 0; i < M; i++) {
        cin >> liczba;
        tab[i] = liczba;
    }

    //podanie liczby, dla której będie sprawdzana wielokrotnosc
    cout << "Podaj liczbe naturalna: ";
    cin >> I;
    cout << "\n1. Wielokrotnosci liczby " << I << ":\n";

    //tworze stos, ktory zawiera wartosci z funkcji
    StackNode* root = StosL(tab, M, I);
    //wyswietlam stos
    displayStack(root);


    /*
        ZADANIE 2.
    */
    //a)
    root = ReverseA(root);
    cout << "\n2.\na) Obrocenie stosu z wykorzystaniem drugiego stosu:\n";
    displayStack(root);

    //b)
    root = ReverseB(&root);
    cout << "b) Obrocenie stosu z wykorzystaniem rekurencji:\n";
    displayStack(root);

    /*
        ZADANIE 3.
    */
    //stworzenie stosu (implementacja tablicowa) i ułożenie na stos elementów
    Stack stack;
    for (int i = 0; i < 7; i++) {
        stack.push((i + 1) * 2);
    }

    //wyświetlenie stosu oryginalnego
    cout << "\n3. Stos originalny:\n";
    stack.display();
    
    //wprowadzenie w konsoli pozycji, z której ma być usunięty element
    int n = 2;
    cout << "\nPodaj nr. pozycji, z ktorej chcesz usunac element: ";
    cin >> n;

    //stworzenie nowego stosu, wywołanie funkcji, usuwającej element z pozycji n i zwracającej ten element
    Stack stos_usunietych;
    stos_usunietych.push(remove(&stack, n));


    //wyświetlenie stosu po usunięty elementu
    cout << "\nStos po usunieciu pozycji " <<n<<":\n";
    stack.display();

    //wyswietlenie stosu, w którym przechowywane są usunięte elementy
    cout << "\nStos usunietych elementow:\n";
    stos_usunietych.display();
    


     //zwolnienie pamieci
    while (!isEmpty(root)) {
        pop(&root);
    }
    delete[] tab;

    return 0;
}