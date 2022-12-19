#include "tseitinTransformer.h"
#include "satSolver.h"
#include <iostream>
#include <string>
#include <map>
#include "parser.h"
#include "treeNode.h"

std::string falseType[] = { "invalid input"};
// std::string falseType = "invalid input";
std::vector<int> arr =  {0};
int code = -1;
TreeNode* root;
std::map<std::string, bool> assignment;

// a helper function parsing the input into the formula string and the assignment string
void parseLine(const std::string &line) {
  // your code starts here
  FormulaParser* fp = new FormulaParser(line);
  root = fp->getTreeRoot();

  if (fp->hasToken()) {
    code = 0;
    arr[code] = 1;
    // std::cout << __LINE__ << std::endl;
  }
  else if (fp->getFalse() != -1) {
    code = fp->getFalse();
    arr[code] = 1;
    // std::cout << __LINE__ << std::endl;
    // std::cout << "Error: " << falseType[code] << std::endl;
  }

  // AssignmentParser* ap = new AssignmentParser(assignmentStr);
  // assignment = ap->parseAssignment();
  // if (ap->getFalse() != -1) {
  //   code = ap->getFalse();
  //   arr[code] = 1;
  // }
}

// The program shall continuously ask for new inputs from standard input and output to the standard output
// The program should terminate gracefully (and quietly) once it sees EOF
int main() {
 std::string line; // store each input line
  while (std::getline(std::cin, line)) // continuously asking for new inputs from standard input
  {
    // std::string formulaStr; // store the formula string
    // std::string assignmentStr; // store the assignment string
    // your code starts here
    int len = line.size();
    // int split;
    // for (split = 0; split < len && line[split] != ';'; split++) {
    //   // formulaStr += line[split];
    // }
    // formulaStr = line.substr(0, split);
    // if (split + 1 < len) {
    //   assignmentStr = line.substr(split + 1, len - 1 - split);
    // }
    // else if (line[split] != ';'){
    //   code = 0;
    //   arr[code] = 1;
    // }
    parseLine(line);

    Tokenizer t(line);
    std::vector<std::string> var;
    for (int i = 0; i < t.getTotal(); i++) {
      if (t.getToken().type == "VAR_NAME") {
        var.push_back(t.getToken().content);
      }
      t.addCounter();
    }
    if (code == -1) {
      // bool res = root->evaluate(assignment);
      // std::cout << res << std::endl;
      TseitinTransformer ttf(root);
      ttf.transform();
      std::cout << ttf.cnfString() << std::endl;
      std::vector<std::vector<int>> temp = ttf.getCnf();
      std::vector<int> assignment(ttf.getVarNum() + 1, 2);  // 0: unsat, 1: sat, 2: unknown
      if (DPLL(temp, assignment)) {
        std::cout << "sat" << std::endl;
      }
      else {
        std::cout << "unsat" << std::endl;
      }
      
    }
    else {
      if (arr[0] == 1) {
        std::cout << "Error: " << falseType[0] << std::endl;
      }
      // else if (arr[1] == 1) {
      //   std::cout << "Error: " << falseType[1] << std::endl;
      // }
      // else if (arr[2] == 1) {
      //   std::cout << "Error: " << falseType[2] << std::endl;
      // }
      // else {
      //   std::cout << "Wrong with code" << std::endl;
      // }
    }
    code = -1;
    arr[0] = 0;
    // arr[1] = 0;
    // arr[2] = 0;
  }
  return 0;
}