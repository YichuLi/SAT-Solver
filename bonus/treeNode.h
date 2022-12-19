#ifndef TNODE_H
#define TNODE_H

#include <string>
#include <map>

// abstract superclass of the syntax tree node
class TreeNode {
    std::string content;
    TreeNode *leftChild = nullptr;
    TreeNode *rightChild = nullptr;
  public:
    TreeNode(std::string cntt);
    TreeNode *getLeftChild() const;
    TreeNode *getRightChild() const;
    // your code starts here
    std::string getContent() const;
    // std::string getType() const;
    virtual bool evaluate(const std::map<std::string, bool> &assignment) const = 0; // pure virtual method
    void updateLeftChild(TreeNode *lChild); // for the operator "-", the operand is stored in leftChild
    void updateChildren(TreeNode *lChild, TreeNode *rChild);
    virtual ~TreeNode();
    TreeNode* getL();
    TreeNode* getR();
    void DestroyRecursive(TreeNode* node);
};

// concrete tree node of opertaor type
class OperatorNode : public TreeNode {
  public:
    OperatorNode(std::string cntt);
    // your code starts here
    bool evaluate(const std::map<std::string, bool> &assignment) const override;
};

// concrete tree node of varibale type
class VariableNode : public TreeNode {
  public:
    VariableNode(std::string cntt);
    // your code starts here
    bool evaluate(const std::map<std::string, bool> &assignment) const override;
};

#endif
