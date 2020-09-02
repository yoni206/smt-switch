/*********************                                                        */
/*! \file cvc4-printinh.cpp
** \verbatim
** Top contributors (to current version):
**   Yoni Zohar
** This file is part of the smt-switch project.
** Copyright (c) 2020 by the authors listed in the file AUTHORS
** in the top-level source directory) and their institutional affiliations.
** All rights reserved.  See the file LICENSE in the top-level source
** directory for licensing information.\endverbatim
**
** \brief
**
**
**/
#include <fstream>
#include <cstdio>
#include <stdexcept>
#include <string>
#include <array>
#include <iostream>
#include <memory>
#include <vector>
#include <sstream>
#include "assert.h"

// note: this file depends on the CMake build infrastructure
// specifically defined macros
// it cannot be compiled outside of the build
#include "test-utils.h"

#include "cvc4_factory.h"
#include "printing_solver.h"
#include "smt.h"
#include "shortcuts.h"

using namespace smt;
using namespace std;


int main()
{
  SmtSolver s = CVC4SolverFactory::create(false);
  s->set_logic("QF_AUFBV");
  s->set_opt("produce-models", "true");
  s->set_opt("incremental", "true");
  s->set_opt("produce-unsat-assumptions", "true");
  Sort intsort = s->make_sort(INT);
  Term x = s->make_symbol("x", instsort);
  Term y = s->make_symbol("y", intsort);
  Term addition = Plus(x,y);  
  Term equality = Equals(addition, x);
  s->assert_formula(equality);
  cout << s->check_sat() << endl;
  return 0;
}
