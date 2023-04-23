#ifndef SDIZO_LIST_H
#define SDIZO_LIST_H
#include "ListElement.h"
#include "../Tools/Timer.h"

class List {
private:
    ListElement* front;         //wska�nik na pocz�tkowy element listy
    ListElement* tail;          //wska�nik na ostatni element listy

    Timer timer;
    int size;					//wielko�� listy

public:
    List();					    //konstruktor domy�lny
    ~List();					//destruktor

    void pushFront(int);		//dodaj element na pierwszej pozycji
    bool pushIn(int, int);		    //dodaj element w �rodku listy
    void pushTail(int);			//dodaj element na ko�cowej pozycji
    bool popFirst();			//usu� element na pierwszej pozycji
    bool popIn(int);			//usu� element w �rodku listy
    bool popLast();			    //usu� element na ko�cowej pozycji
    int search(int);			//wyszukaj dany element w listy
    ListElement* findElement(int); //wyszukaj element po indexie i zwr�� go
    void print();				//wy�wietlanie listy w konsoli

    int getSize();				//zwr�� wielko�� listy
    Timer getTimer();
    void setSize(int);			//zwr�� wska�nik
};


#endif //SDIZO_LIST_H
