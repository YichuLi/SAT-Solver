#include "tseitinTransformer.h"

TseitinTransformer::TseitinTransformer(TreeNode *root): formulaRoot{root} {}

int TseitinTransformer::transSubformula(TreeNode* subRoot) {
  // your code starts here
  std::string content = subRoot->getContent();
  if (content == "-") {
    int child = transSubformula(subRoot->getLeftChild());
    addNegEq(varIdCounter, child);
  }
  else if (content == "+") {
    int l_child = transSubformula(subRoot->getLeftChild());
    int r_child = transSubformula(subRoot->getRightChild());
    addOrEq(varIdCounter, l_child, r_child);
  }
  else if (content == "*") {
    int l_child = transSubformula(subRoot->getLeftChild());
    int r_child = transSubformula(subRoot->getRightChild());
    addAndEq(varIdCounter, l_child, r_child);
  }
  else {
    if (varIdTable.count(content)) {
      return varIdTable[content];
    }
    else {
      varIdTable[content] = varIdCounter;
    }
  }
  varIdCounter++;
  return varIdCounter;
}

void TseitinTransformer::addNegEq(int curID, int childID) {
  // your code starts here
}

void TseitinTransformer::addOrEq(int curID, int leftID, int rightID) {
  // your code starts here
}

void TseitinTransformer::addAndEq(int curID, int leftID, int rightID) {
  // your code starts here
}

std::vector<std::vector<int>> TseitinTransformer::transform() {
  // your code starts here
  
  return cnf;
}

std::string TseitinTransformer::cnfString() const {
  std::string result = "";
  // your code starts here
  return result;
}

unsigned int TseitinTransformer::getVarNum() const {
  // your code starts here
  return 0;
}
