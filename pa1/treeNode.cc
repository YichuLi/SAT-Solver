#include "treeNode.h"

TreeNode::TreeNode(std::string cntt): content {cntt} {}

std::string TreeNode::getContent() const {
  // your code starts here
  return this->content;
}

TreeNode *TreeNode::getLeftChild() const {
  // your code starts here
  return this->leftChild;
}
TreeNode *TreeNode::getRightChild() const {
  // your code starts here
  return this->rightChild;
}

void TreeNode::updateLeftChild(TreeNode *lChild) {
 this->rightChild = lChild;
}

void TreeNode::updateChildren(TreeNode *lChild, TreeNode *rChild) {
  this->leftChild = lChild;
  this->rightChild = rChild;
}

TreeNode* TreeNode::getL() {
  return this->leftChild;
}

TreeNode* TreeNode::getR() {
  return this->rightChild;
}

OperatorNode::OperatorNode(std::string cntt): TreeNode{cntt} {}

bool OperatorNode::evaluate(const std::map<std::string, bool> &assignment) const {
  // your code starts here
  if (this->getContent() == "*") {
    return this->getLeftChild() && this->getRightChild();
  }
  if (this->getContent() == "+") {
    return this->getLeftChild() || this->getRightChild();
  }
  if (this->getContent() == "-") {
    return !this->getLeftChild();
  }
  return false;
}

ConstantNode::ConstantNode(std::string cntt): TreeNode{cntt} {}

bool ConstantNode::evaluate(const std::map<std::string, bool> &assignment) const {
  // your code starts here
  if (this->getContent() == "1") {
    return true;
  }
  return false;
}

VariableNode::VariableNode(std::string cntt): TreeNode{cntt} {}

bool VariableNode::evaluate(const std::map<std::string, bool> &assignment) const {
  // your code starts here
  if (this->getContent() == "1") {
    return true;
  }
  return false;
}

TreeNode::~TreeNode() {
  // your code starts here
}
