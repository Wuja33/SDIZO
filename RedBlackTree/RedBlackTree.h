#ifndef SDIZO_REDBLACKTREE_H
#define SDIZO_REDBLACKTREE_H

#include <iostream>

using namespace std;
#include "Node.h"
#include "../Tools/Timer.h"

class RedBlackTree {
private:
    Timer timer;
    Node nil;
    Node* root;
    string cr, cl, cp;     // £añcuchy do znaków ramek
public:
    RedBlackTree();
    ~RedBlackTree();
    void insert (int key);
    void remove (Node* node);
    void remove (int key);

    Node* search (int key);
    Node* successor (Node* node);

    void rotateLeft (Node* node);
    void rotateRight (Node* node);

    void printRBT(string sp, string sn, Node * p);
    void print( );\
    void deleteTree(Node* node);

    Timer getTimer();
};


#endif //SDIZO_REDBLACKTREE_H
