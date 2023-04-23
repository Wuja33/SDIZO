#include "Menu.h"
#include "Array/ArrayMenu.h"
#include "List/ListMenu.h"
#include "Heap/HeapMenu.h"
#include "RedBlackTree/RedBlackTreeMenu.h"
#include <iostream>
using namespace std;

void Menu::showMenuStructures()
{
    int choose;
    do {
        cout << "1. Tablica dynamiczna\n";
        cout << "2. Lista dwukierunkowa\n";
        cout << "3. Kopiec binarny\n";
        cout << "4. Drzewo Czerwono-Czarne\n";
        cout << "9. TEST AUTOMATYCZNY\n";
        cout << "0. Zakoncz program\n";
        cout << "Wybierz opcje: ";

        cin >> choose; //wybrana opcja

        switch (choose)
        {
            case 1:
                ArrayMenu::showMenuOptionTableS();
                break;
            case 2:
                ListMenu::showMenuOptionListS();
                break;
            case 3:
                HeapMenu::showMenuOptionHeapS();
                break;
            case 4:
                RedBlackTreeMenu::showMenuOptionTreeS();
                break;
            case 9:
                Menu::showMenuAutomatic();
                break;
            case 0:
                break;
            default:
                cout << endl << "Podano nieprawidlowa opcje!" << endl;
                break;
        }
    } while (choose);
}

void Menu::showMenuAutomatic() {
    int choose;
    do {
        cout << "1. Tablica dynamiczna\n";
        cout << "2. Lista dwukierunkowa\n";
        cout << "3. Kopiec binarny\n";
        cout << "4. Drzewo Czerwono-Czarne\n";
        cout << "0. Zakoncz program\n";
        cout << "Wybierz opcje: ";

        cin >> choose; //wybrana opcja

        switch (choose)
        {
            case 1:
                ArrayMenu::showMenuOptionTableA();
                break;
            case 2:
                ListMenu::showMenuOptionListA();
                break;
            case 3:
                HeapMenu::showMenuOptionHeapA();
                break;
            case 4:
                RedBlackTreeMenu::showMenuOptionTreeA();
                break;
            case 0:
                break;
            default:
                cout << endl << "Podano nieprawidlowa opcje!" << endl;
                break;
        }
    } while (choose);
}

