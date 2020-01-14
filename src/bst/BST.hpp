/**
 * TODO: add file header
 */
#ifndef BST_HPP
#define BST_HPP
#include <iostream>
#include <queue>
#include <vector>
#include "BSTIterator.hpp"
#include "BSTNode.hpp"
using namespace std;

/**
 * TODO: add class header
 */
template <typename Data>
class BST {
  protected:
    // pointer to the root of this BST, or 0 if the BST is empty
    BSTNode<Data>* root;

    // number of Data items stored in this BST.
    unsigned int isize;

    // height of this BST.
    int iheight;

  public:
    /** Define iterator as an aliased typename for BSTIterator<Data>. */
    typedef BSTIterator<Data> iterator;

    /**
     * Default constructor.
     * Initialize an empty BST.
     */
    BST() : root(0), isize(0), iheight(-1) {}

    /** TODO */
    BST(const BST<Data>& bst) : root(0), isize(0), iheight(-1) {}

    /** TODO */
    ~BST() {}

    /** TODO */
    bool insert(const Data& item) {
        if (insertHelper(item, root, 0)) {
            isize++;
            return true;
        }

        return false;
    }

    bool insertHelper(const Data& item, BSTNode<Data>* node, int height) {
        // when root is empty
        if (node == nullptr) {
            root = new BSTNode<Data>(item);
            iheight = height;  // set iheight to zero
            return true;
        } else if (item == node->getData()) {
            return false;
        }

        // whenever going deeper, increment height by one
        height += 1;

        if (item < node->getData()) {
            if (node->left == nullptr) {
                node->left = new BSTNode<Data>(item);
                node->left->parent = node;  // set a new parent this node
                // update iheight if the bst grows deeper
                iheight = (height > iheight) ? height : iheight;
                return true;
            }
            return insertHelper(item, node->left, height);
        } else {  // when a given item should be placed right
            if (node->right == nullptr) {
                node->right = new BSTNode<Data>(item);
                node->right->parent = node;
                iheight = (height > iheight) ? height : iheight;
                return true;
            }
            return insertHelper(item, node->right, height);
        }
    }

    /** TODO */
    iterator find(const Data& item) const { return findHelper(item, root); }

    iterator findHelper(const Data& item, BSTNode<Data>* node) const {
        if (node == nullptr) {
            ;
            return nullptr;
        } else if (node->getData() == item) {
            return BSTIterator<Data>(node);
        }

        if (item < node->getData()) {
            return findHelper(item, node->left);
        } else {
            return findHelper(item, node->right);
        }
    }

    /** TODO */
    bool deleteNode(const Data& item) { return false; }

    /** TODO */
    unsigned int size() const { return isize; }

    /** TODO */
    int height() const { return iheight; }

    /** TODO */
    bool empty() const { return root == nullptr; }

    /** TODO */
    iterator begin() const { return BSTIterator<Data>(first(root)); }

    /** Return an iterator pointing past the last item in the BST. */
    iterator end() const { return typename BST<Data>::iterator(0); }

    /** TODO */
    vector<Data> inorder() const {}

    /**
     * DO NOT CHANGE THIS METHOD
     * Prints a tree, including its structure to an
     * output stream to help with grading and debugging.
     */
    void print(ostream* out) {
        if (empty()) {
            *out << "(Empty tree)" << endl;
            return;
        }

        // Using a queue to traverse a tree is otherwise
        // known as a breadth first traversal of the tree.
        // It's useful here to show which nodes are on which
        // level.
        queue<BSTNode<Data>*> toVisit;
        toVisit.push(root);
        int nodesPerLevel = 1;
        int totalSpacing = 1 << iheight;

        for (int i = 0; i <= iheight; i++) {
            for (int j = 0; j < nodesPerLevel; j++) {
                BSTNode<Data>* curr = toVisit.front();
                toVisit.pop();
                if (curr == nullptr) {
                    *out << "X";
                    // If we have an entire missing subtree, we
                    // would like to print X's in place of all
                    // nodes because it avoids ambiguity
                    toVisit.push(nullptr);
                    toVisit.push(nullptr);
                } else {
                    *out << curr->getData();
                    toVisit.push(curr->left);
                    toVisit.push(curr->right);
                }
                for (int k = 0; k < totalSpacing / nodesPerLevel; k++) {
                    *out << "\t";
                }
            }
            *out << endl;
            nodesPerLevel *= 2;
        }
    }

  private:
    /** TODO Helper function for begin() */
    static BSTNode<Data>* first(BSTNode<Data>* root) {
        if (root->left == nullptr) {
            return root;
        }

        BSTNode<Data>* first = root;
        while (first->left != nullptr) {
            first = first->left;
        }

        return first;
    }

    /** TODO */
    static void deleteAll(BSTNode<Data>* n) {
        /* Pseudocode:
           if current node is null: return;
           recursively delete left sub-tree
           recursively delete right sub-tree
           delete current node
        */
    }

    /** TODO */
    BSTNode<Data>* buildSubtree(vector<Data>& data, int start, int end,
                                int depth) {
        return 0;
    }

    // Add more helper functions below
};

#endif  // BST_HPP
