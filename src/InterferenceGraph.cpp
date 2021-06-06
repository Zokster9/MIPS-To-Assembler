/* Autor: Zoran Bukorac
Datum: 06.06.2021. */

#include "InterferenceGraph.h"
#include <iostream>

std::vector<std::vector<int>>& InterferenceGraph::get_matrix()
{
	return m_matrix;
}

Variables* InterferenceGraph::get_variables()
{
	return m_variables;
}

void InterferenceGraph::set_variables(Variables* variables)
{
	m_variables = variables;
}

void InterferenceGraph::add_matrix_row(vector<int>& row)
{
	m_matrix.push_back(row);
}

void InterferenceGraph::printInterferenceMatrix()
{
	if (m_matrix.size() == 0)
	{
		cout << "There is nothing to print!" << endl;
		return;
	}

	cout << "==========================================" << endl;
	cout << "Interference matrix:" << endl;
	cout << "==========================================" << endl;

	// print existing variables in order to mark rows and columns
	for (auto varIt = m_variables->begin(); varIt != m_variables->end(); varIt++)
	{
		cout << "\t" << (*varIt)->get_name();
	}
	cout << endl;

	auto varIt = m_variables->begin();
	for (auto it1 = m_matrix.begin(); it1 != m_matrix.end(); it1++)
	{
		cout << (*varIt++)->get_name();
		for (auto it2 = (*it1).begin(); it2 != (*it1).end(); it2++)
		{
			cout << "\t" << *it2;
		}
		cout << endl;
	}
	cout << "==========================================" << endl;
}

void build_interference_graph(InterferenceGraph& interference_graph, Instructions& instructions, int matrix_size)
{
	Variables* variables = new Variables();
	InterferenceMatrix matrix(matrix_size);

	Instructions::const_iterator instr_it;

	for (instr_it = instructions.begin(); instr_it != instructions.end(); instr_it++)
	{
		if ((*instr_it)->get_instruction_type() != InstructionType::I_NO_TYPE)
		{
			Variables::const_iterator def_var_it;
			Variables& def = (*instr_it)->get_def();

			for (def_var_it = def.begin(); def_var_it != def.end(); def_var_it++)
			{
				variables->push_back((*def_var_it));
				vector<int> def_interferences;

				if (matrix[(*def_var_it)->get_position()].size() != 0)
					def_interferences = matrix[(*def_var_it)->get_position()];

				Variables::const_iterator out_var_it;
				Variables& out = (*instr_it)->get_out();

				for (out_var_it = out.begin(); out_var_it != out.end(); out_var_it++)
				{
					if ((*def_var_it)->get_name() != (*out_var_it)->get_name())
					{
						variables->push_back((*out_var_it));

						if (!interference_graph_exists(def_interferences, (*out_var_it)->get_position()))
							def_interferences.push_back((*out_var_it)->get_position());

						vector<int> out_interferences;

						if (matrix[(*out_var_it)->get_position()].size() != 0)
							out_interferences = matrix[(*out_var_it)->get_position()];

						if (!interference_graph_exists(out_interferences, (*def_var_it)->get_position()))
							out_interferences.push_back((*def_var_it)->get_position());

						matrix[(*out_var_it)->get_position()] = out_interferences;
					}
				}
				matrix[(*def_var_it)->get_position()] = def_interferences;
			}
		}
	}

	variables->sort(compare_variable_positions);
	variables->unique();

	interference_graph.set_variables(variables);

	InterferenceMatrix::iterator interference_matrix_it;

	for (interference_matrix_it = matrix.begin(); interference_matrix_it != matrix.end(); interference_matrix_it++)
	{
		vector<int> interference;

		for (int i = 0; i < variables->size(); i++)
		{
			if (interference_graph_exists((*interference_matrix_it), i))
			{
				interference.push_back(__INTERFERENCE__);
			}
			else
			{
				interference.push_back(__EMPTY__);
			}
		}
		interference_graph.add_matrix_row(interference);
	}
}

bool interference_graph_exists(vector<int>& interferences, int position)
{
	for (int i = 0; i < interferences.size(); i++)
	{
		if (position == interferences[i])
			return true;
	}
	return false;
}

bool compare_variable_positions(const Variable* v1, const Variable* v2) {
	return v1->get_position() < v2->get_position();
}
