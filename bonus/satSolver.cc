#include "satSolver.h"
#include "minisat/core/SolverTypes.h"
#include "minisat/core/Solver.h"
#include <memory>
#include <map>
#include <iostream>

bool DPLL(std::vector<std::vector<int>> &cnf, std::vector<int> &assignment) {
  std::vector<std::vector<int>> cnf1 = BCP(cnf, assignment);
  PLP(cnf, assignment);
  if (cnf1.empty()) {
    return true;
  }
  else if (cnf1.size() == 1 && cnf1[0].size() == 1 && cnf1[0][0] == -1){
    return false;
  }
  // choose_var
  int num = -1;
  std::vector<int> temp1 = assignment;
  for (unsigned int i = 1; i < assignment.size(); i++) {
    if (assignment[i] != 2 && is_exist(cnf1, i)) {
      num = -1;
      break;
    }
    else if (assignment[i] == 2) {
      num = i;
    }
  }
  if (num == -1) {
    return DPLL(cnf1, assignment);
  }
  else {
    assignment[num] = 1;
    if (DPLL(cnf1, assignment)) {
      return true;
    }
    else {
      assignment = temp1;
      assignment[num] = 0;
      return DPLL(cnf1, assignment);
    }
  }
}

std::vector<std::vector<int>> BCP(std::vector<std::vector<int>> &cnf, std::vector<int> &assignment) {
  int len = assignment.size();
  std::vector<std::vector<int>> cnf1;
  bool modified = false;
  int idx = -1;
  for (int i = 1; i < len; i++) {
    if (assignment[i] != 2 && is_exist(cnf, i)) {
      modified = true;
      idx = i;
      break;
    }
  }
  if (modified) {
    for (auto& clause : cnf) {
      int code = -1;
      for (int literal : clause) {
        if (((literal == idx) && (assignment[idx] == 1)) || ((-literal == idx) && (assignment[idx] == 0))) {
          code = 0;
          break;
        }
        else if (((literal == idx) && (assignment[idx] == 0)) || ((-literal == idx) && (assignment[idx] == 1))) {
          code = 1;
          break;
        }
      }
      
      if (code == -1) { // clause remains the same
        cnf1.push_back(clause);
      }
      else if (code == 1) { // shrink the clause by dropping the literal
        std::vector<int> temp;
        for (int lit : clause) {
          if (abs(lit) != idx) {
            temp.push_back(lit);
          }
        }
        cnf1.push_back(temp);
      }
    }
  }
  else {
    cnf1 = cnf;
  }
  std::vector<std::vector<int>> cnf2;
  for (auto& clause : cnf1) {
    if (clause.size() == 1) {
      if (clause[0] > 0) {  // clause[0] is positive
        if (assignment[clause[0]] == 2) {
          assignment[clause[0]] = 1;
        }
        else if (assignment[clause[0]] == 0) {
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
      }
    }
    else {
      cnf2.push_back(clause);
    }
  }
  return cnf2;
}

void PLP(std::vector<std::vector<int>> &cnf, std::vector<int> &assignment) {
  for (unsigned int i = 1; i < assignment.size(); i++) {
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
      }
      else if (!hasPos && hasNeg) {
        assignment[i] = 0;
      }
    }
  }
}

bool is_exist(const std::vector<std::vector<int> >&  v, int item){
  if (v.size() == 0) {
    return false;
  }
  for (unsigned int i = 0; i < v.size(); i++) {
    for (unsigned int j = 0; j < v[i].size(); j++) {
      if (abs(v[i][j]) == item) {
        return true;
      }
    }
  }
  return false;
}