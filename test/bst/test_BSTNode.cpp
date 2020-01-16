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

    BSTNode<int> node3(3);
    BSTNode<int> node10(10);

    node8.left = &node3;
    node3.parent = &node8;

    node8.right = &node10;
    node10.parent = &node8;

    ASSERT_EQ(node3.successor()->getData(), 8);
    ASSERT_EQ(node8.successor()->getData(), 10);
    ASSERT_EQ(node10.successor(), nullptr);
}