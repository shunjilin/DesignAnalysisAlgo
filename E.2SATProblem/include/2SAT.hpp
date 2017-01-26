//Copyright 2017 <Shunji Lin>

#ifndef TWOSAT_HPP
#define TWOSAT_HPP

#include "SCC.hpp"
#include <vector>
#include <utility>

using namespace scc;

namespace twosat {

    struct Clause {
	// stores the clause, negation is represented by negative int
	int u;
	int v;
	Clause(int u, int v) : u(u), v(v) {}
    };

    int literalToVertice(int literal) {
	//Assumption: literal starts from 1
	//Maps positive and negative literals to vertice indexes:
	//[0,n_vertices)
	if (literal > 0) {
	    return (literal * 2) - 2;
	} else {
	    return (-literal * 2) - 1;
	}
    }
    
    class TwoSat {
	int n_variables;
	SCC scc;
	bool solved;
    public:
	TwoSat() {}
	TwoSat(int n_variables, std::vector<Clause> &clauses) :
	    n_variables(n_variables), solved(false)
	{
	    // one vertice for positive and one for negative literal
	    int n_vertices = n_variables * 2;
	    Graph graph = Graph(n_vertices);
	    for (auto & clause : clauses) {
		graph.insertEdge(literalToVertice(-clause.u),
				 literalToVertice(clause.v));
		graph.insertEdge(literalToVertice(-clause.v),
				 literalToVertice(clause.u));
	    }
	    scc = SCC(std::move(graph));
	}

	bool isSatisfiable() {
	    if (!solved) {
		scc.solve();
		solved = true;
	    }
	    for (int i = 1; i <= n_variables; ++i) {
		// if positive and negative of same literal in same scc,
		// 2SAT is unsatisfiable
		if (scc.grouping[literalToVertice(i)] ==
		    scc.grouping[literalToVertice(-i)])
		    return false;
	    }
	    return true;
	}


    };

};

#endif
