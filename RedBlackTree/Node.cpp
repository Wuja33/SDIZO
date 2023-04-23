#include "Node.h"
Node::Node(int key): key(key), parent(nullptr), left(nullptr), right(nullptr), isRed(true)
{ }
Node::Node(int key,Node* parent,Node* left, Node* right): key(key), parent(parent), left(left), right(right), isRed(true)
{}
Node *Node::getGrandFather() {
    return parent->parent;
}

Node *Node::getUncle() {
    if (parent->parent->left == parent)
        return parent->parent->right;
    else
        return parent->parent->left;
}

Node::Node():key(-1), parent(nullptr), left(nullptr), right(nullptr), isRed(false)
{}
