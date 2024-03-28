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

//lista - implementacja wskażnikowa
struct NODE {
  President val; //wskaznik na pierwszy element
  NODE* next;
} *head = NULL;


//wstawianie na początek listy
void insertHead(NODE*& head, President x) {
  NODE* tmp = new NODE;
  tmp->val = x;
  tmp->next = head;
  head = tmp;
}

//wstawianie na koniec listy
/*void l_push_back(NODE* x, Prezydent p) {
  NODE* tmp = new NODE;
  tmp->first = &p;
  tmp->next = x->next;
  x->next = tmp;
}*/

/*
  1. Napisz funkcję, która zwróci wszystkich prezydentów 
  o najkrótszym okresie przy władzy,
*/
void TheShortestPeriod(NODE* head) {
  NODE* tmp = head;
  President p;
  int min = 100;
  int period = 0;
  //cout << p.start_date;

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
      cout << p.name << " " << p.surname << endl;
    }
    tmp = tmp->next;
  }
}

/* 
  2.Napisz fukcję, która zwróci wszystkich pre zydentów
  należących do danej partii.
*/
void WhoBelongs(NODE* head, string party) {
  NODE* tmp = head;
  President p;

  while (tmp != nullptr) {
    p = tmp->val;

    if (party==p.party) {
      cout << p.name << " " << p.surname << endl;
    }
    tmp = tmp->next;
  }
}

/*
  3. Napisz funkcję, która zwróci prezydenta 
  rządzącego w podanym roku
*/
void WhoRuledIn(NODE* head, int year) {
  NODE* tmp = head;
  President p;

  while (tmp != nullptr) {
    p = tmp->val;

    if (year >= p.start_date && year <= p.end_date) {
      cout << p.name << " " << p.surname << endl;
    }
    tmp = tmp->next;
  }
}

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

      //wstawiam obiekt na początek listy
      insertHead(head, p);
      //head w trakcie implementacji
      //cout << "head: " << head->val.name << endl;
    }
    myfile.close();

  }
  else cout << "Unable to open file";

  //head po implementacji
  //cout << "head po impl: " << head->val.name << endl;
  //działa!!


  //najkrotszy okres przy wladzy:
  //TheShortestPeriod(head);
}



int main() {

  loadData("D:/dokumenty/Studia/Semestr 3/Algorytmy i struktury danych/lab1/lista.txt");

  //1.
  TheShortestPeriod(head);

  //2.
  string party;
  cout << "\n2. Podaj nazwe partii: ";
  cin >> party;
  cout << "Prezydenci nalezacy do partii " << party << ":\n";
  WhoBelongs(head, party);

  //3.
  int year;
  cout << "\n3. Podaj rok: ";
  cin >> year;
  cout << "W " << year << " roku rzadzil:\n";
  WhoRuledIn(head, year);



  return 0;
}