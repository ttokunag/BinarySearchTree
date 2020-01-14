#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "BSTIterator.hpp"
#include "BSTNode.hpp"

using namespace std;
using namespace testing;

TEST(BST_ITERATOR_TEST, TEST_ITERATOR_INCREMENT) {
    BSTNode<int> node(3);
    BSTNode<int> node9(9);

    node.right = &node9;
    node9.parent = &node;

    BSTIterator<int> iter(&node);

    ASSERT_NE(iter, nullptr);
    ASSERT_EQ(*iter, 3);

    iter++;

    ASSERT_NE(iter, nullptr);
    ASSERT_EQ(*iter, 9);
}

TEST(BST_ITERATOR_TEST, TEST_ITERATOR_EQUALITY) {
    BSTNode<int> node(3);
    BSTNode<int> node9(9);

    node.right = &node9;
    node9.parent = &node;

    BSTIterator<int> iter(&node);
    BSTIterator<int> other(&node9);

    ASSERT_EQ(iter != (other), true);

    iter++;

    ASSERT_EQ(iter == (other), true);
}