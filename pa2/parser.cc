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
    // std::cout << __LINE__ << std::endl;
    // std::cout << tknzr->getToken().content << std::endl;
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

// AssignmentParser::AssignmentParser(std::string ln): tknzr {new Tokenizer{ln}} {}

// std::map<std::string, bool> AssignmentParser::parseAssignment() {
//   std::map<std::string, bool> results;
//   // your code starts here
//   if (tknzr->hasToken() && !tknzr->currTokenType("VAR_NAME")) {
//     tknzr->isFalse = 0;
//   }
//   while (tknzr->currTokenType("VAR_NAME")) {
//     std::string name = tknzr->getToken().content;
//     tknzr->addCounter();
//     if (!tknzr->currTokenType("COL")) {
//       tknzr->isFalse = 0;
//       break;
//     }
//     tknzr->addCounter();
//     if (!tknzr->currTokenType("CONST")) {
//       tknzr->isFalse = 0;
//       break;
//     }
//     std::string value = tknzr->getToken().content;
//     if (results.count(name) && ((value == "0" && results[name] == true) || (value == "1" && results[name] == false))) { // contradict assignment
//       tknzr->isFalse = 2;
//       break;
//     }
//     if (value == "0") {
//       results[name] = false;
//     }
//     else if (value == "1") {
//       results[name] = true;
//     }
//     else {
//       tknzr->isFalse = 0;
//       break;
//     }
//     tknzr->addCounter();
//     if (!tknzr->hasToken()) {
//       break;
//     }
//     if (!tknzr->currTokenType("COMMA")) {
//       tknzr->isFalse = 0;
//       break;
//     }
//     else {
//       tknzr->addCounter();
//     }
//   }
//   return results;
// }

// int AssignmentParser::getFalse() {
//   return tknzr->isFalse;
// }

// AssignmentParser::~AssignmentParser() {
//   // your code starts here
//   delete tknzr;
// }
