#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "BSTNode.hpp"

using namespace std;
using namespace testing;

TEST(BST_NODE_TESTS, TEST_SUCCESSOR) {
    BSTNode<int> node8(8);

    ASSERT_EQ(node8.left, nullptr);
    ASSERT_EQ(node8.right, nullptr);
    ASSERT_EQ(node8.parent, nullptr);

    BSTNode<int>* node3 = new BSTNode<int>(3);
    BSTNode<int>* node11 = new BSTNode<int>(11);
    BSTNode<int>* node10 = new BSTNode<int>(10);
    BSTNode<int>* node9 = new BSTNode<int>(9);

    node8.left = node3;
    node3->parent = &node8;

    node8.right = node11;
    node11->parent = &node8;

    node11->left = node10;
    node10->parent = node11;

    node10->left = node9;
    node9->parent = node10;

    ASSERT_EQ(node3->successor()->getData(), 8);
    ASSERT_EQ(node8.successor()->getData(), 9);
    ASSERT_EQ(node11->successor(), nullptr);
}