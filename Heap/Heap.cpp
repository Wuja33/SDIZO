#include <cmath>
#include "Heap.h"
#include "../Tools/Generator.h"
#include <iostream>
using namespace std;

Heap::Heap() : wsk(nullptr), size(0)
{}

Heap::~Heap() {
    if (wsk!= nullptr)
        delete[] wsk;
}

void Heap::push(int value)
{
    timer.run();

    int* newWsk = new int[++size];      //utwórz nowy kopiec
    newWsk[size-1] = value;             //wpisz nowa wartoœæ na ostatniej pozycji

    if (wsk!= nullptr)                 //jeœli istnieje kopiec
    {
        for (int i=0; i<(size-1);i++)
        {
            newWsk[i] = wsk[i];
        }

        delete[] wsk;
    }
    wsk = newWsk;

    //przywrócenie w³asnoœci kopca po dodaniu
    heapifyBottom();

    timer.stop();
}

bool Heap::pop() {
    timer.run();

    if (size==0)
    {
        timer.stop();
        return false;
    }
    else if (size == 1)
    {
        size--;
        delete[] wsk;
        wsk = nullptr;

        timer.stop();

        return true;
    }
    else
    {
        int* newWsk = new int [size - 1];
        newWsk[0] = wsk [size - 1];         //ostatni element przenieœ na sam szczyt
        size--;
        for (int i=1 ; i<size ; i++)
        {
            newWsk[i] = wsk[i];
        }

        delete[] wsk;
        wsk = newWsk;
        heapifyTop();                       //przywróæ w³asnoœæ

        timer.stop();

        return true;
    }
}

void Heap::heapifyBottom() {
    int child = size - 1;
    int parent = (child - 1)/2;
    int help;
    while (child > 0 && wsk[parent] < wsk[child])
    {
        help = wsk[parent];
        wsk[parent] = wsk[child];
        wsk[child] = help;

        child = parent;
        parent = (child - 1)/2;
    }
}

void Heap::heapifyTop() {
    int leftChild = 1;
    int rightChild = 2;
    int max = 0;
    int parent = 0;
    int help = 0;

    do {
        max = parent;
        if (leftChild < size && wsk[leftChild] > wsk[max])      //sprawdz czy lewe dziecko jest wiêksze od rodzica
        {
            max = leftChild;
        }

        if (rightChild < size && wsk[rightChild] > wsk[max])    //sprawdz czy prawe dziecko jest wiêksze od max
        {
            max = rightChild;
        }

        if (max!=parent)
        {
            help = wsk[parent];
            wsk[parent] = wsk[max];
            wsk[max] = help;

            parent = max;
            leftChild = (2*parent) + 1;
            rightChild = (2*parent) + 2;
        } else              //jeœli nie wykryto zmiany, zakoñcz
            break;

    } while (true);
}

void Heap::print() {
    if (size > 0 && wsk != nullptr)
    {
        bool outOfBound = false;
        int first = 0;
        int last = 1;

        // Calculate the maximum number of nodes at the current heap level
        int space = pow(2, floor(log2(this->size)) + 1) - 1;

        while (!outOfBound)
        {
            // Print space before each heap level
            cout << string(space / 2 * 3, ' ');

            // Print nodes on current heap level
            for (int i = first; i < last; i++)
            {
                if (i >= this->size)
                {
                    outOfBound = true;
                    break;
                }
                cout << '[' << wsk[i] << ']' << string(space * 3, ' ');
            }
            cout << "\n\n";

            // Change indexes or last and first node on each heap level
            first = last;
            last = 2 * last + 1;

            // Change size of space between nodes
            space = space / 2;
        }
        return;
    }
    cout << "Kopiec jest pusty" << std::endl;
}

int Heap::search(int numberToSearch) {
    timer.run();
    if (size > 0)									//jeœli istnieje kopiec
    {
        for (unsigned i = 0; i < size; i++)
        {
            if (wsk[i] == numberToSearch)			//jeœli któryœ element jest równy poszukiwanemu, to zwróæ prawde
            {
                timer.stop();
                return i;
            }
        }
        timer.stop();
        return -1;
    }
    else {
        timer.stop();
        return -1;
    }
}

Timer Heap::getTimer() {
    return timer;
}

void Heap::createHeapTest(unsigned dataSize) {
    delete[] wsk;
    size = 0;

    Generator generator;
    wsk = new int [dataSize];
    for (unsigned i = 0; i < dataSize; ++i) {
        wsk[i] = generator.getNumber();
        size++;
        this->heapifyBottom();
    }
}

