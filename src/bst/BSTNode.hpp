/**
 * TODO: add file header
 */
#ifndef BSTNODE_HPP
#define BSTNODE_HPP
#include <iomanip>
#include <iostream>
using namespace std;

/**
 * TODO: add class header
 */
template <typename Data>
class BSTNode {
  private:
    Data data;

  public:
    BSTNode<Data>* left;
    BSTNode<Data>* right;
    BSTNode<Data>* parent;

    /** TODO */
    BSTNode(const Data& d) : data(d) { left = right = parent = nullptr; }

    /** Set the value of data */
    void setData(const Data& d) { data = d; }

    /** Get the value of data */
    Data getData() { return data; }

    /** TODO */
    BSTNode<Data>* successor() {
        if (right != nullptr) {
            return right->leftmostChild();
        }

        BSTNode<Data>* ancestor = parent;
        BSTNode<Data>* current = this;
        while (ancestor != nullptr && current != ancestor->left) {
            ancestor = ancestor->parent;
            current = current->parent;
        }

        return ancestor;
    }

    BSTNode<Data>* leftmostChild() {
        // the case this node has no left child
        if (left == nullptr) {
            return this;
        }

        BSTNode<Data>* leftmost = this->left;
        // going down left until hitting a leaf
        while (leftmost->left != nullptr) {
            leftmost = leftmost->left;
        }

        return leftmost;
    }

    void addLeft(BSTNode<Data>* node) {
        right = node;
        node->parent = this;
    }

    void addRight(BSTNode<Data>* node) {
        right = node;
        node->parent = this;
    }
};

/**
 * DO NOT CHANGE THIS METHOD
 * Overload operator<< to print a BSTNode's fields to an ostream.
 */
template <typename Data>
ostream& operator<<(ostream& stm, const BSTNode<Data>& n) {
    stm << '[';
    stm << setw(10) << &n;                  // address of the BSTNode
    stm << "; p:" << setw(10) << n.parent;  // address of its parent
    stm << "; l:" << setw(10) << n.left;    // address of its left child
    stm << "; r:" << setw(10) << n.right;   // address of its right child
    stm << "; d:" << n.data;                // its data field
    stm << ']';
    return stm;
}

#endif  // BSTNODE_HPP
