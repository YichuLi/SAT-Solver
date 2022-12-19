#ifndef SAT_H
#define SAT_H

#include <vector>

bool DPLL(std::vector<std::vector<int>> &cnf, std::vector<int> &assignment); // return the SAT result of cnf by calling MiniSAT

std::vector<std::vector<int>> BCP(std::vector<std::vector<int>> &cnf, std::vector<int> &assignment);

bool is_exist(const std::vector<std::vector<int> >&  v, int item);

void PLP(std::vector<std::vector<int>> &cnf, std::vector<int> &assignment);

#endif
