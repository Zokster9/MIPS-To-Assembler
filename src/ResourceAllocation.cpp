#include "ResourceAllocation.h"

void do_resource_allocation(InterferenceGraph* interference_graph, std::stack<Variable*>* stack, vector<Regs>& regs)
{
	InterferenceMatrix matrix = interference_graph->get_matrix();

	while (!stack->empty())
	{
		list<int> already_taken_reg;
		Variable* var = new Variable();
		var = stack->top();
		stack->pop();
		int position = var->get_position();

		for (int i = 0; i < matrix[position].size(); i++)
		{
			if (matrix[position][i] == __INTERFERENCE__)
			{
				Variable* neighbour_var = get_variable(i, interference_graph->get_variables());
				int neighbour_reg = neighbour_var->get_assignment();

				already_taken_reg.push_back(neighbour_reg);
			}
		}

		for (Regs reg : regs)
		{
			if (std::find(already_taken_reg.begin(), already_taken_reg.end(), reg) == already_taken_reg.end())
			{
				var->set_assignment(reg);
				break;
			}
		}
	}
}

vector<Regs> get_regs()
{
	vector<Regs> regs;

	for (Regs r = t0; r != __REG_NUMBER__ + 1; ++r)
	{
		regs.push_back(r);
	}
	return regs;
}

Regs operator++(Regs& r)
{
	r = Regs(static_cast<std::underlying_type<Regs>::type>(r) + 1);
	return r;
}
