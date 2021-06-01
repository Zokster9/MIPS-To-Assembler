#ifndef __RESOURCE_ALLOCATION__
#define __RESOURCE_ALLOCATION__

#include "IR.h"
#include "InterferenceGraph.h"

void do_resource_allocation(InterferenceGraph* interference_graph, std::stack<Variable*>* stack, vector<Regs>& regs);

vector<Regs> get_regs();

Regs operator++(Regs& r);

#endif

