/**
 * About this file:
 * This file implements Binary Search Tree in C++
 * Refer to BSTNode.hpp and BSTIterator.hpp for more
 * details of the classes used here.
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
 * About BST class:
 * BST class implements Binary Search Tree data structure.
 * Accepts a generic datatype Data, and allows us to use general
 * BST methods such as insert, find, remove, etc.
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

    /*
     * Default constructor.
     * Initialize an empty BST.
     */
    BST() : root(0), isize(0), iheight(-1) {}

    /*
     * description:
     * Constructor which clones a given BST
     *
     * @param: const BST<Data>&
     */
    BST(const BST<Data>& bst) : root(0), isize(0), iheight(-1) {}

    /*
     * description:
     * Destructor of this class. Free every pointer included in
     * this BST and a root node
     *
     * No parameter is needed
     */
    ~BST() {
        deleteAll(root);
        delete root;
    }

    /*
     * description:
     * Inserts a new node with a given item to a BST.
     * Returns true if the node is successfully inserted.
     * Returns false otherwise, that is, there exists a node
     * which contains the same data as a given item
     *
     * @param const Data&: data for a new node
     */
    bool insert(const Data& item) {
        // run a helper function
        if (insertHelper(item, root, 0)) {
            // increment the size if a node is successfully inserted
            isize++;
            return true;
        }

        return false;
    }

    /*
     * Description:
     * A helper function for node insertion. Recursively calls itself
     * until finding an appropriate place to insert. This function also
     * updates the height of the BST if necessary.
     *
     * Returns true if the node is successfully inserted.
     * Returns false otherwise, that is, there exists a node
     * which contains the same data as a given item
     *
     * @param const Data&: data for a new node
     * @param BSTNode<Data>*: a node whose data we compare with a given data
     * @param int height: a distance from a root node to a current node
     */
    bool insertHelper(const Data& item, BSTNode<Data>* node, int height) {
        // when root is empty
        if (node == nullptr) {
            root = new BSTNode<Data>(item);
            iheight = height;
            return true;
        }
        // if there exists a node with the same data, we reject to insert
        else if (item == node->getData()) {
            return false;
        }

        // we go deeper, so increment height by one
        height += 1;

        if (item < node->getData()) {
            // when a data is "smaller" than a current node, and
            // it doesn't have a left child, insert a new node there
            if (node->left == nullptr) {
                node->left = new BSTNode<Data>(item);
                node->left->parent = node;
                // update iheight if a bst gets taller by this insertion
                iheight = (height > iheight) ? height : iheight;
                return true;
            }
            // proceed to left if it is not a appropriate place yet
            return insertHelper(item, node->left, height);
        } else {
            // when a data is "larger" than a current node, and
            // it doesn't have a right child, insert a new node there
            if (node->right == nullptr) {
                node->right = new BSTNode<Data>(item);
                node->right->parent = node;
                iheight = (height > iheight) ? height : iheight;
                return true;
            }
            // proceed to right if it is not a appropriate place yet
            return insertHelper(item, node->right, height);
        }
    }

    /*
     * Description:
     * Find a node with a given data, and return an iterator which
     * points to the node.
     *
     * @param const Data&: a data that this method looks for.
     */
    iterator find(const Data& item) const {
        return findHelper(item, root);
        // findHelper description is right below this function
    }

    /*
     * Description:
     * A helper function for find operation. Recursive calls itself until
     * finding a node with a given data.
     *
     * @param const Data&: a data that this method looks for
     * @param BSTNode<Data>*: a reference of a current node
     */
    iterator findHelper(const Data& item, BSTNode<Data>* node) const {
        // if a root node isn't set yet, return null iterator
        if (node == nullptr) {
            return BSTIterator<Data>(nullptr);
        }
        // return an iterator pointing the node if it finds a node with
        // a data equals a given data
        else if (node->getData() == item) {
            return BSTIterator<Data>(node);
        }

        // if a current node doesn't have a data that we look for, it
        // proceeds either left or right depending on a current node data
        if (item < node->getData()) {
            return findHelper(item, node->left);
        } else {
            return findHelper(item, node->right);
        }
    }

    /** TODO */
    bool deleteNode(const Data& item) { return false; }

    /*
     * Description:
     * Getter function which returns the size of this BST
     */
    unsigned int size() const { return isize; }

    /*
     * Description:
     * Getter function which returns the height of this BST
     */
    int height() const { return iheight; }

    /*
     * Description:
     * Returns true if this BST is empty (contains no node)
     */
    bool empty() const { return root == nullptr; }

    /*
     * Description:
     * Returns an iterator which iterates nodes in "incremental" order
     * (Meaning of "incremental" varies depending on Data)
     */
    iterator begin() const { return BSTIterator<Data>(first(root)); }

    /** Return an iterator pointing past the last item in the BST. */
    iterator end() const { return typename BST<Data>::iterator(0); }

    /*
     * Description:
     * Returns a vector of Data which sorted in "incremental" order
     * (Meaning of "incremental" varies depending on Data)
     */
    vector<Data> inorder() const {
        vector<Data> resultPtr;
        inorderHelper(&resultPtr, root);
        return resultPtr;
    }

    /**TODO */
    void inorderHelper(vector<Data>* resultPtr, BSTNode<Data>* node) const {
        if (node == nullptr) {
            return;
        }

        inorderHelper(resultPtr, node->left);
        // push a new Data to a vector
        resultPtr->push_back(node->getData());
        inorderHelper(resultPtr, node->right);
    }

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
        if (n == nullptr) {
            return;
        }

        deleteAll(n->left);
        deleteAll(n->right);

        delete n->left;
        delete n->right;
    }

    /** TODO */
    BSTNode<Data>* buildSubtree(vector<Data>& data, int start, int end,
                                int depth) {
        return 0;
    }

    // Add more helper functions below
};

#endif  // BST_HPP
