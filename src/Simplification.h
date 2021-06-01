#pragma once
#include <stack>
#include "IR.h"
#include "InterferenceGraph.h"
#include "Constants.h"

void do_simplification(InterferenceGraph* interference_graph, stack<Variable*>* stack, int degree);
