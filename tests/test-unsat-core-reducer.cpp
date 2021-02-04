/*********************                                                        */
/*! \file test-unsat-core-reducer.cpp
** \verbatim
** Top contributors (to current version):
**   Ahmed Irfan, Makai Mann
** This file is part of the smt-switch project.
** Copyright (c) 2020 by the authors listed in the file AUTHORS
** in the top-level source directory) and their institutional affiliations.
** All rights reserved.  See the file LICENSE in the top-level source
** directory for licensing information.\endverbatim
**
** \brief Tests for unsat-core-based reducer.
**
**
**/

#include <utility>
#include <vector>

#include "available_solvers.h"
#include "gtest/gtest.h"
#include "smt.h"
#include "utils.h"

using namespace smt;
using namespace std;

namespace smt_tests {

class UnsatCoreReducerTests
    : public ::testing::Test,
      public ::testing::WithParamInterface<SolverConfiguration>
{
 protected:
  void SetUp() override
  {
    s = create_solver(GetParam());
    boolsort = s->make_sort(BOOL);

    r = create_solver(GetParam());
  }
  SmtSolver s;
  Sort boolsort;
  SmtSolver r;
};

TEST_P(UnsatCoreReducerTests, UnsatCoreReducer)
{
  UnsatCoreReducer uscr(r);

  Term a = s->make_symbol("a", boolsort);
  Term b = s->make_symbol("b", boolsort);
  Term formula = s->make_term(And, a, b);
  TermVec assump({ s->make_term(Not, a), s->make_term(Not, b) });
  TermVec red, rem;

  uscr.reduce_assump_unsatcore(formula, assump, red, &rem);
  EXPECT_TRUE(red.size() == 1);
  EXPECT_TRUE(rem.size() == 1);
  EXPECT_TRUE(rem[0] != red[0]);
}

TEST_P(UnsatCoreReducerTests, UnsatCoreReducerLinear)
{
  UnsatCoreReducer uscr(r);

  Term a = s->make_symbol("a", boolsort);
  Term b = s->make_symbol("b", boolsort);
  Term formula = s->make_term(And, a, b);
  TermVec assump({ s->make_term(Not, a), s->make_term(Not, b) });
  TermVec red, rem;

  uscr.linear_reduce_assump_unsatcore(formula, assump, red, &rem);
  EXPECT_EQ(red.size() , 1);
  EXPECT_EQ(rem.size() , 1);
  EXPECT_NE(rem[0] , red[0]);
}

// The unsat cores reducer module requires the
// underlying solver to support both unsat cores
// and term translation.
INSTANTIATE_TEST_SUITE_P(ParameterizedSolverUnsatCoreReducerTests,
                         UnsatCoreReducerTests,
                         testing::ValuesIn(filter_solver_configurations(
                             { UNSAT_CORE, FULL_TRANSFER })));

}  // namespace smt_tests
