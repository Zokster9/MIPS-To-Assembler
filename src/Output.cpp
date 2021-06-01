#include "Output.h"
#include <fstream>
#include <iostream>

using namespace std;

void write(Instructions& instructions, Variables& variables, Function& f)
{
	std::string fileName = ".\\..\\output\\multiply.s";
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
		out << *instr_it;
	}

	out.close();
}
