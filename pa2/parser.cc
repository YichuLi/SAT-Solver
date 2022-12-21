#include "parser.h"
#include "treeNode.h"
#include "tokenizer.h"

FormulaParser::FormulaParser(std::string ln): tknzr {new Tokenizer{ln}} {}

TreeNode *FormulaParser::parseConjTerm() {
  // your code starts here
  TreeNode* t1 = parseTerm();
  while (true) {
    if (tknzr->currTokenType("MULT") == false) {
      break;
    }
    tknzr->addCounter();
    TreeNode* t2 = parseConjTerm();
    TreeNode* addNode = new OperatorNode("*");
    addNode->updateChildren(t1, t2);
    return addNode;
  }
  return t1;
}

TreeNode *FormulaParser::parseTerm() {
  // your code starts here 
  if (tknzr->currTokenType("LPR")) {
    tknzr->addCounter();
    TreeNode* t = parseFormula();
    // tknzr->addCounter();
    if (!tknzr->currTokenType("RPR")) {
      tknzr->isFalse = 0;
    }
    else {
      tknzr->addCounter();
      return t;
    }
  }
  else if (tknzr->currTokenType("VAR_NAME")) {
    VariableNode* vn = new VariableNode(tknzr->getToken().content);
    tknzr->addCounter();
    return vn;
  }
  else if (tknzr->currTokenType("NEG")) {
    tknzr->addCounter();
    TreeNode* t = parseTerm();
    TreeNode* addNode = new OperatorNode("-");
    addNode->updateLeftChild(t);
    return addNode;
  }
  else {
    tknzr->isFalse = 0;
  }
  return nullptr;
}

TreeNode *FormulaParser::parseFormula() {
  // your code starts here
  TreeNode* t1 = parseConjTerm();
  while (true) {
    TreeNode* t2;
    if (!tknzr->currTokenType("ADD")) {
      break;
    }
    tknzr->addCounter();
    t2 = parseFormula();
    TreeNode* addNode = new OperatorNode("+");
    addNode->updateChildren(t1, t2);
    return addNode;
  }
  return t1;
}

TreeNode * FormulaParser::getTreeRoot() {
  return parseFormula();
}

int FormulaParser::getFalse() {
  return tknzr->isFalse;
}

bool FormulaParser::hasToken() {
  return tknzr->hasToken();
}
FormulaParser::~FormulaParser() {
  // your code starts here
  delete tknzr;
}
