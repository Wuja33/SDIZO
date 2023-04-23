#include "ListMenu.h"
#include "../Tools/FileClass.h"
#include "List.h"
#include <iostream>
#include <fstream>

using namespace std;

void ListMenu::showMenuOptionListA()
{
    Generator gen;
    int repeats = 0;
    int dataCount = 0;
    int dataHelp = 0;

    double timeAddFirst = 0;
    double timeAddIn = 0;
    double timeAddLast = 0;
    double timeDeleteFirst = 0;
    double timeDeleteIn = 0;
    double timeDeleteLast = 0;
    double timeSearch = 0;

    fstream file;
    file.open("../Results/ListResults.txt",ios::out|ios::in);
    if (file.fail())
    {
        cout << "ERROR - FILE OPEN TO OUT ";
        return;
    }

    cout << "Podaj ilosc powtorzen na kazda ilosc danych: ";
    cin >> repeats;
    cout << "Podaj ilosc kategorii danych: ";
    cin >> dataCount;

    int* data = new int [dataCount];

    for (int i = 0; i < dataCount; ++i) {
        cout << i+1 << ": ";
        cin >> dataHelp;
        data[i] = dataHelp;
    }

    /*
     * FORMATOWANIE PLIKU
     * rozmiar danych;liczba powtórzeñ;czas (addFirst);czas (addIn);czas (addLast);czas (deleteFirst);czas (deleteIn);czas (deleteLast);czas (search)
     */
    for (int i = 0; i < dataCount; ++i) {           //liczba kategorii
        file << data[i] << ";" << repeats << ";";
        for (int k = 0; k < repeats; ++k) {         //liczba powtórzeñ
            List* list = new List();
            for (int j = 0; j < data[i]; ++j) {
                list->pushTail(gen.getNumber());    //tworzenie listy
            }
            for (int j = 0; j < 7; ++j) {           //liczba operacji
                switch (j) {
                    case 0:
                        list->pushFront(gen.getNumber());
                        timeAddFirst += list->getTimer().getTimeMs();
                        break;
                    case 1:
                        list->pushIn(gen.getNumber(), gen.getNumber(0, data[i] - 1));
                        timeAddIn += list->getTimer().getTimeMs();
                        break;
                    case 2:
                        list->pushTail(gen.getNumber());
                        timeAddLast += list->getTimer().getTimeMs();
                        break;
                    case 3:
                        list->popFirst();
                        timeDeleteFirst += list->getTimer().getTimeMs();
                        break;
                    case 4:
                        list->popIn(gen.getNumber(0, data[i] - 1));
                        timeDeleteIn += list->getTimer().getTimeMs();
                        break;
                    case 5:
                        list->popLast();
                        timeDeleteLast += list->getTimer().getTimeMs();
                        break;
                    case 6:
                        list->search(gen.getNumber());
                        timeSearch += list->getTimer().getTimeMs();
                        break;
                }
            }
            delete list;
        }
        file << timeAddFirst/repeats << ";" << timeAddIn/repeats << ";" << timeDeleteFirst/repeats << ";" << timeDeleteFirst/repeats << ";" << timeDeleteIn/repeats << ";" << timeDeleteLast/repeats << ";" << timeSearch/repeats << endl;
        timeAddFirst = 0;
        timeAddIn = 0;
        timeAddLast = 0;
        timeDeleteFirst = 0;
        timeDeleteIn = 0;
        timeDeleteLast = 0;
        timeSearch = 0;
        cout << endl << data[i] << " | FINISHED |" << endl;
    }
    file.close();
}

void ListMenu::showMenuOptionListS()
{
    List* list = new List();
    int chooseOption = 0;
    int chooseNumber = 0;
    do
    {
        cout << "1. Wczytaj liste z pliku\n";
        cout << "2. Dodaj element na sam poczatek\n";
        cout << "3. Dodaj element w srodku listy\n";
        cout << "4. Dodaj element na koniec listy\n";
        cout << "5. Usun poczatkowy element\n";
        cout << "6. Usun element w srodku listy\n";
        cout << "7. Usun ostatni element listy\n";
        cout << "8. Wyszukaj element w liscie\n";
        cout << "9. Wyswietl liste\n";
        cout << "0. Wroc\n";
        cout << "Wybierz opcje: ";
        int index;
        cin >> chooseOption; //wybrana opcje

        switch (chooseOption)
        {
            case 1:
                cout << "Pobieranie danych z pliku tekstowego. Podaj nazwe pliku: ";
                {
                    string filename;
                    cin >> filename;
                    List* newList;
                    newList = FileClass::listFromFile(filename);
                    if (newList)    //jeœli jest nowa lista, usuñ star¹
                    {
                        delete list;
                        list = newList;
                    }
                    list->print();
                }
                break;
            case 2:	//DODAWANIE NA POCZ¥TEK
                cout << endl << "Dodawanie elementu na sam poczatek.\n" << "Podaj element: ";
                cin >> chooseNumber;
                list->pushFront(chooseNumber);
                cout << "Dodano poczatkowy element!\n";
                list->getTimer().printResult();
                list->print();
                break;
            case 3: //DODAWANIE W ŒRODKU
                cout << "Dodawanie elementu w srodku tablicy.\n" << "Podaj element: ";
                cin >> chooseNumber;
                cout << "Podaj index: ";
                cin >> index;
                if (list->pushIn(chooseNumber, index))
                {
                    cout << "Dodano element!\n";
                    list->getTimer().printResult();
                    list->print();
                }
                else
                    cout << "Blad! Podano zly index lub lista jest nie istnieje." << endl;
                break;
            case 4:	//DODAWANIE NA KONIEC
                cout << "Dodawanie elementu na sam koniec.\n" << "Podaj element: ";
                cin >> chooseNumber;
                list->pushTail(chooseNumber);
                cout << "Dodano element!\n";
                list->getTimer().printResult();
                list->print();
                break;
            case 5:	//USUWANIE PIERWSZEGO ELEMENTU
                if (list->popFirst())
                {
                    cout << "Usunieto poczatkowy element!\n";
                    list->getTimer().printResult();
                    list->print();
                }
                else
                    cout << "Error" << endl;
                break;
            case 6:	//USUWANIE ELEMENTU W ŒRODKU
                cout << "Usuwanie elementu w srodku.\n" << "Podaj index: ";
                cin >> index;
                if (list->popIn(index))
                {
                    cout << "Usunieto element na pozycji:" << index << " !\n";
                    list->getTimer().printResult();
                    list->print();
                }
                else
                    cout << "Error" << endl;
                break;
            case 7:
                if (list->popLast())
                {
                    cout << "Usunieto ostatni element!\n";
                    list->getTimer().printResult();
                    list->print();
                }
                else
                    cout << "Error" << endl;
                break;
            case 8:
                cout << "Szukanie elementu w liscie.\n" << "Podaj element: ";
                cin >> chooseNumber;
                {
                    int i_help = list->search(chooseNumber);
                    list->getTimer().printResult();
                    if (i_help != -1)
                        cout << "Znaleziono element: " << chooseNumber << " na pozycji : " << i_help << " \n";
                    else
                        cout << "Nie znaleziono takiego elementu w tablicy!" << endl;
                }
                break;
            case 9:
                list->print();
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
    delete list;
}
