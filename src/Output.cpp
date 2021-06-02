#include "Output.h"
#include <fstream>
#include <iostream>

using namespace std;

void write(Instructions& instructions, Variables& variables, Function& f, Labels& labels)
{
	std::string fileName = ".\\..\\output\\proba.s";
	std::ofstream out(fileName);

	out << ".globl " << f.get_name() << endl << endl;
	out << ".data" << endl;

	int num_mem_vars = get_num_mem_vars(variables);

	Variables::const_iterator var_it = variables.begin();

	for (int i = 0; i < num_mem_vars; i++)
	{
		out << (*var_it);
		var_it++;
	}
	out << endl;

	out << ".text" << endl;
	out << f.get_name() << ":" << endl;

	Instructions::const_iterator instr_it;

	for (instr_it = instructions.begin(); instr_it != instructions.end(); instr_it++)
	{
		if (is_instruction_after_label(*instr_it, labels))
		{
			Label* label = new Label();
			label = get_label(*instr_it, labels);

			out << label;
		}

		out << *instr_it;
	}

	out.close();
}

bool is_instruction_after_label(Instruction* instruction, Labels& labels)
{
	Labels::iterator lab_it;

	for (lab_it = labels.begin(); lab_it != labels.end(); lab_it++)
	{
		Instruction* succ = (*lab_it)->get_succ_instruction();
		
		if (succ->get_position() == instruction->get_position())
		{
			return true;
		}
	}
	
	return false;
}

Label* get_label(Instruction* instruction, Labels& labels)
{
	Labels::iterator lab_it;

	for (lab_it = labels.begin(); lab_it != labels.end(); lab_it++)
	{
		Instruction* succ = (*lab_it)->get_succ_instruction();

		if (succ->get_position() == instruction->get_position())
		{
			return *lab_it;
		}
	}
}
