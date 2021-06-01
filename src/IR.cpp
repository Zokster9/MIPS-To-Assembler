#include "IR.h"

bool Variable::operator==(const Variable* var)
{
	return this->m_name == var->m_name && this->m_position == var->m_position;
}

void Variable::set_position(int position)
{
	m_position = position;
}

void Variable::set_assignment(Regs reg)
{
	m_assignment = reg;
}

std::string Variable::get_name() const
{
	return m_name;
}

Variable::VariableType Variable::get_type()
{
	return m_type;
}

int Variable::get_position() const
{
	return m_position;
}

Regs Variable::get_assignment()
{
	return m_assignment;
}

ostream& operator<<(ostream& out, Variable* var)
{
	out << var->m_name << ":\t.word " << var->m_value << endl;
	return out;
}

bool variable_exists(Variable* var, Variables& vars)
{
	Variables::const_iterator it;
	for (it = vars.begin(); it != vars.end(); it++)
	{
		if ((*it) == var)
			return true;
	}
	return false;
}

bool variable_exists(std::string name, Variables& vars)
{
	Variables::const_iterator it;
	for (it = vars.begin(); it != vars.end(); it++)
	{
		if ((*it)->get_name() == name)
			return true;
	}
	return false;
}

void push_back_var(Variables& vars, Variable* var)
{
	if (!variable_exists(var, vars))
		vars.push_back(var);
}

int get_num_reg_vars(Variables& vars)
{
	Variables::const_iterator it;
	int counter = 0;
	for (it = vars.begin(); it != vars.end(); it++)
	{
		if ((*it)->get_type() == Variable::REG_VAR)
			counter++;
	}
	return counter;
}

int get_num_mem_vars(Variables& vars)
{
	Variables::const_iterator it;
	int counter = 0;
	for (it = vars.begin(); it != vars.end(); it++)
	{
		if ((*it)->get_type() == Variable::MEM_VAR)
			counter++;
	}
	return counter;
}

Variable* get_variable(int position, Variables* vars)
{
	Variables::const_iterator it;
	for (it = vars->begin(); it != vars->end(); it++)
	{
		if ((*it)->get_position() == position)
			return (*it);
	}
}

Variable* get_variable(std::string name, Variables& vars)
{
	Variables::const_iterator it;
	for (it = vars.begin(); it != vars.end(); it++)
	{
		if ((*it)->get_name() == name)
			return (*it);
	}
}

ostream& operator<<(ostream& out, Instruction* instruction)
{
	if (instruction->m_type == I_ADD)
	{
		Variable* dst_var = *instruction->m_dst.begin();

		Variables::const_iterator src_it = instruction->m_src.begin();
		Variable* src1_var = *(src_it++);
		Variable* src2_var = *src_it;

		out << "\tadd\t$t" << dst_var->get_assignment() - 1 << ", $t" << src1_var->get_assignment() - 1 << ", $t" << src2_var->get_assignment() - 1 << endl;
	}
	else if (instruction->m_type == I_LW)
	{
		Variable* dst_var = *instruction->m_dst.begin();
		Variable* src_var = *instruction->m_src.begin();

		out << "\tla\t$t" << dst_var->get_assignment() - 1 << ", " << instruction->m_const << "($t" << src_var->get_assignment() - 1 << ")" << endl;
	}
	else if (instruction->m_type == I_LA)
	{
		Variable* dst_var = *instruction->m_dst.begin();
		Variable* src_var = *instruction->m_src.begin();

		out << "\tlw\t$t" << dst_var->get_assignment() - 1 << ", " << src_var->get_name() << endl;
	}

	return out;
}

InstructionType Instruction::get_instruction_type()
{
	return m_type;
}

Variables Instruction::get_use()
{
	return m_use;
}

Variables Instruction::get_def()
{
	return m_def;
}

Variables Instruction::get_in()
{
	return m_in;
}

Variables Instruction::get_out()
{
	return m_out;
}

std::list<Instruction*> Instruction::get_succ()
{
	return m_succ;
}

void Instruction::set_in(Variables& in)
{
	m_in = in;
}

void Instruction::set_out(Variables& out)
{
	m_out = out;
}

void Instruction::add_pred(Instruction* instruction)
{
	m_pred.push_back(instruction);
}

void Instruction::add_succ(Instruction* instruction)
{
	m_succ.push_back(instruction);
}
