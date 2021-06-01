#include "IR.h"

bool Variable::operator==(const Variable* var)
{
	return this->m_name == var->m_name && this->m_position == var->m_position;
}

void Variable::set_position(int position)
{
	m_position = position;
}

void Variable::set_assignment(Regs& reg)
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

Variable* get_variable(std::string name, Variables& vars)
{
	Variables::const_iterator it;
	for (it = vars.begin(); it != vars.end(); it++)
	{
		if ((*it)->get_name() == name)
			return (*it);
	}
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
