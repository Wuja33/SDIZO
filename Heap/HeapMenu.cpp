#include "HeapMenu.h"
#include "Heap.h"
#include "../Tools/FileClass.h"
#include <iostream>
#include <fstream>

using namespace std;

void HeapMenu::showMenuOptionHeapA() {
    Generator gen;
    int repeats = 0;
    int dataCount = 0;
    int dataHelp = 0;

    double timeAdd = 0;
    double timeDelete = 0;
    double timeSearch = 0;

    fstream file;
    file.open("../Results/HeapResults.txt",ios::out|ios::in);
    if (file.fail())
    {
        cout << "ERROR - FILE OPEN TO OUT ";
        return;
    }

    cout << "Podaj ilosc powtorzen na kazda ilosc danych: ";
    cin >> repeats;
    cout << "Podaj ilosc kategorii danych: ";
    cin >> dataCount;

    unsigned * data = new unsigned [dataCount];

    for (int i = 0; i < dataCount; ++i) {
        cout << i+1 << ": ";
        cin >> dataHelp;
        data[i] = dataHelp;
    }

    /*
     * FORMATOWANIE PLIKU
     * rozmiar danych;liczba powtórzeñ;czas (push);czas (pop);czas (search)
     */
    for (int i = 0; i < dataCount; ++i) {           //liczba kategorii
        file << data[i] << ";" << repeats << ";";
        for (int k = 0; k < repeats; ++k) {         //liczba powtórzeñ
            Heap* heap = new Heap();
            heap->createHeapTest(data[i]);
            for (int j = 0; j < 3; ++j) {           //liczba operacji
                switch (j) {
                    case 0:
                        heap->push(gen.getNumber());
                        timeAdd += heap->getTimer().getTimeMs();
                        break;
                    case 1:
                        heap->pop();
                        timeDelete += heap->getTimer().getTimeMs();
                        break;
                    case 2:
                        heap->search(gen.getNumber());
                        timeSearch += heap->getTimer().getTimeMs();
                        break;
                }
            }
            delete heap;
        }
        file << timeAdd/repeats << ";" << timeDelete/repeats << ";" << timeSearch/repeats << endl;
        timeAdd = 0;
        timeDelete= 0;
        timeSearch = 0;
        cout << endl << data[i] << " | FINISHED |" << endl;
    }
    file.close();
}

void HeapMenu::showMenuOptionHeapS() {
    Heap* heap = new Heap();
    int chooseOption = 0;
    int chooseNumber = 0;
    do
    {
        cout << "1. Wczytaj kopiec z pliku\n";
        cout << "2. Dodaj element\n";
        cout << "3. Usun element\n";
        cout << "4. Wyszukaj element w kopcu\n";
        cout << "5. Wyswietl kopiec\n";
        cout << "0. Wroc\n";
        cout << "Wybierz opcje: ";
        cin >> chooseOption; //wybrana opcje

        switch (chooseOption)
        {
            case 1:
                cout << "Pobieranie danych z pliku tekstowego. Podaj nazwe pliku: ";
                {
                    string filename;
                    cin >> filename;
                    Heap* newHeap;
                    newHeap = FileClass::heapFromFile(filename);
                    if (newHeap)    //jeœli jest nowy kopiec, usuñ stary
                    {
                        delete heap;
                        heap = newHeap;
                    }
                    heap->print();
                }
                break;
            case 2:	//DODAWANIE NA POCZ¥TEK
                cout << endl << "Dodawanie elementu.\n" << "Podaj element: ";
                cin >> chooseNumber;
                heap->push(chooseNumber);
                cout << "Dodano element!\n";
                heap->getTimer().printResult();
                heap->print();
                break;
            case 3:	//USUWANIE KORZENIA
                if (heap->pop())
                {
                    cout << "Usunieto element!\n";
                    heap->getTimer().printResult();
                    heap->print();
                }
                else
                    cout << "Error" << endl;
                break;
            case 4:
                cout << "Szukanie elementu w kopcu.\n" << "Podaj element: ";
                cin >> chooseNumber;
                {
                    int i_help = heap->search(chooseNumber);
                    heap->getTimer().printResult();
                    if (i_help != -1)
                        cout << "Znaleziono element: " << chooseNumber << " na pozycji : " << i_help << " \n";
                    else
                        cout << "Nie znaleziono takiego elementu w kopcu!" << endl;
                }
                break;
            case 5:
                heap->print();
                break;
            case 0:
                system("cls");
                break;
            default:
                cout << endl << "Podano niepoprawna opcje!" << endl;
                break;
        }
        cout << endl << endl;
    } while (chooseOption);
    delete heap;
}
