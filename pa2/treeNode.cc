#include "treeNode.h"

TreeNode::TreeNode(std::string cntt): content {cntt} {}

std::string TreeNode::getContent() const {
  // your code starts here
  return this->content;
}

// std::string TreeNode::getType() const {
//   // your code starts here
//   return this->;
// }

TreeNode *TreeNode::getLeftChild() const {
  // your code starts here
  return this->leftChild;
}
TreeNode *TreeNode::getRightChild() const {
  // your code starts here
  return this->rightChild;
}

void TreeNode::updateLeftChild(TreeNode *lChild) {
 this->leftChild = lChild;
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
    return this->getLeftChild()->evaluate(assignment) && this->getRightChild()->evaluate(assignment);
  }
  if (this->getContent() == "+") {
    return this->getLeftChild()->evaluate(assignment) || this->getRightChild()->evaluate(assignment);
  }
  if (this->getContent() == "-") {
    return !this->getLeftChild()->evaluate(assignment);
  }
  return false;
}

VariableNode::VariableNode(std::string cntt): TreeNode{cntt} {}

bool VariableNode::evaluate(const std::map<std::string, bool> &assignment) const {
  // your code starts here
  if (!assignment.count(this->getContent())) {
    return false;
  }
  return assignment.at(this->getContent());
}

TreeNode::~TreeNode() {
  // your code starts here
  DestroyRecursive(this);
}

void TreeNode::DestroyRecursive(TreeNode* node)
{
    if (node)
    {
        DestroyRecursive(node->leftChild);
        DestroyRecursive(node->rightChild);
        delete node;
    }
}