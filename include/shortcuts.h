/*********************                                                        */
/*! \file logging_solver.h
** \verbatim
** Top contributors (to current version):
**   Makai Mann, Clark Barrett
** This file is part of the smt-switch project.
** Copyright (c) 2020 by the authors listed in the file AUTHORS
** in the top-level source directory) and their institutional affiliations.
** All rights reserved.  See the file LICENSE in the top-level source
** directory for licensing information.\endverbatim
**
** \brief Class that wraps another SmtSolver and tracks the term DAG by
**        wrapping sorts and terms and performs hash-consing.
**
**/

#pragma once

#include "solver.h"
#include "term_hashtable.h"

#include <string>

namespace smt {


class Singleton {
   static Singleton *instance;
   Solver solver;
 
   // Private constructor so that no objects can be created.
   Singleton();

   public:
   static Singleton *getInstance();

   Solver getSolver();

   void setSolver(Solver s);


};

  Term And(smt::Term t1, smt::Term t2);
  Term Equal(smt::Term t1, smt::Term t2);


}  // namespace smt
