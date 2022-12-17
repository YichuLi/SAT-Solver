#include "satSolver.h"
#include "minisat/core/SolverTypes.h"
#include "minisat/core/Solver.h"

bool satCallingMiniSat(unsigned int numVar, std::vector<std::vector<int>> &cnf) {
  // your code starts here
  std::unique_ptr<Minisat::Solver> solver(new Minisat::Solver());
  Minisat::vec<Minisat::Lit> literals;
  for (int i = 0; i < numVar; i++) {
    literals.push(Minisat::mkLit(solver->newVar()));
  }

  // Add the clauses to the solver
  for (const auto &clause : cnf) {
    Minisat::vec<Minisat::Lit> clauseVec;
    for (const auto &lit : clause) {
      Minisat::Lit literal;
      if (lit < 0) {
        literal = ~literals[-lit - 1];
      }
      else {
        literal = literals[lit - 1];
      }
      // Minisat::Lit literal = Minisat::mkLit(std::abs(lit), lit < 0);

      clauseVec.push(literal);
    }
    solver->addClause(clauseVec);
  }
  
  return solver->solve();
}
 