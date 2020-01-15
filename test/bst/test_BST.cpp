#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "BST.hpp"
#include "util.hpp"

using namespace std;
using namespace testing;

/* Empty BST test starts here */

// TEST(BSTTests, EMPTY_TREE_HEIGHT_TEST) {
//     BST<int> bst;
//     ASSERT_EQ(bst.height(), -1);
// }

TEST(BSTTests, INSERTION_TEST) {
    BST<int> bst;

    bst.insert(8);
    bst.insert(3);
    bst.insert(10);
    bst.insert(3);

    ASSERT_EQ(bst.size(), 3);
}

TEST(BSTTests, HEIGHT_TEST) {
    BST<int> bst;
    ASSERT_EQ(bst.height(), -1);

    bst.insert(8);
    ASSERT_EQ(bst.height(), 0);

    bst.insert(3);
    ASSERT_EQ(bst.height(), 1);

    bst.insert(10);
    ASSERT_EQ(bst.height(), 1);

    bst.insert(6);
    bst.insert(7);
    ASSERT_EQ(bst.height(), 3);
}

TEST(BSTTests, BEGIN_END_TEST) {
    BST<int> bst;
    bst.insert(8);
    bst.insert(3);
    bst.insert(10);

    BSTIterator<int> iter = bst.begin();
    ASSERT_EQ(*iter, 3);

    iter++;
    ASSERT_EQ(*iter, 8);

    iter++;
    ASSERT_EQ(*iter, 10);
}

TEST(BSTTests, FIND_TEST) {
    BST<int> bst;
    bst.insert(8);
    bst.insert(3);
    bst.insert(10);
    BSTIterator<int> iter(nullptr);

    ASSERT_EQ(*(bst.find(3)), 3);
    ASSERT_EQ(*(bst.find(8)), 8);
    ASSERT_EQ(*(bst.find(10)), 10);
    ASSERT_EQ(bst.find(11) == iter, true);

    BSTIterator<int> findIter = bst.find(3);
    ASSERT_EQ(*findIter, 3);

    findIter++;
    ASSERT_EQ(*findIter, 8);
}

TEST(BSTTests, EMPTY_TEST) {
    BST<int> bst;
    ASSERT_EQ(bst.empty(), true);
    bst.insert(1);
    ASSERT_EQ(bst.empty(), false);
}

TEST(BSTTests, INORDER_TEST) {
    BST<int> bst;
    bst.insert(8);
    bst.insert(3);
    bst.insert(10);

    vector<int> vec = bst.inorder();
    ASSERT_EQ(vec[0], 3);
    ASSERT_EQ(vec[1], 8);
    ASSERT_EQ(vec[2], 10);
}

/* Small BST test starts here */

/**
 * A simple test fixture from which multiple tests
 * can be created. All fixture tests (denoted by the
 * TEST_F macro) can access the protected members of this
 * fixture. Its data is reset after every test.
 *
 * Builds the following BST:
 *         3
 *        / \
 *       1   4
 *      /     \
 *    -33     100
 */
class SmallBSTFixture : public ::testing::Test {
  protected:
    BST<int> bst;

  public:
    SmallBSTFixture() {
        // initialization code here
        vector<int> input{3, 4, 1, 100, -33};
        insertIntoBST(input, bst);
    }
    // code in SetUp() will execute just before the test ensues
    // void SetUp() {}
};

// TEST_F(SmallBSTFixture, SMALL_SIZE_TEST) {
//     // assert that the small BST has the correct size
//     ASSERT_EQ(bst.size(), 5);
// }

// TEST_F(SmallBSTFixture, SMALL_INSERT_DUPLICATES_TEST) {
//     // assert failed duplicate insertion
//     ASSERT_FALSE(bst.insert(3));
// }

// TODO: add more BST tests here