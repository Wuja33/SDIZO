#include <cstdio>
#include "List.h"

List::List() : front(nullptr), tail(nullptr), size(0)
{
}

List::~List() {
    ListElement* help;
    while (front)               //dopóki istnieje wskaŸnik na pocz¹towy element, wykonuj pêtle
    {
        help = front->next;     //zmienna pomocnicza do przechowywania wskaŸnika na nastêpny element
        delete front;           //usuwanie frontu
        front = help;           //zamiana nastêpnego elementu na frontowy
    }
}

void List::pushFront(int value) {
    timer.run();

    ListElement* help = new ListElement(front, nullptr,value);

    if (front) //jeœli istnieje pocz¹tkowy element
        front->back = help;

    front = help;  //przypisz element na sam pocz¹tek

    if (!tail)  //jeœli jest to jedyny element w liœcie, ustaw koniec
        tail = front;

    size++;

    timer.stop();
}

bool List::pushIn(int value, int index) {
    timer.run();

    if (index==0)
    {
        timer.stop();
        pushFront(value);
    }
    else if (index == size)
    {
        timer.stop();
        pushTail(value);
    }
    else
    {
        ListElement* oldElement = findElement(index);
        if (!oldElement)    //jeœli znaleziony element na danym indeksie to null, zakoñcz funkcje
        {
            timer.stop();
            return false;
        }

        ListElement* newElement = new ListElement(oldElement,oldElement->back,value);
        oldElement->back->next = newElement;
        oldElement->back = newElement;
        size ++;
        timer.stop();
    }

    return true;
}

void List::pushTail(int value) {
    timer.run();

    ListElement* help =  new ListElement(nullptr, tail,value);

    if (tail)  //jeœli istnieje ostatni element, to ustaw jako koniec
        tail->next = help;

    tail = help;   //przypisz wartoœæ na sam koniec listy

    if (!front) //jeœli nie istnieje pocz¹tkowy element, to ustaw jako pocz¹tek
        front = help;


    size++;
    timer.stop();
}

bool List::popFirst() {
    timer.run();
    if (front)                      //jeœli istnieje pocz¹tek
    {
        front = front->next;        //zamieñ 2 element na pocz¹tek listy

        if (!front)                 //jeœli 2 element nie istnieje
            tail = nullptr;         //to ustaw koniec listy na nullptr
        else
            front->back = nullptr;  //jeœli istnieje, to ustaw null na poprzednika

        size--;
        timer.stop();
        return true;
    } else
    {
        timer.stop();
        return false;
    }

}

bool List::popIn(int index) {
    timer.run();

    if (index == 0) {
        timer.stop();
        if (!popFirst())
            return false;
    }
    else if(index == size - 1) {
        timer.stop();
        if (!popLast())
            return false;
    }
    else
    {
        ListElement* deletedElement = findElement(index);
        if (!deletedElement)    //jeœli znaleziony element na danym indeksie to null, zakoñcz funkcje
        {
            timer.stop();
            return false;
        }
        deletedElement->back->next = deletedElement->next;
        deletedElement->next->back = deletedElement->back;
        delete deletedElement;
        size--;
        timer.stop();
    }
    return true;
}

bool List::popLast() {
    timer.run();

    if (tail)                       //jeœli istnieje koniec
    {
        tail = tail->back;          //zamieñ przedostatni element na koniec listy

        if (!tail)                  //jeœli przedostatni element nie istnieje
            front = nullptr;        //to ustaw pocz¹tek listy na nullptr
        else
            tail->next = nullptr;  //jeœli istnieje, to ustaw null na nastêpniku

        size--;
        timer.stop();
        return true;
    } else
    {
        timer.stop();
        return false;
    }
}

int List::search(int value) {
    timer.run();

    int index = 0;

    ListElement* elementToSearched = front;

    while (elementToSearched != nullptr)        //wykonuj dopóki wskaŸnik jest ró¿ny od null (do koñca listy)
    {
        if(elementToSearched->key == value)
        {
            timer.stop();
            return index;
        }

        elementToSearched = elementToSearched->next;
        index++;
    }

    timer.stop();
    return -1;  //nie uda³o siê odnaleŸc
}

ListElement *List::findElement(int index) {
    if (index < size && index >= 0)          //jeœli istnieje lista
    {
        ListElement* elementToSearched = front;
        for (int i = 1; i <= index; i++) {
            elementToSearched = elementToSearched->next;    //zamieniaj tyle razy, ile wynosi index
        }
        return elementToSearched;
    }
    else
        return nullptr;
}


void List::print() {
    if (front) {
        int i = 0;
        ListElement *elementToPrint = front;
        while (elementToPrint)
        {
            printf("%4u|%-6d", i, elementToPrint->key);

            if (!((i+1) % 10))
                printf("\n");

            elementToPrint = elementToPrint->next;
            i++;
        }
    } else
        printf("PUSTA LISTA");
}

int List::getSize() {
    return size;
}
void List::setSize(int size) {
    this->size = size;
}

Timer List::getTimer() {
    return timer;
}

