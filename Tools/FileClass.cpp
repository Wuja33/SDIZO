#include "FileClass.h"
#include <fstream>
#include <iostream>

using namespace std;

Array* FileClass::arrayFromFile(string filename)
{
	int size;			//iloœæ danych
	fstream file;		//plik
    Array* tab = new Array();
	int* wsk = nullptr;
	int data;
	file.open(filename, ios::in);

	if (file.is_open())
	{
		file >> size;
		if (file.fail())
			cout << "File error - READ SIZE" << endl;
		else
		{
			tab->setSize(size);
			wsk = new int[size];		//stworzenie tablicy o wczytanym rozmiarze
			for (int i = 0; i < size; i++)
			{
				file >> data;
				if (file.fail())
				{
					cout << "File error - READ DATA" << endl;
					break;
				}
				else
					wsk[i] = data;
			}
		}
		file.close();
		tab->setWsk(wsk);
        return tab;
	}
	else
		cout << "File error - OPEN" << endl;

    return nullptr;
}
List* FileClass::listFromFile(string filename)
{
    int size;			//iloœæ danych
    fstream file;		//plik
    List* newList = new List();
    int data;
    file.open(filename, ios::in);

    if (file.is_open())
    {
        file >> size;
        if (file.fail())
            cout << "File error - READ SIZE" << endl;
        else
        {
            for (int i = 0; i < size; i++)
            {
                file >> data;
                if (file.fail())
                {
                    cout << "File error - READ DATA" << endl;
                    break;
                }
                else
                    newList->pushTail(data);
            }
        }
        file.close();
        return newList;
    }
    else
        cout << "File error - OPEN" << endl;

    return nullptr;
}
Heap* FileClass::heapFromFile(string filename) {
    int size;			//iloœæ danych
    fstream file;		//plik
    Heap* newHeap = new Heap();
    int data;
    file.open(filename, ios::in);

    if (file.is_open())
    {
        file >> size;
        if (file.fail())
            cout << "File error - READ SIZE" << endl;
        else
        {
            for (int i = 0; i < size; i++)
            {
                file >> data;
                if (file.fail())
                {
                    cout << "File error - READ DATA" << endl;
                    break;
                }
                else
                    newHeap->push(data);
            }
        }
        file.close();
        return newHeap;
    }
    else
        cout << "File error - OPEN" << endl;

    return nullptr;
}

RedBlackTree *FileClass::treeFromFile(string filename) {
    int size;			//iloœæ danych
    fstream file;		//plik
    RedBlackTree* tree = new RedBlackTree();
    int data;
    file.open(filename, ios::in);

    if (file.is_open())
    {
        file >> size;
        if (file.fail())
            cout << "File error - READ SIZE" << endl;
        else
        {
            for (int i = 0; i < size; i++)
            {
                file >> data;
                if (file.fail())
                {
                    cout << "File error - READ DATA" << endl;
                    break;
                }
                else
                    tree->insert(data);
            }
        }
        file.close();
        return tree;
    }
    else
        cout << "File error - OPEN" << endl;

    return nullptr;
}
