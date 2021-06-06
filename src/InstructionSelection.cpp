/* Autor: Zoran Bukorac
Datum: 06.06.2021. */

#include "InstructionSelection.h"


// prolazi se kroz token listu i pune se liste varijabli i instrukcija
void fill_instruction_list(Instructions& instructions, Variables& variables, TokenList& tokenList, Labels& labels)
{
	TokenList::iterator it;

	//pozicija za registarsku varijablu
	int position = 0;

	Token previousToken;

	bool has_neighbour_label = false;

	string lab_name;
	
	for (it = tokenList.begin(); it != tokenList.end(); it++)
	{
		TokenType token_type = (*it).getType();

		// gleda se da li instrukciji prethodi labela
		if (previousToken.getType() == T_ID && token_type == T_COL)
		{
			lab_name = previousToken.getValue();
			has_neighbour_label = true;
		}

		if (token_type == T_MEM || token_type == T_REG)
		{
			add_variable(variables, token_type, it);
		}
		else if (token_type == T_ADD)
		{
			add_ADD_instruction(instructions, variables, it, position, labels, has_neighbour_label, lab_name);
		}
		else if (token_type == T_LA)
		{
			add_LA_instruction(instructions, variables, it, position, labels, has_neighbour_label, lab_name);
		}
		else if (token_type == T_LW)
		{
			add_LW_instruction(instructions, variables, it, position, labels, has_neighbour_label, lab_name);
		}
		else if (token_type == T_ADDI)
		{
			add_ADDI_instruction(instructions, variables, it, position, labels, has_neighbour_label, lab_name);
		}
		else if (token_type == T_B)
		{
			add_B_instruction(instructions, variables, it, position, labels, has_neighbour_label, lab_name);
		}
		else if (token_type == T_BLTZ)
		{
			add_BLTZ_instruction(instructions, variables, it, position, labels, has_neighbour_label, lab_name);
		}
		else if (token_type == T_LI)
		{
			add_LI_instruction(instructions, variables, it, position, labels, has_neighbour_label, lab_name);
		}
		else if (token_type == T_NOP)
		{
			add_NOP_instruction(instructions, position, labels, has_neighbour_label, lab_name);
		}
		else if (token_type == T_SUB)
		{
			add_SUB_instruction(instructions, variables, it, position, labels, has_neighbour_label, lab_name);
		}
		else if (token_type == T_SW)
		{
			add_SW_instruction(instructions, variables, it, position, labels, has_neighbour_label, lab_name);
		}
		else if (token_type == T_DIV)
		{
			add_DIV_instruction(instructions, variables, it, position, labels, has_neighbour_label, lab_name);
		}
		else if (token_type == T_NOT)
		{
			add_NOT_instruction(instructions, variables, it, position, labels, has_neighbour_label, lab_name);
		}
		else if (token_type == T_SEQ)
		{
			add_SEQ_instruction(instructions, variables, it, position, labels, has_neighbour_label, lab_name);
		}

		if (previousToken.getType() == T_COL)
		{
			has_neighbour_label = false;
		}

		previousToken = *it;
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

void add_ADD_instruction(Instructions& instructions, Variables& variables, TokenList::iterator it, int& position, Labels& labels, bool has_neighbour_label, string lab_name)
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

	// postavljaju se naslednici i prethodnici instrukcije ako prethodna instrukcija nije bezuslovni skok
	if (instructions.size() != 0)
	{
		pred_instr = get_pred_instr(instructions);

		if (pred_instr->get_instruction_type() != I_B)
		{
			instr->add_pred(pred_instr);
			pred_instr->add_succ(instr);
		}
	}

	if (has_neighbour_label)
	{
		// ako labela postoji postavljaju se prethodnici i naslednici labele
		if (label_exists(labels, lab_name))
			add_instruction_to_label(instr, pred_instr, lab_name, labels);
		else
			throw runtime_error("Label is not defined!");
	}

	instructions.push_back(instr);
}

void add_ADDI_instruction(Instructions& instructions, Variables& variables, TokenList::iterator it, int& position, Labels& labels, bool has_neighbour_label, string lab_name)
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

	string const_ = (*it).getValue();

	fill_def(def, vars_dst);
	fill_use(use, vars_src);

	Instruction* instr = new Instruction(instructions.size(), I_ADDI, vars_dst, vars_src, const_, use, def);

	if (instructions.size() != 0)
	{
		pred_instr = get_pred_instr(instructions);

		if (pred_instr->get_instruction_type() != I_B)
		{
			instr->add_pred(pred_instr);
			pred_instr->add_succ(instr);
		}
	}

	instructions.push_back(instr);

	if (has_neighbour_label)
	{
		if (label_exists(labels, lab_name))
			add_instruction_to_label(instr, pred_instr, lab_name, labels);
		else
			throw runtime_error("Label is not defined!");
	}
}

void add_LA_instruction(Instructions& instructions, Variables& variables, TokenList::iterator it, int& position, Labels& labels, bool has_neighbour_label, string lab_name)
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

		if (pred_instr->get_instruction_type() != I_B)
		{
			instr->add_pred(pred_instr);
			pred_instr->add_succ(instr);
		}
	}

	if (has_neighbour_label)
	{
		if (label_exists(labels, lab_name))
			add_instruction_to_label(instr, pred_instr, lab_name, labels);
		else
			throw runtime_error("Label is not defined!");
	}

	instructions.push_back(instr);
}

void add_LW_instruction(Instructions& instructions, Variables& variables, TokenList::iterator it, int& position, Labels& labels, bool has_neighbour_label, string lab_name)
{
	Variables vars_dst;
	Variables vars_src;
	Variables use;
	Variables def;
	string const_;
	Instruction* pred_instr = new Instruction();

	it++;

	add_variable_to_instruction((*it).getValue(), variables, vars_dst, position);

	it++;
	it++;
	const_ = (*it).getValue();
	it++;
	it++;

	add_variable_to_instruction((*it).getValue(), variables, vars_src, position);

	fill_def(def, vars_dst);
	fill_use(use, vars_src);

	Instruction* instr = new Instruction(instructions.size(), I_LW, vars_dst, vars_src, const_, use, def);

	if (instructions.size() != 0)
	{
		pred_instr = get_pred_instr(instructions);

		if (pred_instr->get_instruction_type() != I_B)
		{
			instr->add_pred(pred_instr);
			pred_instr->add_succ(instr);
		}
	}

	if (has_neighbour_label)
	{
		if (label_exists(labels, lab_name))
			add_instruction_to_label(instr, pred_instr, lab_name, labels);
		else
			throw runtime_error("Label is not defined!");
	}

	instructions.push_back(instr);
}

void add_LI_instruction(Instructions& instructions, Variables& variables, TokenList::iterator it, int& position, Labels& labels, bool has_neighbour_label, string lab_name)
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

	string const_ = (*it).getValue();

	fill_def(def, vars_dst);
	fill_use(use, vars_src);

	Instruction* instr = new Instruction(instructions.size(), I_LI, vars_dst, vars_src, const_, use, def);

	if (instructions.size() != 0)
	{
		pred_instr = get_pred_instr(instructions);

		if (pred_instr->get_instruction_type() != I_B)
		{
			instr->add_pred(pred_instr);
			pred_instr->add_succ(instr);
		}
	}

	if (has_neighbour_label)
	{
		if (label_exists(labels, lab_name))
			add_instruction_to_label(instr, pred_instr, lab_name, labels);
		else
			throw runtime_error("Label is not defined!");
	}

	instructions.push_back(instr);
}

void add_B_instruction(Instructions& instructions, Variables& variables, TokenList::iterator it, int& position, Labels& labels, bool has_neighbour_label, string lab_name)
{
	Instruction* pred_instr = new Instruction();

	it++;

	string jump_label = (*it).getValue();

	Instruction* instr = new Instruction(instructions.size(), I_B, jump_label);

	if (instructions.size() != 0)
	{
		pred_instr = get_pred_instr(instructions);

		if (pred_instr->get_instruction_type() != I_B)
		{
			instr->add_pred(pred_instr);
			pred_instr->add_succ(instr);
		}
	}

	if (has_neighbour_label)
	{
		if (label_exists(labels, lab_name))
			add_instruction_to_label(instr, pred_instr, lab_name, labels);
		else
			throw runtime_error("Label is not defined!");
	}

	instructions.push_back(instr);
}

void add_BLTZ_instruction(Instructions& instructions, Variables& variables, TokenList::iterator it, int& position, Labels& labels, bool has_neighbour_label, string lab_name)
{
	Variables vars_dst;
	Variables vars_src;
	Variables use;
	Variables def;
	Instruction* pred_instr = new Instruction();

	it++;

	add_variable_to_instruction((*it).getValue(), variables, vars_src, position);

	it++;
	it++;
	
	string jump_label = (*it).getValue();

	fill_use(use, vars_src);

	Instruction* instr = new Instruction(instructions.size(), I_BLTZ, vars_dst, vars_src, use, def, jump_label);

	if (instructions.size() != 0)
	{
		pred_instr = get_pred_instr(instructions);

		if (pred_instr->get_instruction_type() != I_B)
		{
			instr->add_pred(pred_instr);
			pred_instr->add_succ(instr);
		}
	}

	if (has_neighbour_label)
	{
		if (label_exists(labels, lab_name))
			add_instruction_to_label(instr, pred_instr, lab_name, labels);
		else
			throw runtime_error("Label is not defined!");
	}

	instructions.push_back(instr);
}

void add_NOP_instruction(Instructions& instructions, int& position, Labels& labels, bool has_neighbour_label, string lab_name)
{
	Instruction* instr = new Instruction(instructions.size(), I_NOP);

	Instruction* pred_instr = new Instruction();

	if (instructions.size() != 0)
	{
		pred_instr = get_pred_instr(instructions);

		if (pred_instr->get_instruction_type() != I_B)
		{
			instr->add_pred(pred_instr);
			pred_instr->add_succ(instr);
		}
	}

	if (has_neighbour_label)
	{
		if (label_exists(labels, lab_name))
			add_instruction_to_label(instr, pred_instr, lab_name, labels);
		else
			throw runtime_error("Label is not defined!");
	}

	instructions.push_back(instr);
}

void add_SUB_instruction(Instructions& instructions, Variables& variables, TokenList::iterator it, int& position, Labels& labels, bool has_neighbour_label, string lab_name)
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

		if (pred_instr->get_instruction_type() != I_B)
		{
			instr->add_pred(pred_instr);
			pred_instr->add_succ(instr);
		}
	}

	if (has_neighbour_label)
	{
		if (label_exists(labels, lab_name))
			add_instruction_to_label(instr, pred_instr, lab_name, labels);
		else
			throw runtime_error("Label is not defined!");
	}

	instructions.push_back(instr);
}

void add_SW_instruction(Instructions& instructions, Variables& variables, TokenList::iterator it, int& position, Labels& labels, bool has_neighbour_label, string lab_name)
{
	Variables vars_dst;
	Variables vars_src;
	Variables use;
	Variables def;
	Instruction* pred_instr = new Instruction();

	it++;

	add_variable_to_instruction((*it).getValue(), variables, vars_src, position);

	it++;
	it++;

	string const_ = (*it).getValue();

	it++;
	it++;

	add_variable_to_instruction((*it).getValue(), variables, vars_dst, position);

	fill_def(def, vars_dst);
	fill_use(use, vars_src);

	Instruction* instr = new Instruction(instructions.size(), I_SW, vars_dst, vars_src, const_, use, def);

	if (instructions.size() != 0)
	{
		pred_instr = get_pred_instr(instructions);

		if (pred_instr->get_instruction_type() != I_B)
		{
			instr->add_pred(pred_instr);
			pred_instr->add_succ(instr);
		}
	}

	if (has_neighbour_label)
	{
		if (label_exists(labels, lab_name))
			add_instruction_to_label(instr, pred_instr, lab_name, labels);
		else
			throw runtime_error("Label is not defined!");
	}

	instructions.push_back(instr);
}

void add_DIV_instruction(Instructions& instructions, Variables& variables, TokenList::iterator it, int& position, Labels& labels, bool has_neighbour_label, string lab_name)
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

	Instruction* instr = new Instruction(instructions.size(), I_DIV, vars_dst, vars_src, use, def);

	if (instructions.size() != 0)
	{
		pred_instr = get_pred_instr(instructions);

		if (pred_instr->get_instruction_type() != I_B)
		{
			instr->add_pred(pred_instr);
			pred_instr->add_succ(instr);
		}
	}

	if (has_neighbour_label)
	{
		if (label_exists(labels, lab_name))
			add_instruction_to_label(instr, pred_instr, lab_name, labels);
		else
			throw runtime_error("Label is not defined!");
	}

	instructions.push_back(instr);
}

void add_NOT_instruction(Instructions& instructions, Variables& variables, TokenList::iterator it, int& position, Labels& labels, bool has_neighbour_label, string lab_name)
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

	Instruction* instr = new Instruction(instructions.size(), I_NOT, vars_dst, vars_src, use, def);

	if (instructions.size() != 0)
	{
		pred_instr = get_pred_instr(instructions);

		if (pred_instr->get_instruction_type() != I_B)
		{
			instr->add_pred(pred_instr);
			pred_instr->add_succ(instr);
		}
	}

	if (has_neighbour_label)
	{
		if (label_exists(labels, lab_name))
			add_instruction_to_label(instr, pred_instr, lab_name, labels);
		else
			throw runtime_error("Label is not defined!");
	}

	instructions.push_back(instr);
}

void add_SEQ_instruction(Instructions& instructions, Variables& variables, TokenList::iterator it, int& position, Labels& labels, bool has_neighbour_label, string lab_name)
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

	Instruction* instr = new Instruction(instructions.size(), I_SEQ, vars_dst, vars_src, use, def);

	if (instructions.size() != 0)
	{
		pred_instr = get_pred_instr(instructions);

		if (pred_instr->get_instruction_type() != I_B)
		{
			instr->add_pred(pred_instr);
			pred_instr->add_succ(instr);
		}
	}

	if (has_neighbour_label)
	{
		if (label_exists(labels, lab_name))
			add_instruction_to_label(instr, pred_instr, lab_name, labels);
		else
			throw runtime_error("Label is not defined!");
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
	else
	{
		throw runtime_error("Variable does not exist!");
	}
}

void add_instruction_to_label(Instruction* instr, Instruction* pred_instr, string lab_name, Labels& labels)
{
	Labels::iterator lab_it;

	for (lab_it = labels.begin(); lab_it != labels.end(); lab_it++)
	{
		string name = (*lab_it)->get_name();
		if (name == lab_name)
		{
			(*lab_it)->add_succ(instr);
			(*lab_it)->add_pred(pred_instr);
			break;
		}
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
	return (*rit);
}

// dodaju se naslednici branch instrukcijama
void set_branch_relations(Instructions& instructions, Labels& labels)
{
	Instructions::iterator instruction_it;

	for (instruction_it = instructions.begin(); instruction_it != instructions.end(); instruction_it++)
	{
		if ((*instruction_it)->get_instruction_type() == I_B || (*instruction_it)->get_instruction_type() == I_BLTZ)
		{
			add_branch_succ((*instruction_it), labels);
		}
	}
}

void add_branch_succ(Instruction* instruction, Labels& labels)
{
	Labels::iterator label_it;

	for (label_it = labels.begin(); label_it != labels.end(); label_it++)
	{
		if ((*label_it)->get_name() == instruction->get_label_name())
		{
			Instruction* succ = new Instruction();
			succ = (*label_it)->get_succ_instruction();
			if (!is_instruction_pred(succ->get_pred(), instruction))
			{
				instruction->add_succ(succ);
				succ->add_pred(instruction);
			}
		}
	}
}

// provera da li je instrukcija vec postavljena kao prethodnik
bool is_instruction_pred(Instructions& instructions, Instruction* instruction)
{
	Instructions::iterator instruction_it;

	for (instruction_it = instructions.begin(); instruction_it != instructions.end(); instruction_it++)
	{
		if ((*instruction_it)->get_position() == instruction->get_position())
			return true;
	}
}
