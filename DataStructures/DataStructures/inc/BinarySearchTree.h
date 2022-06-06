#pragma once
#include <iostream>

class BST {
private:
	struct BSTNode {
		int32_t value;
		std::shared_ptr<BSTNode> rightLeaf;
		std::shared_ptr<BSTNode> leftLeaf;
		BSTNode() = default;
		BSTNode(int32_t value) :value(value) {}
		bool leftExist() { return leftLeaf != nullptr; }
		bool rightExist() { return rightLeaf != nullptr; }
		friend bool operator== (const BSTNode& lv, const BSTNode& rv) { return lv.value == rv.value; }
		friend bool operator>= (const BSTNode& lv, const BSTNode& rv) { return lv.value >= rv.value; }
		friend bool operator<= (const BSTNode& lv, const BSTNode& rv) { return lv.value <= rv.value; }
		friend bool operator> (const BSTNode& lv, const BSTNode& rv) { return lv.value > rv.value; }
		friend bool operator< (const BSTNode& lv, const BSTNode& rv) { return lv.value < rv.value; }
		friend bool operator== (const int32_t& lv, const BSTNode& rv) { return lv == rv.value; }
		friend bool operator>= (const int32_t& lv, const BSTNode& rv) { return lv >= rv.value; }
		friend bool operator<= (const int32_t& lv, const BSTNode& rv) { return lv <= rv.value; }
		friend bool operator> (const int32_t& lv, const BSTNode& rv) { return lv > rv.value; }
		friend bool operator< (const int32_t& lv, const BSTNode& rv) { return lv < rv.value; }
	};
	std::shared_ptr<BSTNode> root;
	size_t size;
	void handleInsertOperation(const int32_t& value, std::shared_ptr<BSTNode>& node) {
		if (value > *node)
			if (node->rightExist()) handleInsertOperation(value, node->rightLeaf);
			else node->rightLeaf = std::make_shared<BSTNode>(value);
		else
			if (node->leftExist()) handleInsertOperation(value, node->leftLeaf);
			else node->leftLeaf = std::make_shared<BSTNode>(value);
	}
	bool handleSearchOperation(const int32_t& value, const std::shared_ptr<BSTNode>& node)const {
		if (value == *node) return true;
		//check other nodes
		else if (value > *node)
			if (node->rightExist())handleSearchOperation(value, node->rightLeaf);
			else return false;
		else
			if (node->leftExist())handleSearchOperation(value, node->leftLeaf);
			else return false;
	}
	bool handleRemoveOperation(const int32_t& value, std::shared_ptr<BSTNode>& node, std::shared_ptr<BSTNode> backNode = nullptr) {
		if (value == *node) {
			int childNo = 0;
			if (node->leftExist())childNo++;
			if (node->rightExist())childNo++;
			switch (childNo) {
			case 0:
				if (backNode != nullptr) {
					 
				}
				else {

				}
				break;
			case 1:
				break;
			case 2:
				break;
			}
			return true;
		}
		//check other nodes
		else if (value > *node)
			if (node->rightExist())handleRemoveOperation(value, node->rightLeaf, node);
			else return false;
		else
			if (node->leftExist())handleRemoveOperation(value, node->leftLeaf, node);
			else return false;
	}
public:
	bool isEmpty()const { return root == nullptr; }
	size_t getSize() { return size; }
	void insert(const int32_t& value) {
		if (!isEmpty()) handleInsertOperation(value, root);
		else root = std::make_shared<BSTNode>(value);
		size++;
	}
	bool search(const int32_t& value) const {
		if (!isEmpty())	return handleSearchOperation(value, root);
		return false;
	}
	bool remove(const int32_t& value) {
		if (!isEmpty())	return handleRemoveOperation(value, root);
		return false;
	}
};