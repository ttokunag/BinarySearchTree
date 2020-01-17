/**
 * This file implements an iterator for a binary
 * search tree.
 */
#ifndef BSTITERATOR_HPP
#define BSTITERATOR_HPP
#include <iterator>
#include <list>
#include "BSTNode.hpp"

using namespace std;

/**
 * This overload an interator data structure.
 * This class contains a reference of a BSTNode. This iterator
 * points to a node in ascending order.
 */
template <typename Data>
class BSTIterator : public iterator<input_iterator_tag, Data> {
  private:
    BSTNode<Data>* curr;

  public:
    /**
     * Constructor that initialize the current BSTNode
     * in this BSTIterator.
     */
    BSTIterator(BSTNode<Data>* curr) : curr(curr) {}

    /** Dereference operator. */
    Data operator*() const { return curr->getData(); }

    /** Pre-increment operator. */
    BSTIterator<Data>& operator++() {
        curr = curr->successor();
        return *this;
    }

    /** Post-increment operator. */
    BSTIterator<Data> operator++(int) {
        BSTIterator before = BSTIterator(curr);
        ++(*this);
        return before;
    }

    /** Returns true if two iterators point to the same node */
    bool operator==(BSTIterator<Data> const& other) const {
        return curr == other.curr;
    }

    /** Returns true if two iterators point to different nodes */
    bool operator!=(BSTIterator<Data> const& other) const {
        return curr != other.curr;
    }
};

#endif  // BSTITERATOR_HPP
