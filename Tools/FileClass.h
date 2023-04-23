#include <iostream>
#include "../Array/Array.h"
#include "../List/List.h"
#include "../Heap/Heap.h"
#include "../RedBlackTree/RedBlackTree.h"

using namespace std;
class FileClass
{

public:
    static Array* arrayFromFile(string filename);
    static List* listFromFile(string filename);
    static Heap* heapFromFile(string filename);
    static RedBlackTree* treeFromFile(string filename);
};