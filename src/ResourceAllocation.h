#ifndef __RESOURCE_ALLOCATION__
#define __RESOURCE_ALLOCATION__

/* Autor: Zoran Bukorac
Datum: 06.06.2021. */

#include "IR.h"
#include "InterferenceGraph.h"

void do_resource_allocation(InterferenceGraph* interference_graph, std::stack<Variable*>* stack, vector<Regs>& regs);

vector<Regs> get_regs(int reg_num);

Regs operator++(Regs& r);

#endif

