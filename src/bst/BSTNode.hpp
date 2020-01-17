/**
 * This file implements a BSTNode data structure
 * which is used to implement a BST.
 */
#ifndef BSTNODE_HPP
#define BSTNODE_HPP
#include <iomanip>
#include <iostream>
using namespace std;

/**
 * BSTNode contains a generic datatype and references
 * for a left child, a right child, and parent node.
 */
template <typename Data>
class BSTNode {
  private:
    Data data;

  public:
    BSTNode<Data>* left;
    BSTNode<Data>* right;
    BSTNode<Data>* parent;

    /*
     * Description:
     * Initializes a BSTNode. Sets the content of a new node, and
     * sets left, right, parent to a null pointer
     *
     * @param const Data&: a data for a new node
     */
    BSTNode(const Data& d) : data(d) { left = right = parent = nullptr; }

    /** Set the value of data */
    void setData(const Data& d) { data = d; }

    /** Get the value of data */
    Data getData() { return data; }

    /*
     * Description:
     * Returns a reference of a successor node of this node.
     * A successor node is a "smallest" node "larger" than this node.
     * (Meaning of small and larger depends on Data)
     */
    BSTNode<Data>* successor() {
        // if a node has a right child, a successor is a leftmost
        // child node of the right child
        if (right != nullptr) {
            return right->leftmostChild();
        }

        // Otherwise, a successor is a first ancestor node whose left child
        // is an ancestor of this node
        BSTNode<Data>* ancestor = parent;
        BSTNode<Data>* current = this;
        while (ancestor != nullptr && current != ancestor->left) {
            ancestor = ancestor->parent;
            current = current->parent;
        }

        return ancestor;
    }

    /*
     * Description:
     * A helper function which returns a reference of
     * a leftmost child node of this node. Used in successor().
     */
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
