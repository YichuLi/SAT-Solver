#include <iostream>
#include <string>
#include <map>
#include "parser.h"
#include "treeNode.h"

std::string falseType[] = { "Invalid input", "Incomplete assignment", "Contradicting assignment"};
int code = -1;
TreeNode* root;
std::map<std::string, bool> assignment;

// a helper function parsing the input into the formula string and the assignment string
void parseLine(const std::string &line, std::string &formulaStr, std::string &assignmentStr) {
  // your code starts here
  FormulaParser* fp = new FormulaParser(formulaStr);
  root = fp->getTreeRoot();
  if (fp->hasToken()) {
    code = 0;
    std::cout << "Error: " << falseType[0] << std::endl;
  }
  else if (fp->getFalse() != -1) {
    code = fp->getFalse();
    std::cout << "Error: " << falseType[fp->getFalse()] << std::endl;
  }
  // else {
  //   std::cout << root->getContent() << std::endl;
  //   std::cout << root->getL()->getContent() << std::endl;
  //   std::cout << root->getR()->getContent() << std::endl;
  // }
  AssignmentParser* ap = new AssignmentParser(assignmentStr);
  assignment = ap->parseAssignment();
  if (ap->getFalse() != -1) {
    std::cout << "Error: " << falseType[ap->getFalse()] << std::endl;
  }
}


// The program shall continuously ask for new inputs from standard input and output to the standard output
// The program should terminate gracefully (and quietly) once it sees EOF
int main() {
  std::string line; // store each input line
  while (std::getline(std::cin, line)) // continuously asking for new inputs from standard input
  {
    // std::string line; // store each input line
    std::string formulaStr; // store the formula string
    std::string assignmentStr; // store the assignment string
    // your code starts here
    // std::getline(std::cin, line);
    int len = line.size();
    int split;
    for (split = 0; split < len && line[split] != ';'; split++) {
      // formulaStr += line[split];
    }
    formulaStr = line.substr(0, split);
    // Tokenizer t(formulaStr);
    // std::cout << t.getTotal() << std::endl;
    // for (int i = 0; i < t.getTotal(); i++) {
    //   std::cout << t.getToken().content << std::endl;
    //   t.addCounter();
    // }
    if (split + 1 < len) {
      assignmentStr = line.substr(split + 1, len - 1 - split);
    }
    else if (line[split] != ';'){
      std::cout << "Error: " << falseType[0] << std::endl;
    }
    parseLine(line, formulaStr, assignmentStr);
    bool res = root->evaluate(assignment);
    
    // Tokenizer t(line);

    // if (t.isFalse != -1) {
    //   std::cout << "Error: " << falseType[t.isFalse] << std::endl;
    //   continue;
    // }

    // while(t.hasToken()) {
    //   std::cout << t.getToken().content << std::endl;
    //   t.addCounter();
    // }
  }
}
