#include "Label.h"

string Label::get_name()
{
	return m_name;
}

void Label::add_pred(Instruction* instruction)
{
	pred.push_back(instruction);
}

void Label::add_succ(Instruction* instruction)
{
	succ.push_back(instruction);
}

Instruction* Label::get_succ_instruction()
{
	return (*succ.begin());
}

ostream& operator<<(ostream& out, Label* label)
{
	out << label->m_name << ":" << endl;
	return out;
}

bool label_exists(Labels labels, string lab_name)
{
	Labels::const_iterator it;

	for (it = labels.begin(); it != labels.end(); it++)
	{
		if ((*it)->get_name() == lab_name)
			return true;
	}

	return false;
}
