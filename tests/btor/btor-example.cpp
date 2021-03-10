/*********************                                                        */
/*! \file btor-example.cpp
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
**/

#include <iostream>
#include <vector>

#include "boolector_factory.h"
#include "smt.h"

using namespace smt;
using namespace std;

int main()
{
  SmtSolver s = CVC4SolverFactory::create(false);
  s->set_opt("incremental", "true");

  Sort bvsort9 = s->make_sort(BV, 9);

  Sort funsort = s->make_sort(FUNCTION, { bvsort9, bvsort9 });

  Term x = s->make_symbol("x", bvsort9);

  Term y = s->make_symbol("y", bvsort9);

  Term f = s->make_symbol("f", funsort);

  Term fx = s->make_term(Apply, f, x);

  Term fy = s->make_term(Apply, f, y);

  // Functions are terms

  assert(fx->get_op() == Apply);

  TermVec fx_children(fx->begin(), fx->end());

  assert(fx_children.size() == 2);

  // These equalities are structural e.g. the first child *is* f

  // These are not SMT equalities

  assert(fx_children[0] == f);

  assert(fx_children[1] == x);

  // (assert (distinct (f x) (f y)))

  s->assert_formula(s->make_term(Distinct, fx, fy));

  Term x_7_0 = s->make_term(Op(Extract, 7, 0), x);

  Term y_7_0 = s->make_term(Op(Extract, 7, 0), y);

  // (assert (= ((_ extract 7 0) x) ((_ extract 7 0) y)))

  s->assert_formula(s->make_term(Equal, x_7_0, y_7_0));

  Result r = s->check_sat();

  assert(r.is_sat());  // the MSB of x and y can be different

  // (assert (= ((_ extract 8 8) x) ((_ extract 8 8) y)))

  s->assert_formula(s->make_term(Equal,

                                 s->make_term(Op(Extract, 8, 8), x),

                                 s->make_term(Op(Extract, 8, 8), y)));

  r = s->check_sat();

  assert(r.is_unsat());

  return 0;
}
