#include "InstructionSelection.h"

void fill_instruction_list(Instructions& instructions, Variables& variables, TokenList& tokenList)
{
	TokenList::iterator it;
	int position = 0;
	
	for (it = tokenList.begin(); it != tokenList.end(); it++)
	{
		TokenType token_type = (*it).getType();
		if (token_type == T_MEM || token_type == T_REG)
		{
			add_variable(variables, token_type, it);
		}
		else if (token_type == T_ADD)
		{
			add_ADD_instruction(instructions, variables, it, position);
		}
		else if (token_type == T_LA)
		{
			add_LA_instruction(instructions, variables, it, position);
		}
		else if (token_type == T_LW)
		{
			add_LW_instruction(instructions, variables, it, position);
		}
		else if (token_type == T_ADDI)
		{
			add_ADDI_instruction(instructions, variables, it, position);
		}
		else if (token_type == T_B)
		{
			add_B_instruction(instructions, variables, it, position);
		}
		else if (token_type == T_BLTZ)
		{
			add_BLTZ_instruction(instructions, variables, it, position);
		}
		else if (token_type == T_LI)
		{
			add_LI_instruction(instructions, variables, it, position);
		}
		else if (token_type == T_NOP)
		{
			add_NOP_instruction(instructions);
		}
		else if (token_type == T_SUB)
		{
			add_SUB_instruction(instructions, variables, it, position);
		}
		else if (token_type == T_SW)
		{
			add_SW_instruction(instructions, variables, it, position);
		}
	}
}

void add_variable(Variables& variables, TokenType& token_type, TokenList::iterator it)
{
	it++;
	std::string name = (*it).getValue();
	Variable* var;
	switch (token_type)
	{
	case T_REG:
		var = new Variable(name, Variable::REG_VAR);
		break;
	default:
		it++;
		int value = std::stoi((*it).getValue());
		var = new Variable(name, value, Variable::MEM_VAR);
		break;
	}
	push_back_var(variables, var);
}

void add_ADD_instruction(Instructions& instructions, Variables& variables, TokenList::iterator it, int& position)
{
	Variables vars_dst;
	Variables vars_src;
	Variables use;
	Variables def;
	Instruction* pred_instr = new Instruction();

	it++;

	add_variable_to_instruction((*it).getValue(), variables, vars_dst, position);

	it++;
	it++;

	add_variable_to_instruction((*it).getValue(), variables, vars_src, position);

	it++;
	it++;

	add_variable_to_instruction((*it).getValue(), variables, vars_src, position);

	fill_def(def, vars_dst);
	fill_use(use, vars_src);

	Instruction* instr = new Instruction(instructions.size(), I_ADD, vars_dst, vars_src, use, def);

	if (instructions.size() != 0)
	{
		pred_instr = get_pred_instr(instructions);
		instr->add_pred(pred_instr);
		pred_instr->add_succ(instr);
	}

	instructions.push_back(instr);
}

void add_ADDI_instruction(Instructions& instructions, Variables& variables, TokenList::iterator it, int& position)
{
	Variables vars_dst;
	Variables vars_src;
	Variables use;
	Variables def;
	Instruction* pred_instr = new Instruction();

	it++;

	add_variable_to_instruction((*it).getValue(), variables, vars_dst, position);

	it++;
	it++;

	add_variable_to_instruction((*it).getValue(), variables, vars_src, position);

	it++;
	it++;

	fill_def(def, vars_dst);
	fill_use(use, vars_src);

	Instruction* instr = new Instruction(instructions.size(), I_ADDI, vars_dst, vars_src, use, def);

	if (instructions.size() != 0)
	{
		pred_instr = get_pred_instr(instructions);
		instr->add_pred(pred_instr);
		pred_instr->add_succ(instr);
	}

	instructions.push_back(instr);
}

void add_LA_instruction(Instructions& instructions, Variables& variables, TokenList::iterator it, int& position)
{
	Variables vars_dst;
	Variables vars_src;
	Variables use;
	Variables def;
	Instruction* pred_instr = new Instruction();

	it++;

	add_variable_to_instruction((*it).getValue(), variables, vars_dst, position);

	it++;
	it++;

	add_variable_to_instruction((*it).getValue(), variables, vars_src, position);

	fill_def(def, vars_dst);
	fill_use(use, vars_src);

	Instruction* instr = new Instruction(instructions.size(), I_LA, vars_dst, vars_src, use, def);

	if (instructions.size() != 0)
	{
		pred_instr = get_pred_instr(instructions);
		instr->add_pred(pred_instr);
		pred_instr->add_succ(instr);
	}

	instructions.push_back(instr);
}

void add_LW_instruction(Instructions& instructions, Variables& variables, TokenList::iterator it, int& position)
{
	Variables vars_dst;
	Variables vars_src;
	Variables use;
	Variables def;
	Instruction* pred_instr = new Instruction();

	it++;

	add_variable_to_instruction((*it).getValue(), variables, vars_dst, position);

	it++;
	it++;
	it++;
	it++;

	add_variable_to_instruction((*it).getValue(), variables, vars_src, position);

	fill_def(def, vars_dst);
	fill_use(use, vars_src);

	Instruction* instr = new Instruction(instructions.size(), I_LW, vars_dst, vars_src, use, def);

	if (instructions.size() != 0)
	{
		pred_instr = get_pred_instr(instructions);
		instr->add_pred(pred_instr);
		pred_instr->add_succ(instr);
	}

	instructions.push_back(instr);
}

void add_LI_instruction(Instructions& instructions, Variables& variables, TokenList::iterator it, int& position)
{
	Variables vars_dst;
	Variables vars_src;
	Variables use;
	Variables def;
	Instruction* pred_instr = new Instruction();

	it++;

	add_variable_to_instruction((*it).getValue(), variables, vars_dst, position);

	fill_def(def, vars_dst);
	fill_use(use, vars_src);

	Instruction* instr = new Instruction(instructions.size(), I_LI, vars_dst, vars_src, use, def);

	if (instructions.size() != 0)
	{
		pred_instr = get_pred_instr(instructions);
		instr->add_pred(pred_instr);
		pred_instr->add_succ(instr);
	}

	instructions.push_back(instr);
}

void add_B_instruction(Instructions& instructions, Variables& variables, TokenList::iterator it, int& position)
{
	Variables vars_dst;
	Variables vars_src;
	Variables use;
	Variables def;
	Instruction* pred_instr = new Instruction();

	it++;

	add_variable_to_instruction((*it).getValue(), variables, vars_dst, position);

	fill_def(def, vars_dst);
	fill_use(use, vars_src);

	Instruction* instr = new Instruction(instructions.size(), I_B, vars_dst, vars_src, use, def);

	if (instructions.size() != 0)
	{
		pred_instr = get_pred_instr(instructions);
		instr->add_pred(pred_instr);
		pred_instr->add_succ(instr);
	}

	instructions.push_back(instr);
}

void add_BLTZ_instruction(Instructions& instructions, Variables& variables, TokenList::iterator it, int& position)
{
	Variables vars_dst;
	Variables vars_src;
	Variables use;
	Variables def;
	Instruction* pred_instr = new Instruction();

	it++;

	add_variable_to_instruction((*it).getValue(), variables, vars_dst, position);

	it++;
	it++;

	add_variable_to_instruction((*it).getValue(), variables, vars_src, position);

	fill_def(def, vars_dst);
	fill_use(use, vars_src);

	Instruction* instr = new Instruction(instructions.size(), I_BLTZ, vars_dst, vars_src, use, def);

	if (instructions.size() != 0)
	{
		pred_instr = get_pred_instr(instructions);
		instr->add_pred(pred_instr);
		pred_instr->add_succ(instr);
	}

	instructions.push_back(instr);
}

void add_NOP_instruction(Instructions& instructions)
{
	Variables vars_dst;
	Variables vars_src;
	Variables use;
	Variables def;

	Instruction* instr = new Instruction(instructions.size(), I_NOP, vars_dst, vars_src);
	instructions.push_back(instr);
}

void add_SUB_instruction(Instructions& instructions, Variables& variables, TokenList::iterator it, int& position)
{
	Variables vars_dst;
	Variables vars_src;
	Variables use;
	Variables def;
	Instruction* pred_instr = new Instruction();

	it++;

	add_variable_to_instruction((*it).getValue(), variables, vars_dst, position);

	it++;
	it++;

	add_variable_to_instruction((*it).getValue(), variables, vars_src, position);

	it++;
	it++;

	add_variable_to_instruction((*it).getValue(), variables, vars_src, position);

	fill_def(def, vars_dst);
	fill_use(use, vars_src);

	Instruction* instr = new Instruction(instructions.size(), I_SUB, vars_dst, vars_src, use, def);

	if (instructions.size() != 0)
	{
		pred_instr = get_pred_instr(instructions);
		instr->add_pred(pred_instr);
		pred_instr->add_succ(instr);
	}

	instructions.push_back(instr);
}

void add_SW_instruction(Instructions& instructions, Variables& variables, TokenList::iterator it, int& position)
{
	Variables vars_dst;
	Variables vars_src;
	Variables use;
	Variables def;
	Instruction* pred_instr = new Instruction();

	it++;

	add_variable_to_instruction((*it).getValue(), variables, vars_dst, position);

	it++;
	it++;
	it++;
	it++;

	add_variable_to_instruction((*it).getValue(), variables, vars_src, position);

	fill_def(def, vars_dst);
	fill_use(use, vars_src);

	Instruction* instr = new Instruction(instructions.size(), I_SW, vars_dst, vars_src, use, def);

	if (instructions.size() != 0)
	{
		pred_instr = get_pred_instr(instructions);
		instr->add_pred(pred_instr);
		pred_instr->add_succ(instr);
	}

	instructions.push_back(instr);
}

void add_variable_to_instruction(std::string name, Variables& vars, Variables& instr_vars, int& position)
{
	if (variable_exists(name, vars))
	{
		Variable* dst = get_variable(name, vars);
		if (dst->get_type() == Variable::REG_VAR)
			set_variable_position(dst, position);
		instr_vars.push_back(dst);
	}
}

void set_variable_position(Variable* var, int& position)
{
	if (var->get_position() == -1)
		var->set_position(position++);
}

void fill_def(Variables& def, Variables& dst)
{
	Variables::const_iterator it;
	for (it = dst.begin(); it != dst.end(); it++)
	{
		def.push_back((*it));
	}
}

void fill_use(Variables& use, Variables& src)
{
	Variables::const_iterator it;
	for (it = src.begin(); it != src.end(); it++)
	{
		if ((*it)->get_type() != Variable::MEM_VAR)
			use.push_back(*it);
	}
}

Instruction* get_pred_instr(Instructions& instructions)
{
	Instructions::const_reverse_iterator rit;
	rit = instructions.rbegin();
	if ((*rit)->get_instruction_type() != I_B || (*rit)->get_instruction_type() != I_BLTZ)
	{
		return (*rit);
	}
	return nullptr;
}
