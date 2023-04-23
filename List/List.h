#ifndef SDIZO_LIST_H
#define SDIZO_LIST_H
#include "ListElement.h"
#include "../Tools/Timer.h"

class List {
private:
    ListElement* front;         //wskaŸnik na pocz¹tkowy element listy
    ListElement* tail;          //wskaŸnik na ostatni element listy

    Timer timer;
    int size;					//wielkoœæ listy

public:
    List();					    //konstruktor domyœlny
    ~List();					//destruktor

    void pushFront(int);		//dodaj element na pierwszej pozycji
    bool pushIn(int, int);		    //dodaj element w œrodku listy
    void pushTail(int);			//dodaj element na koñcowej pozycji
    bool popFirst();			//usuñ element na pierwszej pozycji
    bool popIn(int);			//usuñ element w œrodku listy
    bool popLast();			    //usuñ element na koñcowej pozycji
    int search(int);			//wyszukaj dany element w listy
    ListElement* findElement(int); //wyszukaj element po indexie i zwróæ go
    void print();				//wyœwietlanie listy w konsoli

    int getSize();				//zwróæ wielkoœæ listy
    Timer getTimer();
    void setSize(int);			//zwróæ wskaŸnik
};


#endif //SDIZO_LIST_H
