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
    node.left = new BSTNode<int>(1);
    node.right = new BSTNode<int>(8);

    ASSERT_EQ(node.successor()->getData(), 8);

    delete node.left;
    delete node.right;
}