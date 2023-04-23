#ifndef SDIZO_HEAP_H
#define SDIZO_HEAP_H


#include "../Tools/Timer.h"

class Heap {
    Timer timer;
    int* wsk;
    int size;

public:
    Heap();
    ~Heap();
    void push(int);
    bool pop();
    void heapifyBottom();
    void heapifyTop();
    void print();

    int search(int i);
    Timer getTimer();
    void createHeapTest(unsigned dataSize);
};


#endif //SDIZO_HEAP_H
