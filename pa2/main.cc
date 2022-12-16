#include "tseitinTransformer.h"
#include "satSolver.h"
#include <iostream>
#include <string>
#include <map>
#include "parser.h"
#include "treeNode.h"

std::string falseType[] = { "invalid input", "incomplete assignment", "contradicting assignment"};
std::vector<int> arr =  {0,0,0};
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
    arr[code] = 1;
    // std::cout << "Error: " << falseType[code] << std::endl;
  }
  else if (fp->getFalse() != -1) {
    code = fp->getFalse();
    arr[code] = 1;
    // std::cout << "Error: " << falseType[code] << std::endl;
  }

  AssignmentParser* ap = new AssignmentParser(assignmentStr);
  assignment = ap->parseAssignment();
  if (ap->getFalse() != -1) {
    code = ap->getFalse();
    arr[code] = 1;
  }
}

// The program shall continuously ask for new inputs from standard input and output to the standard output
// The program should terminate gracefully (and quietly) once it sees EOF
int main() {
 std::string line; // store each input line
  while (std::getline(std::cin, line)) // continuously asking for new inputs from standard input
  {
    std::string formulaStr; // store the formula string
    std::string assignmentStr; // store the assignment string
    // your code starts here
    int len = line.size();
    int split;
    for (split = 0; split < len && line[split] != ';'; split++) {
      // formulaStr += line[split];
    }
    formulaStr = line.substr(0, split);
    if (split + 1 < len) {
      assignmentStr = line.substr(split + 1, len - 1 - split);
    }
    else if (line[split] != ';'){
      code = 0;
      arr[code] = 1;
    }
    parseLine(line, formulaStr, assignmentStr);

    Tokenizer t(formulaStr);
    std::vector<std::string> var;
    for (int i = 0; i < t.getTotal(); i++) {
      if (t.getToken().type == "VAR_NAME") {
        var.push_back(t.getToken().content);
      }
      t.addCounter();
    }
    for (size_t i = 0; i < var.size(); i++) {
      if (!assignment.count(var[i])) {
        code = 1;
        arr[code] = 1;
      }
    }
    if (code == -1) {
      bool res = root->evaluate(assignment);
      std::cout << res << std::endl;
    }
    else {
      if (arr[0] == 1) {
        std::cout << "Error: " << falseType[0] << std::endl;
      }
      else if (arr[1] == 1) {
        std::cout << "Error: " << falseType[1] << std::endl;
      }
      else if (arr[2] == 1) {
        std::cout << "Error: " << falseType[2] << std::endl;
      }
      else {
        std::cout << "Wrong with code" << std::endl;
      }
    }
    code = -1;
    arr[0] = 0;
    arr[1] = 0;
    arr[2] = 0;
  }
  return 0;
}
