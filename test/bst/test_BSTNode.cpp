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
    BSTNode<int> node(3);

    BSTNode<int>* test = new BSTNode<int>(3);
    BSTNode<int>* leftTest = new BSTNode<int>(1);
    test->left = leftTest;

    delete leftTest;
    // delete test->left;
    delete test->right;

    // BSTNode<int>* node8 = new BSTNode<int>(8);
    // BSTNode<int>* node4 = new BSTNode<int>(4);
    // BSTNode<int>* node6 = new BSTNode<int>(6);
    // BSTNode<int>* node10 = new BSTNode<int>(10);
    // BSTNode<int>* node14 = new BSTNode<int>(14);
    // node8->left = node4;
    // node4->right = node6;

    // ASSERT_EQ(node8->left->successor()->getData(), 6);
}