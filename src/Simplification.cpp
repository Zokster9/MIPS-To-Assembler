#include "Simplification.h"

void do_simplification(InterferenceGraph* interference_graph, stack<Variable*>* stack, int degree)
{
	int max_rang = -1;
	int max_rang_position = 0;
	list<int> already_on_stack;

	InterferenceMatrix& matrix = interference_graph->get_matrix();

	for (int i = 0; i < matrix.size(); i++)
	{

		for (int j = 0; j < matrix.size(); j++)
		{
			int current_rang = 0;

			for (int k = 0; k < matrix[j].size(); k++)
			{
				if (matrix[j][k] == __INTERFERENCE__)
					current_rang++;
			}

			if (current_rang > max_rang && current_rang < degree)
			{
				if (std::find(already_on_stack.begin(), already_on_stack.end(), j) == already_on_stack.end())
				{
					max_rang = current_rang;
					max_rang_position = j;
				}
			}
		}
		
		if (max_rang == -1)
		{
			throw std::runtime_error("Spilling occurred");
		}

		max_rang = -1;

		Variable* var = new Variable();
		var = get_variable(max_rang_position, interference_graph->get_variables());
		already_on_stack.push_back(max_rang_position);
		stack->push(var);
	}
}