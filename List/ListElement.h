#ifndef SDIZO_LISTELEMENT_H
#define SDIZO_LISTELEMENT_H


class ListElement {
public:
    ListElement* next;  //wskaünik na nastÍpny element w liúcie
    ListElement* back;  //wskaünik na poprzedni element w liúcie
    int key;

    ListElement():next(nullptr),back(nullptr),key(-1)
    {}
    ListElement(ListElement* next, ListElement* back, int key):next(next),back(back),key(key)
    {}
};


#endif //SDIZO_LISTELEMENT_H
