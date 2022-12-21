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
  }
  else if (fp->getFalse() != -1) {
    code = fp->getFalse();
    arr[code] = 1;
  }
}

// The program shall continuously ask for new inputs from standard input and output to the standard output
// The program should terminate gracefully (and quietly) once it sees EOF
int main() {
 std::string line; // store each input line
  while (std::getline(std::cin, line)) // continuously asking for new inputs from standard input
  {
    // your code starts here
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
      TseitinTransformer ttf(root);
      ttf.transform();
      std::vector<std::vector<int>> temp = ttf.getCnf();
      if (satCallingMiniSat(ttf.getVarNum(), temp)) {
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
    }
    code = -1;
    arr[0] = 0;
  }
  return 0;
}
