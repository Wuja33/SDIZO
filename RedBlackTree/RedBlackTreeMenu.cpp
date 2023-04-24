#include "RedBlackTreeMenu.h"
#include "../Tools/FileClass.h"
#include "RedBlackTree.h"
#include <iostream>
#include <fstream>

using namespace std;

void RedBlackTreeMenu::showMenuOptionTreeA() {
    Generator gen;
    int repeats = 0;
    int dataCount = 0;
    int dataHelp = 0;

    double timeInsert = 0;
    double timeDelete = 0;
    double timeSearch = 0;

    fstream file;
    file.open("../Results/RedBlackTreeResults.txt",ios::out|ios::in);
    if (file.fail())
    {
        cout << "ERROR - FILE OPEN TO OUT ";
        return;
    }

    cout << "Podaj ilosc powtorzen na kazda ilosc danych: ";
    cin >> repeats;
    cout << "Podaj ilosc kategorii danych: ";
    cin >> dataCount;

    int * data = new int [dataCount];

    for (int i = 0; i < dataCount; ++i) {
        cout << i+1 << ": ";
        cin >> dataHelp;
        data[i] = dataHelp;
    }

    /*
     * FORMATOWANIE PLIKU
     * rozmiar danych;liczba powtórzeñ;czas (insert);czas (remove);czas (search)
     */
    for (int i = 0; i < dataCount; ++i) {           //liczba kategorii
        file << data[i] << ";" << repeats << ";";
        for (int k = 0; k < repeats; ++k) {         //liczba powtórzeñ
            RedBlackTree* tree = new RedBlackTree();
            int* tab = new int[data[i]];                //tablica do przechowywania dodanych elementów
            int valueAdd;
            for (int j = 0; j < data[i]; ++j) {
                valueAdd = gen.getNumber();
                tab[j] = valueAdd;                  //uzupe³nianie tablicy
                tree->insert(valueAdd);         //tworzenie listy
            }
            for (int j = 0; j < 3; ++j) {           //liczba operacji
                switch (j) {
                    case 0:
                        tree->insert(gen.getNumber());
                        timeInsert += tree->getTimer().getTimeMs();
                        break;
                    case 1:
                        tree->remove(tab[gen.getNumber(0,data[i])]);
                        timeDelete += tree->getTimer().getTimeMs();
                        break;
                    case 2:
                        tree->search(gen.getNumber());
                        timeSearch += tree->getTimer().getTimeMs();
                        break;
                }
            }
            delete tree;
            delete[] tab;
        }
        file << timeInsert / repeats << ";" << timeDelete / repeats << ";" << timeSearch / repeats << endl;
        timeInsert = 0;
        timeDelete= 0;
        timeSearch = 0;
        cout << endl << data[i] << " | FINISHED |" << endl;
    }
    file.close();
}

void RedBlackTreeMenu::showMenuOptionTreeS() {
    Generator gen;
    RedBlackTree* tree = new RedBlackTree();
    int chooseOption = 0;
    int chooseNumber = 0;
    do
    {
        cout << "1. Wczytaj drzewo z pliku\n";
        cout << "2. Dodaj element\n";
        cout << "3. Usun element\n";
        cout << "4. Wyszukaj element w drzewie\n";
        cout << "5. Wyswietl drzewo\n";
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
                    RedBlackTree* newTree;
                    newTree = FileClass::treeFromFile(filename);
                    if (newTree)    //jeœli jest nowy kopiec, usuñ stary
                    {
                        delete tree;
                        tree = newTree;
                    }
                    tree->print();
                }
                break;
            case 2:	//DODAWANIE
                cout << endl << "Dodawanie elementu.\n" << "Podaj element: ";
                cin >> chooseNumber;
                tree->insert(chooseNumber);
                cout << "Dodano element!\n";
                tree->getTimer().printResult();
                tree->print();
                break;
            case 3:	//USUWANIE
                int key;
                cout << "Usuwanie elementu.\n" << "Podaj klucz: ";
                cin >> key;
                {
                    Node *serachNodeToDelete = tree->search(key);
                    if (serachNodeToDelete != nullptr) {
                        tree->remove(serachNodeToDelete);
                        cout << "Usunieto element!" << "!\n";
                        tree->getTimer().printResult();
                        tree->print();
                    } else
                        cout << "Error!" << endl;
                }
                break;
            case 4:
                cout << "Szukanie elementu w kopcu.\n" << "Podaj element: ";
                cin >> chooseNumber;
                {
                    Node* nodeTosearch = tree->search(chooseNumber);
                    tree->getTimer().printResult();
                    if (nodeTosearch != nullptr)
                        cout << "Znaleziono element! " << "\n";
                    else
                        cout << "Nie znaleziono takiego elementu w kopcu!" << endl;
                }
                break;
            case 5:
                tree->print();
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
    delete tree;
}
