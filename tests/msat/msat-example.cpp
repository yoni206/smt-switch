#include <iostream>
#include "msat_factory.h"
#include "smt.h"
using namespace smt; using namespace std;

int main()
{
  SmtSolver s = MsatSolverFactory::create(true);
  s->set_logic("QF_UFBV");
  s->set_opt("incremental", "true");
  s->set_opt("produce-models", "true");
  s->set_opt("produce-unsat-assumptions", "true");
  Sort bvsort = s->make_sort(BV, 32);
  Sort funsort = s->make_sort(FUNCTION, {bvsort, bvsort});

  Term x = s->make_symbol("x", bvsort);
  Term y = s->make_symbol("y", bvsort);
  Term f = s->make_symbol("f", funsort);
  Term fx = s->make_term(Apply, f, x);
  Term fy = s->make_term(Apply, f, y);
  Term x0 = s->make_term(Op(Extract, 15, 0), x);
  Term y0 = s->make_term(Op(Extract, 15, 0), y);
  
  s->assert_formula(s->make_term(Distinct, fx, fy));

  s->push(1);
  s->assert_formula(s->make_term(Equal, x0, y0));
  cout <<  s->check_sat() << endl;
  cout << s->get_value(x) << endl;
  s->pop(1);

  Term x_and_y = s->make_term(BVAnd, x, y);
  Sort boolsort = s->make_sort(BOOL);
  Term a1 = s->make_symbol("a1", boolsort);
  Term a2 = s->make_symbol("a2", boolsort);
  Term a3 = s->make_symbol("a3", boolsort);
  s->assert_formula(s->make_term(Equal, a1, s->make_term(BVUge, x_and_y, x)));
  s->assert_formula(s->make_term(Equal, a2, s->make_term(BVUge, x_and_y, y)));
  s->assert_formula(s->make_term(Equal, a3, s->make_term(BVUge, x0, y0)));
  cout << s->check_sat_assuming({a1, a2, a3}) << endl;
  UnorderedTermSet ua; 
  s->get_unsat_assumptions(ua); 
  for (Term t : ua) { cout << t << endl; }
}
