#pragma once
#include "IR.h"
#include "InterferenceGraph.h"

void do_simplification(InterferenceGraph* interference_graph, stack<Variable*>* stack, int degree);
