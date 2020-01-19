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
     * Constructor which copies a given BST after
     * balancing it out.
     *
     * @param BST<Data>: a BST to be cloned
     */
    BST(const BST<Data>& bst) : root(0), isize(0), iheight(-1) {
        vector<Data> inorder = bst.inorder();
        root = buildSubtree(inorder, 0, inorder.size() - 1, 0);
    }

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
     * Find a node with a given data, and return an iterator which
     * points to the node.
     *
     * @param const Data&: a data that this method looks for.
     */
    iterator find(const Data& item) const {
        return findHelper(item, root);
        // findHelper description is right below this function
    }

    /** TODO */
    bool deleteNode(const Data& item) {
        // finds a node with a given data. findNode is implemeted below this
        // function
        BSTNode<Data>* node = findNode(item, root);

        // No nodes contain a given data, so return false
        if (node == nullptr) {
            return false;
        }

        // A node to delete has no child
        if (node->left == nullptr && node->right == nullptr) {
            deleteNodeWithNoChild(node);  // a private helper function
        }
        // A node to delete has two children
        else if (node->left != nullptr && node->right != nullptr) {
            deleteNodeWithTwoChildren(node);  // a private helper function
        }
        // A node to delete has either a left or right child
        else {
            BSTNode<Data>* child = (node->left) ? node->left : node->right;

            deleteNodeWithOneChild(node, child);  // a private helper function
        }

        return true;
    }

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
    /*
     * Description:
     * Returns a reference of a "smallest" node in this BST.
     *
     * @param BSTNode<Data>*: a reference of a current node
     */
    static BSTNode<Data>* first(BSTNode<Data>* root) {
        // return the root pointer if a BST has at most one node
        if (root == nullptr || root->left == nullptr) {
            return root;
        }

        BSTNode<Data>* first = root;
        // keep iterating until hitting the leftmost node
        while (first->left != nullptr) {
            first = first->left;
        }

        return first;
    }

    /*
     * Description:
     * A helper function for a destructor. This keeps
     * freeing pointers related to a given node.
     *
     * @param BSTNode<Data>*: a pointer to a node to be freed
     */
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

        // Delete the left and right frist
        deleteAll(n->left);
        deleteAll(n->right);

        delete n->left;
        delete n->right;
        // we don't free n->parent and itself because it causes
        // double free error
    }

    /*
     * Description:
     * A helper function for a balanced BST constructor. By taking a
     * median value of a vector as a new node, a new BST keep being
     * balanced.
     *
     * @param vector<Data>: a vector which is sorted in incremental order
     * @param int start: an index of the first element of a vector
     * @param int end: an index of the last element of a vector
     * @param int depth: the depth to insert a new node
     */
    BSTNode<Data>* buildSubtree(vector<Data>& data, int start, int end,
                                int depth) {
        if (start > end) {
            return nullptr;
        }

        // increment the size at each time adding a new node
        isize += 1;

        int medianIndex = (start + end) / 2;
        // if a subtree contains even number of nodes,
        // a larger median value is chosen
        if ((end - start + 1) % 2 != 1) {
            medianIndex += 1;
        }

        BSTNode<Data>* newRoot = new BSTNode<Data>(data[medianIndex]);

        newRoot->left = buildSubtree(data, start, medianIndex - 1, depth + 1);
        newRoot->right = buildSubtree(data, medianIndex + 1, end, depth + 1);

        // set a parent of a left and right child if exists
        if (newRoot->left != nullptr) {
            newRoot->left->parent = newRoot;
        }
        if (newRoot->right != nullptr) {
            newRoot->right->parent = newRoot;
        }

        // updates the height of a bst if necessary
        iheight = (depth > iheight) ? depth : iheight;

        return newRoot;
    }

    // Add more helper functions below

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

    BSTNode<Data>* findNode(const Data& item, BSTNode<Data>* node) {
        if (node == nullptr) {
            return nullptr;
        } else if (node->getData() == item) {
            return node;
        }

        if (item < node->getData()) {
            return findNode(item, node->left);
        } else {
            return findNode(item, node->right);
        }
    }

    void deleteNodeWithNoChild(BSTNode<Data>* node) {
        if (node == root) {
            root = nullptr;
        } else if (node->parent->left == node) {
            node->parent->left = nullptr;
            node->parent = nullptr;
        } else {
            node->parent->right = nullptr;
            node->parent = nullptr;
        }
        delete node;
    }

    void deleteNodeWithOneChild(BSTNode<Data>* node, BSTNode<Data>* child) {
        if (node == root) {
            root = child;
            root->parent = nullptr;
        } else if (node->parent->left == node) {
            node->parent->left = child;
            child->parent = node->parent;
        } else {
            node->parent->right = child;
            child->parent = node->parent;
        }

        delete node;
    }

    void deleteNodeWithTwoChildren(BSTNode<Data>* node) {
        BSTNode<Data>* successor = node->successor();

        Data successorVal = successor->getData();

        deleteNode(successorVal);

        node->setData(successorVal);
    }

    /*
     * Description:
     * A helper function for inorder(). Recursively calls itself in the
     * order of left, current, and right.
     *
     * @param vector<Data>*: a reference of a vector to return
     * @param BSTNode<Data>*: a reference of a current node
     */
    void inorderHelper(vector<Data>* resultPtr, BSTNode<Data>* node) const {
        if (node == nullptr) {
            return;
        }

        /* Inorder traversal:
            left => parent => right */

        inorderHelper(resultPtr, node->left);
        // push a current node Data to a vector
        resultPtr->push_back(node->getData());

        inorderHelper(resultPtr, node->right);
    }
};

#endif  // BST_HPP
