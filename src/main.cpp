#include <iostream>
#include <exception>

#include "LexicalAnalysis.h"
#include "SyntaxAnalysis.h"
#include "IR.h"
#include "InstructionSelection.h"
#include "LivenessAnalysis.h"
#include "InterferenceGraph.h"
#include "Simplification.h"
#include "ResourceAllocation.h"

using namespace std;


int main()
{
	try
	{
		std::string fileName = ".\\..\\examples\\simple.mavn";
		bool retVal = false;

		LexicalAnalysis lex;

		if (!lex.readInputFile(fileName))
			throw runtime_error("\nException! Failed to open input file!\n");

		lex.initialize();

		retVal = lex.Do();

		if (retVal)
		{
			cout << "Lexical analysis finished successfully!" << endl;
			lex.printTokens();
		}
		else
		{
			lex.printLexError();
			throw runtime_error("\nException! Lexical analysis failed!\n");
		}

		SyntaxAnalysis syntax(lex);

		if (syntax.Do())
		{
			cout << "Syntax analysis finished successfully!" << endl;
		}
		else
		{
			cout << "Syntax analysis failed!" << endl;
		}

		Instructions instructions;

		Variables variables;

		fill_instruction_list(instructions, variables, lex.getTokenList());

		livenessAnalysis(instructions);

		InterferenceGraph interference_graph;

		build_interference_graph(interference_graph, instructions, get_num_reg_vars(variables));

		interference_graph.printInterferenceMatrix();

		stack<Variable*> stack;

		do_simplification(&interference_graph, &stack, __REG_NUMBER__);

		vector<Regs> regs;

		regs = get_regs();

		do_resource_allocation(&interference_graph, &stack, regs);
	}
	catch (runtime_error e)
	{
		cout << e.what() << endl;
		return 1;
	}

	return 0;
}
