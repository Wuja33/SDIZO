//
// Created by Dawid on 21.04.2023.
//

#ifndef SDIZO_NODE_H
#define SDIZO_NODE_H


class Node {
public:
    int key;
    bool isRed;     // 1 - RED  0 - BLACK     DEFAULT -> RED

    Node* parent;
    Node* left;
    Node* right;

    Node(int key);
    Node(int key,Node* parent,Node* left, Node* right);
    Node();

    Node* getGrandFather ();
    Node* getUncle ();
};


#endif //SDIZO_NODE_H
