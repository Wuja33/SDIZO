#ifndef SDIZO_LISTELEMENT_H
#define SDIZO_LISTELEMENT_H


class ListElement {
public:
    ListElement* next;  //wska�nik na nast�pny element w li�cie
    ListElement* back;  //wska�nik na poprzedni element w li�cie
    int key;

    ListElement():next(nullptr),back(nullptr),key(-1)
    {}
    ListElement(ListElement* next, ListElement* back, int key):next(next),back(back),key(key)
    {}
};


#endif //SDIZO_LISTELEMENT_H
