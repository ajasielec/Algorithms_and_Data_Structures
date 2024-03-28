#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

struct President {
    string name;
    string surname;
    string party;
    int start_date;
    int end_date;
};

// LISTY I OPERACJE NA LISTACH
//lista g³ówna- implementacja wska¿nikowa
struct NODE {
    President val; 
    NODE* next;
} *head = NULL;

//lista dodatkowa (na odpowiedzi do zadan)
struct NODE1 {
    President val; 
    NODE1* next;
} *head1 = NULL;


//wstawianie na pocz¹tek listy
void insertHead(NODE*& head, President x) {
    NODE* tmp = new NODE;
    tmp->val = x;
    tmp->next = head;
    head = tmp;
}
void insertHead(NODE1*& head1, President x) {
    NODE1* tmp = new NODE1;
    tmp->val = x;
    tmp->next = head1;
    head1 = tmp;
}

//czyszczenie listy dodatkowej
void deleteList(NODE1** head1) {
    NODE1* tmp = *head1;
    NODE1* next;
    while (tmp != nullptr) {
        next = tmp->next;
        free(tmp);
        tmp = next;
    }
    *head1 = NULL;
}

//wypisywanie listy dodatkowej
void displayList(NODE1* head1) {
    NODE1* tmp = head1;
    while (tmp != nullptr) {
        President p;
        p = tmp->val;
        cout << p.name << " " << p.surname << endl;
        tmp = tmp->next;
    }
}

//=======================================================//
//funkcja split
string* split(string s, string delimiter) {

    int pos_start = 0;
    int pos_end;
    int delim_len = delimiter.length();

    string token;
    static string buffer[10];

    int idx = 0;

    while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {

        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;

        buffer[idx] = token;
        idx++;

        //cout << idx << endl;

    }

    token = s.substr(pos_start, pos_end - pos_start);
    pos_start = pos_end + delim_len;
    buffer[idx] = token;

    //cout << buffer[3] << endl;

    return buffer;

}

//funkcja wczytujaca dane z pliku
void loadData(string path) {
    string line;
    ifstream myfile("" + path);

    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            //split the string
            string* buffer = split(line, " ");
            President p;

            //przypisuje dane polom obiektu p
            p.name = buffer[0];
            p.surname = buffer[1];
            p.start_date = atoi(buffer[2].c_str());
            p.end_date = atoi(buffer[3].c_str());
            p.party = buffer[4];

            //wstawiam obiekt na pocz¹tek listy
            insertHead(head, p);
            //sprawdzam head w trakcie implementacji
            //cout << "head: " << head->val.start_date <<"-" << head->val.end_date << endl;
        }
        myfile.close();

    }
    else cout << "Unable to open file";

    //head po implementacji
    //cout << "head po impl: " << head->val.name << endl;
}



//========================ZADANIA===============================//
/*
  1. Napisz funkcjê, która zwróci wszystkich prezydentów
  o najkrótszym okresie przy w³adzy,
*/
NODE1* TheShortestPeriod(NODE* head) {
    NODE* tmp = head;
    President p;
    int min = 100;
    int period = 0;
    NODE1* result = head1;

    //znalezienie min okresu panowania
    while (tmp != nullptr) {
        p = tmp->val;
        period = p.end_date - p.start_date;

        if (period <= min) {
            min = period;
        }
        tmp = tmp->next;
    }
    cout << "a) najkrotszy okres panowania = " << min << endl << "tyle panowali:\n";

    //wypisanie wszystkich z min okresem panowania
    tmp = head;
    while (tmp != nullptr) {
        p = tmp->val;
        period = p.end_date - p.start_date;
        if (period == min) {
            insertHead(head1, p);
        }
        tmp = tmp->next;
    }
    return result;
}

/*
  2.Napisz fukcjê, która zwróci wszystkich prezydentów
  nale¿¹cych do danej partii.
*/
NODE1* WhoBelongs(NODE* head, string party) {
    NODE* tmp = head;
    President p;
    NODE1* result = head1;

    while (tmp != nullptr) {
        p = tmp->val;

        if (party == p.party) {
            insertHead(head1, p);
        }
        tmp = tmp->next;
    }
    return result;
}

/*
  3. Napisz funkcjê, która zwróci prezydenta
  rz¹dz¹cego w podanym roku
*/
NODE1* WhoRuledIn(NODE* head, int year) {
    NODE* tmp = head;
    President p;
    NODE1* result = head1;

    while (tmp != nullptr) {
        p = tmp->val;

        if (year >= p.start_date && year <= p.end_date) {
            insertHead(head1, p);
        }
        tmp = tmp->next;
    }
    return result;
}



//=====================MAIN=========================//
int main() {

    loadData("C:/Users/Anna/source/repos/AiSD_lab1/lista.txt");

    //1.
    NODE1* z1 = TheShortestPeriod(head);
    displayList(head1);
    deleteList(&head1);
    /*if (head1 == nullptr)
        cout << "Usuniete." << endl;*/

    //2.
    string party;
    cout << "\n2. Podaj nazwe partii: ";
    cin >> party;
    cout << "Prezydenci nalezacy do partii " << party << ":\n";
    NODE1* z2 = WhoBelongs(head, party);
    displayList(head1);
    deleteList(&head1);

    //3.
    int year;
    cout << "\n3. Podaj rok: ";
    cin >> year;
    cout << "W " << year << " roku rzadzil:\n";
    NODE1* z3 = WhoRuledIn(head, year);
    displayList(head1);
    deleteList(&head1);
   

    return 0;
}