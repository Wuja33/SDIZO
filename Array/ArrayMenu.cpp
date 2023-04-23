#include "ArrayMenu.h"
#include "../Tools/FileClass.h"
#include <iostream>
#include <fstream>
using namespace std;

void ArrayMenu::showMenuOptionTableA()
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
    file.open("../Results/ArrayResults.txt",ios::out|ios::in);
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
            Array* tab = new Array();
            tab->createTableTest(data[i]);  //tworzenie tablicy
            for (int j = 0; j < 7; ++j) {           //liczba operacji
                switch (j) {
                    case 0:
                        tab->addFirst(gen.getNumber());
                        timeAddFirst += tab->getTimer().getTimeMs();
                        break;
                    case 1:
                        tab->addIn(gen.getNumber(),gen.getNumber(0,data[i]-1));
                        timeAddIn += tab->getTimer().getTimeMs();
                        break;
                    case 2:
                        tab->addLast(gen.getNumber());
                        timeAddLast += tab->getTimer().getTimeMs();
                        break;
                    case 3:
                        tab->deleteFirst();
                        timeDeleteFirst += tab->getTimer().getTimeMs();
                        break;
                    case 4:
                        tab->deleteIn(gen.getNumber(0,data[i]-1));
                        timeDeleteIn += tab->getTimer().getTimeMs();
                        break;
                    case 5:
                        tab->deleteLast();
                        timeDeleteLast += tab->getTimer().getTimeMs();
                        break;
                    case 6:
                        tab->search(gen.getNumber());
                        timeSearch += tab->getTimer().getTimeMs();
                        break;
                    }
            }
            delete tab;
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

void ArrayMenu::showMenuOptionTableS()
{
	Array* tab = new Array();
    int chooseOption = 0;
    int chooseNumber = 0;
	do
	{
		cout << "1. Wczytaj tablicy z pliku\n";
		cout << "2. Dodaj element na sam poczatek\n";
		cout << "3. Dodaj element w srodku tablicy\n";
		cout << "4. Dodaj element na koniec tablicy\n";
		cout << "5. Usun poczatkowy element\n";
		cout << "6. Usun element w srodku tablicy\n";
		cout << "7. Usun ostatni element tablicy\n";
		cout << "8. Wyszukaj element w tablicy\n";
		cout << "9. Wyswietl tablice\n";
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
                    Array* newTab;
                    newTab = FileClass::arrayFromFile(filename);
                    if (newTab)
                    {
                        delete tab;
                        tab = newTab;
                    }
                }
                break;
            case 2:	//DODAWANIE NA POCZ¥TEK
                cout << endl << "Dodawanie elementu na sam poczatek.\n" << "Podaj element: ";
                cin >> chooseNumber;
                tab->addFirst(chooseNumber);
                cout << "Dodano poczatkowy element!\n";
                tab->getTimer().printResult();
                tab->print();
                break;
            case 3: //DODAWANIE W ŒRODKU
                cout << "Dodawanie elementu w srodku tablicy.\n" << "Podaj element: ";
                cin >> chooseNumber;
                cout << "Podaj index: ";
                cin >> index;
                if(tab->addIn(chooseNumber, index))
                {
                    cout << "Dodano element!\n";
                    tab->getTimer().printResult();
                    tab->print();
                }
                else
                    cout << "ERROR!" <<endl;

                break;
            case 4:	//DODAWANIE NA KONIEC
                cout << "Dodawanie elementu na sam koniec.\n" << "Podaj element: ";
                cin >> chooseNumber;
                tab->addLast(chooseNumber);
                tab->getTimer().printResult();
                tab->print();
                break;
            case 5:	//USUWANIE PIERWSZEGO ELEMENTU
                if (tab->deleteFirst())
                {
                    cout << "Usunieto poczatkowy element!\n";
                    tab->getTimer().printResult();
                    tab->print();
                }
                else
                    cout << "Error" << endl;
                break;
            case 6:	//USUWANIE ELEMENTU W ŒRODKU
                cout << "Usuwanie elementu w srodku.\n" << "Podaj index: ";
                cin >> index;
                if (tab->deleteIn(index))
                {
                    cout << "Usunieto element na pozycji:" << index << " !\n";
                    tab->getTimer().printResult();
                    tab->print();
                }
                else
                    cout << "Error" << endl;
                break;
            case 7:
                if (tab->deleteLast())
                {
                    cout << "Usunieto ostatni element!\n";
                    tab->getTimer().printResult();
                    tab->print();
                }
                else
                    cout << "Error" << endl;
                break;
            case 8:
                cout << "Szukanie elementu w tablicy.\n" << "Podaj element: ";
                cin >> chooseNumber;
                {
                    unsigned i_help = tab->search(chooseNumber);
                    tab->getTimer().printResult();

                    if (i_help != -1)
                        cout << "Znaleziono element: " << chooseNumber << " na pozycji : " << i_help << " \n";
                    else
                        cout << "Nie znaleziono takiego elementu w tablicy!" << endl;
                }
                break;
            case 9:
                tab->print();
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
    //usuñ tablice po zakonczeniu
    delete tab;
}
