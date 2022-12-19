#include "tseitinTransformer.h"

TseitinTransformer::TseitinTransformer(TreeNode *root): formulaRoot{root} {}

int TseitinTransformer::transSubformula(TreeNode* subRoot) {
  // your code starts here
  std::string content = subRoot->getContent();
  int currIdCounter = varIdCounter;
  if (content == "-") {
    varIdCounter++;
    int child = transSubformula(subRoot->getLeftChild());
    addNegEq(currIdCounter, child);
  }
  else if (content == "+") {
    varIdCounter++;
    int l_child = transSubformula(subRoot->getLeftChild());
    int r_child = transSubformula(subRoot->getRightChild());
    addOrEq(currIdCounter, l_child, r_child);
  }
  else if (content == "*") {
    varIdCounter++;
    int l_child = transSubformula(subRoot->getLeftChild());
    int r_child = transSubformula(subRoot->getRightChild());
    addAndEq(currIdCounter, l_child, r_child);
  }
  else {
    if (varIdTable.count(content)) {
      return varIdTable[content];
    }
    else {  // new variable to be assigned
      varIdTable[content] = varIdCounter;
      varIdCounter++;
    }
  }
  return currIdCounter;
}

void TseitinTransformer::addNegEq(int curID, int childID) {
  // your code starts here
  // std::vector<int> arr = [{-curID, -childID}, {curID, childID}];
  cnf.push_back({-curID, -childID});
  cnf.push_back({curID, childID});
}

void TseitinTransformer::addOrEq(int curID, int leftID, int rightID) {
  // your code starts here
  cnf.push_back({-curID, leftID, rightID});
  cnf.push_back({curID, -leftID});
  cnf.push_back({curID, -rightID});
}

void TseitinTransformer::addAndEq(int curID, int leftID, int rightID) {
  // your code starts here
  cnf.push_back({curID, -leftID, -rightID});
  cnf.push_back({-curID, leftID});
  cnf.push_back({-curID, rightID});
}

std::vector<std::vector<int>> TseitinTransformer::transform() {
  // your code starts here
  transSubformula(formulaRoot);
  cnf.push_back({1});
  return cnf;
}

std::string TseitinTransformer::cnfString() const {
  std::string result = "";
  if (cnf.size() == 0) {
    return "Error";
  }
  // your code starts here
  for (auto v : cnf) {
    result += "[";
    for (int i : v) {
      result += std::to_string(i);
      result += ",";
    }
    result += "]";
  }
  return result;
}

unsigned int TseitinTransformer::getVarNum() const {
  // your code starts here
  unsigned int res = varIdCounter - 1;
  return res;
}

std::vector<std::vector<int>> TseitinTransformer::getCnf() {
  return cnf;
}
