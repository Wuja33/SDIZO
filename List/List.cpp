#include <cstdio>
#include "List.h"

List::List() : front(nullptr), tail(nullptr), size(0)
{
}

List::~List() {
    ListElement* help;
    while (front)               //dop�ki istnieje wska�nik na pocz�towy element, wykonuj p�tle
    {
        help = front->next;     //zmienna pomocnicza do przechowywania wska�nika na nast�pny element
        delete front;           //usuwanie frontu
        front = help;           //zamiana nast�pnego elementu na frontowy
    }
}

void List::pushFront(int value) {
    timer.run();

    ListElement* help = new ListElement(front, nullptr,value);

    if (front) //je�li istnieje pocz�tkowy element
        front->back = help;

    front = help;  //przypisz element na sam pocz�tek

    if (!tail)  //je�li jest to jedyny element w li�cie, ustaw koniec
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
        if (!oldElement)    //je�li znaleziony element na danym indeksie to null, zako�cz funkcje
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

    if (tail)  //je�li istnieje ostatni element, to ustaw jako koniec
        tail->next = help;

    tail = help;   //przypisz warto�� na sam koniec listy

    if (!front) //je�li nie istnieje pocz�tkowy element, to ustaw jako pocz�tek
        front = help;


    size++;
    timer.stop();
}

bool List::popFirst() {
    timer.run();
    if (front)                      //je�li istnieje pocz�tek
    {
        front = front->next;        //zamie� 2 element na pocz�tek listy

        if (!front)                 //je�li 2 element nie istnieje
            tail = nullptr;         //to ustaw koniec listy na nullptr
        else
            front->back = nullptr;  //je�li istnieje, to ustaw null na poprzednika

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
        if (!deletedElement)    //je�li znaleziony element na danym indeksie to null, zako�cz funkcje
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

    if (tail)                       //je�li istnieje koniec
    {
        tail = tail->back;          //zamie� przedostatni element na koniec listy

        if (!tail)                  //je�li przedostatni element nie istnieje
            front = nullptr;        //to ustaw pocz�tek listy na nullptr
        else
            tail->next = nullptr;  //je�li istnieje, to ustaw null na nast�pniku

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

    while (elementToSearched != nullptr)        //wykonuj dop�ki wska�nik jest r�ny od null (do ko�ca listy)
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
    return -1;  //nie uda�o si� odnale�c
}

ListElement *List::findElement(int index) {
    if (index < size && index >= 0)          //je�li istnieje lista
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

