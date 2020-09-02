/*********************                                                        */
/*! \file logging_solver.cpp
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

#include "assert.h"

#include "logging_solver.h"
#include "logging_sort.h"
#include "logging_term.h"
#include "sort_inference.h"

#include "utils.h"

using namespace std;

namespace smt {

/* These are the only sortkinds that are supported for get_value
   Terms returned by get_value were not created through the
   smt-switch API, so the LoggingSolver needs to recover some
   information. Most SortKinds are not an issue because they
   have no Op or children
 */

   Singleton::Singleton() {
      solver = AbsSmtSolver();
   }

   static Singleton* Singleton::getInstance()  {
      if (!instance)
      instance = new Singleton;
      return instance;
   }

   Solver Singleton::getSolver() {
      return this->solver ;
   }

   void Singleton::setData(Solver s) {
      this->solver = s;
   }

  Term And(smt::Term t1, smt::Term t2) {
    return Singleton::getInstance()->getSolver().make_term(And, t1, t2);
  }

  Term Equal(smt::Term t1, smt::Term t2) {
    return Singleton::getInstance()->getSolver().make_term(Equal, t1, t2);
  }



}
