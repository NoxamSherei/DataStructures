#pragma once
#include "../pch.h"
#include "../../DataStructures/inc/BinarySearchTree.h"

class BSTTestFixture :public ::testing::Test {
protected:
	std::shared_ptr<BST> tree;
	void SetUp() {
		tree = std::make_shared<BST>();
	}
};

TEST_F(BSTTestFixture, isEmpty) {
	ASSERT_TRUE(tree->isEmpty());
}

TEST_F(BSTTestFixture, testOperations) {
	ASSERT_EQ(tree->getSize(), 0);
	tree->insert(10);
	tree->insert(8);
	tree->insert(12);
	tree->insert(7);
	tree->insert(9);
	ASSERT_EQ(tree->getSize(), 5);
	EXPECT_EQ(tree->search(99),false);
	EXPECT_EQ(tree->search(10), true);
	EXPECT_EQ(tree->search(8), true);
	EXPECT_EQ(tree->search(12), true);
	EXPECT_EQ(tree->search(7), true);
	EXPECT_EQ(tree->search(9), true);
}