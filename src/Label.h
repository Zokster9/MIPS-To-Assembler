#pragma once
#include "IR.h"

class Label
{
public:
	Label() : m_name("") {}
	Label(string name) : m_name(name) {}

	string get_name();

	void add_pred(Instruction* instruction);

	void add_succ(Instruction* instruction);

	Instruction* get_succ_instruction();

	friend ostream& operator<<(ostream& out, Label* label);

private:
	string m_name;
	Instructions pred;
	Instructions succ;

};

/**
 * This type represents list of labels from program code.
 */
typedef list<Label*> Labels;

bool label_exists(Labels labels, string lab_name);

