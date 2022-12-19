#include "satSolver.h"
#include "minisat/core/SolverTypes.h"
#include "minisat/core/Solver.h"
#include <memory>
#include <map>
#include <iostream>
// bool satCallingMiniSat(unsigned int numVar, std::vector<std::vector<int>> &cnf) {
//   // your code starts here
//   std::unique_ptr<Minisat::Solver> solver(new Minisat::Solver());
//   Minisat::vec<Minisat::Lit> literals;
//   for (int i = 0; i < numVar; i++) {
//     literals.push(Minisat::mkLit(solver->newVar()));
//   }

//   // Add the clauses to the solver
//   for (const auto &clause : cnf) {
//     Minisat::vec<Minisat::Lit> clauseVec;
//     for (const auto &lit : clause) {
//       Minisat::Lit literal;
//       if (lit < 0) {
//         literal = ~literals[-lit - 1];
//       }
//       else {
//         literal = literals[lit - 1];
//       }
//       // Minisat::Lit literal = Minisat::mkLit(std::abs(lit), lit < 0);

//       clauseVec.push(literal);
//     }
//     solver->addClause(clauseVec);
//   }
  
//   return solver->solve();
// }

bool DPLL(std::vector<std::vector<int>> &cnf, std::vector<int> &assignment) {
  // std::cout << "DPLL in:" << __LINE__ << std::endl;
  std::vector<std::vector<int>> cnf1 = BCP(cnf, assignment);
  PLP(cnf, assignment);
  std::cout << "------------" << std::endl;
  // std::cout << "cnf1 size: " << cnf1.size() << std::endl;
  // for (auto& i : cnf1) {
  //   for (int j : i) {
  //     std::cout << j << ",";
  //   }
  //   std::cout << std::endl;
  // }
  // std::cout << "assignment: ";
  // for (int i = 0; i < assignment.size(); i++) {
  //   std::cout << i << ":" << assignment[i] << std::endl;
  // }
  if (cnf1.empty()) {
    return true;
  }
  else if (cnf1.size() == 1 && cnf1[0].size() == 1 && cnf1[0][0] == -1){
    return false;
  }
  // choose_var
  int num = -1;
  for (int i = 1; i < assignment.size(); i++) {
    if (assignment[i] != 2 && is_exist(cnf1, i)) {
      num = -1;
      break;
    }
    else if (assignment[i] == 2) {
      num = i;
    }
  }
  if (num == -1) {
    // std::cout << "ERROR in:" << __LINE__ << std::endl;
    // std::cout << "DENGDAI in:" << __LINE__ << std::endl;
    return DPLL(cnf1, assignment);
  }
  else {
    // std::vector<int> temp1 = assignment;
    // std::vector<std::vector<int>> temp2 = cnf1;
    assignment[num] = 1;
    if (DPLL(cnf1, assignment)) {
      return true;
    }
    else {
      // assignment = temp1;
      // cnf1 = temp2;
      assignment[num] = 0;
      return DPLL(cnf1, assignment);
    }
  }
}

// 1: for each pair (v,u) in A
// 2:          for each clause C in ϕ
// 3:                     if ((v occurs positively in C and u is the value true) OR
//                               v occurs negatively in C and u is the value false)) then
//                               mark the clause C as satisfied and remove from ϕ
// 4:                    if ((v occurs positively in C and u is the value false) OR
//                              v occurs negatively and u is the value true)) then
//                              mark the literal as false, and shrink the clause C by dropping v
// 5:                    if C becomes unit, add it to the map A with appropriate value and remove it from ϕ
// 6: Return the modified formula //Note that the formula ϕ is being modified by either dropping clauses (step 3 and step 5) or dropping literals (step 4)

std::vector<std::vector<int>> BCP(std::vector<std::vector<int>> &cnf, std::vector<int> &assignment) {
  int len = assignment.size();
  std::vector<std::vector<int>> cnf1;
  bool modified = false;
  int idx = -1;
  // std::cout << __LINE__ << std::endl;
  for (int i = 1; i < len; i++) {
    if (assignment[i] != 2 && is_exist(cnf, i)) {
      modified = true;
      idx = i;
      std::cout << "idx is: " << idx << std::endl;
      break;
    }
  }
  // std::cout << __LINE__ << std::endl;
  if (modified) {
    for (auto& clause : cnf) {
      // std::vector<int> formula;
      int code = -1;
      for (int literal : clause) {
        std::cout << literal << ",";
        // int code = -1;
        if (((literal == idx) && (assignment[idx] == 1)) || ((-literal == idx) && (assignment[idx] == 0))) {
          code = 0;
          // break;
        }
        else if (((literal == idx) && (assignment[idx] == 0)) || ((-literal == idx) && (assignment[idx] == 1))) {
          code = 1;
          // break;
        }
      }
      std::cout << "code is " << code;
      std::cout << std::endl;
      
      if (code == -1) { // clause remains the same
        cnf1.push_back(clause);
      }
      else if (code == 1) { // shrink the clause by dropping the literal
        std::vector<int> temp;
        for (int lit : clause) {
          // std::cout << abs(lit) << std::endl;
          if (abs(lit) != idx) {
            temp.push_back(lit);
          }
        }
        std::cout << "temp: [";
        for (int l : temp) {
          std::cout << l << ",";
        }
        std::cout << "]" << std::endl;
        // std::cout << __LINE__ << std::endl;
        cnf1.push_back(temp);
      }
    }
  }
  else {
    cnf1 = cnf;
  }
  // std::cout << __LINE__ << std::endl;
  std::vector<std::vector<int>> cnf2;
  for (auto& clause : cnf1) {
    // std::cout << __LINE__ << std::endl;
    if (clause.size() == 1) {
      if (clause[0] > 0) {  // clause[0] is positive
        if (assignment[clause[0]] == 2) {
          assignment[clause[0]] = 1;
        }
        else if (assignment[clause[0]] == 0) {
          std::cout << "Bye!" << std::endl;
          return {{-1}};
        }
      }
      else {  // clause[0] is negative
        if (assignment[-clause[0]] == 2) {
          assignment[-clause[0]] = 0;
        }
        else if (assignment[-clause[0]] == 1) {
          return {{-1}};
        }
        // assignment[clause[0]] = 0;
      }
      // std::cout << __LINE__ << std::endl;
      // return BCP(cnf1, assignment);
      // std::cout << __LINE__ << std::endl;
    }
    else {
      cnf2.push_back(clause);
    }
  }
  // std::cout << __LINE__ << std::endl;
  return cnf2;
}

void PLP(std::vector<std::vector<int>> &cnf, std::vector<int> &assignment) {
  std::vector<std::vector<int>> cnf2;
  for (int i = 1; i < assignment.size(); i++) {
    bool hasPos = false;
    bool hasNeg = false;
    if (assignment[i] == 2) {
      for (auto& clause : cnf) {
        for (int lit : clause) {
          if (i == lit) {
            hasPos = true;
          }
          else if (i == -lit) {
            hasNeg = true;
          }
        }
      }
      if (hasPos && !hasNeg) {
        assignment[i] = 1;
        // bool drop = false;
        // for (auto& clause2 : cnf) {
        //   for (int k : clause2) {
        //     if (k == i) {
        //       drop = true;
        //     }
        //   }
        //   if (!drop) {
        //     cnf2.push_back(clause2);
        //   }
        // }
      }
      else if (!hasPos && hasNeg) {
        assignment[i] = 0;
        // bool drop = false;
        // for (auto& clause2 : cnf) {
        //   for (int k : clause2) {
        //     if (k == -i) {
        //       drop = true;
        //     }
        //   }
        //   if (!drop) {
        //     cnf2.push_back(clause2);
        //   }
        // }
      }
    }
  }
}

// std::vector<std::vector<int>> BCP(std::vector<std::vector<int>> &cnf, std::vector<int> &assignment) {
//   int len = assignment.size();
//   std::vector<std::vector<int>> cnf1;
//   for (int i = 1; i < len; i++) {
//     if (assignment[i] != 2) { // for each assigned literal
//       for (auto& clause : cnf) {
//         int code = -1;  // 0: remove clause, 1: drop literal
//         for (int literal : clause) {
//           if (((literal == i) && (assignment[i] == 1)) || ((-literal == i) && (assignment[i] == 0))) {
//             code = 0;
//             break;
//           }
//           else if (((literal == i) && (assignment[i] == 0)) || ((-literal == i) && (assignment[i] == 1))) {
//             code = 1;
//             break;
//           }
//         }
//         if (code == -1) {
//           cnf1.push_back(clause);
//         }
//         else if (code == 1) {
//           std::vector<int> temp;
//           for (int lit : clause) {
//             if (abs(lit) != i) {
//               temp.push_back(lit);
//             }
//           }
//           cnf1.push_back(temp);
//         }
//       }
//     }
//   }
//   for (auto& clause : cnf1) {
//     if (clause.size() == 1) {
//       if (clause[0] > 0) {
//         assignment[clause[0]] = 1;
//       }
//       else {
//         assignment[clause[0]] = 0;
//       }
//       BCP(cnf1, assignment);
//     }
//   }
//   return cnf1;
// }

bool is_exist(const std::vector<std::vector<int> >&  v, int item){
  for (auto row = v.begin(); row != v.end(); row++) {
      if (std::find(row->begin(), row->end(), item) != row->end()) {
        return true;
      }
      if (std::find(row->begin(), row->end(), -item) != row->end()) {
        return true;
      }
  }

  return false;
}