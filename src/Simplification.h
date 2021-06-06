#pragma once

/* Autor: Zoran Bukorac
Datum: 06.06.2021. */

#include "IR.h"
#include "InterferenceGraph.h"

void do_simplification(InterferenceGraph* interference_graph, stack<Variable*>* stack, int degree);
