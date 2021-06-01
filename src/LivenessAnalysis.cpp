#include "LivenessAnalysis.h"

void livenessAnalysis(Instructions& instructions)
{
	bool doItAgain = true;

	while (doItAgain) {

		doItAgain = false;

		Instructions::reverse_iterator rit = instructions.rbegin();
		for (; rit != instructions.rend(); rit++) {
			Variables& out = (*rit)->get_out();
			Variables& in = (*rit)->get_in();
			Variables newIn;
			Variables newOut;

			Instructions& successors = (*rit)->get_succ();
			Instructions::iterator succIt = successors.begin();

			for (; succIt != successors.end(); succIt++) {
				Variables& succIn = (*succIt)->get_in();
				newOut.insert(newOut.end(), succIn.begin(), succIn.end());
			}
			newOut.sort();
			newOut.unique();

			Variables& use = (*rit)->get_use();
			Variables& def = (*rit)->get_def();

			Variables outMinusDef;
			Variables::iterator varIt = newOut.begin();
			for (; varIt != newOut.end(); varIt++) {
				if (!variable_exists(*varIt, def)) {
					outMinusDef.push_back(*varIt);
				}
			}

			newIn = use;
			newIn.insert(newIn.end(), outMinusDef.begin(), outMinusDef.end());
			newIn.sort();
			newIn.unique();

			if (newIn != in || newOut != out) {
				doItAgain = true;
			}

			(*rit)->set_in(newIn);
			(*rit)->set_out(newOut);

		}
	}
}
