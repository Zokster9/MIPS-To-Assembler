/* Autor: Zoran Bukorac
Datum: 06.06.2021. */

#include "LivenessAnalysis.h"

void livenessAnalysis(Instructions& instructions)
{
	bool iterate = false;
	do {

		iterate = false;

		Instructions::reverse_iterator rit;
		for (rit = instructions.rbegin(); rit != instructions.rend(); rit++) {
			Variables& out = (*rit)->get_out();
			Variables& in = (*rit)->get_in();
			Variables newIn;
			Variables newOut;

			Instructions& successors = (*rit)->get_succ();
			Instructions::iterator succIt;

			for (succIt = successors.begin(); succIt != successors.end(); succIt++) {
				Variables& succIn = (*succIt)->get_in();
				newOut.insert(newOut.end(), succIn.begin(), succIn.end());
			}
			newOut.sort();
			newOut.unique();

			Variables& use = (*rit)->get_use();
			Variables& def = (*rit)->get_def();

			Variables outMinusDef;
			Variables::iterator varIt;
			for (varIt = newOut.begin(); varIt != newOut.end(); varIt++) {
				if (!variable_exists(*varIt, def)) {
					outMinusDef.push_back(*varIt);
				}
			}

			newIn = use;
			newIn.insert(newIn.end(), outMinusDef.begin(), outMinusDef.end());
			newIn.sort();
			newIn.unique();

			if (newIn != in || newOut != out) {
				iterate = true;
			}

			(*rit)->set_in(newIn);
			(*rit)->set_out(newOut);

		}
	} while (iterate);
}
