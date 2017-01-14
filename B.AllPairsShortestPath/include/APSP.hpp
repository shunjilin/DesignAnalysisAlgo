//Copyright 2017 <Shunji Lin>

#ifndef APSP_HPP
#define APSP_HPP

#include "JohnsonsAlgo.hpp"

using namespace johnsonsalgo;

namespace apsp {
    int APSPCost(Graph graph) {
	JohnsonsAlgo johnsonsalgo = JohnsonsAlgo(graph);
	johnsonsalgo.preprocess();
	if (johnsonsalgo.hasNegativeCycle()) {
	    return INFTY;
	}
	return johnsonsalgo.APSPCost();
    }

};
#endif
