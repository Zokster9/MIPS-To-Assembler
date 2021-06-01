#ifndef __IR__
#define __IR__

#include "Types.h"


/**
 * This class represents one variable from program code.
 */
class Variable
{
public:
	enum VariableType
	{
		MEM_VAR,
		REG_VAR,
		NO_TYPE
	};

	Variable() : m_type(NO_TYPE), m_name(""), m_position(-1), m_assignment(no_assign), m_value(-1) {}
	Variable(std::string name, int pos) : m_type(NO_TYPE), m_name(name), m_position(pos), m_assignment(no_assign), m_value(-1) {}
	Variable(std::string name, int val, VariableType type) : m_type(type), m_name(name), m_position(-1), m_assignment(no_assign), m_value(val) {}
	Variable(std::string name, VariableType type) : m_type(type), m_name(name), m_position(-1), m_assignment(no_assign), m_value(-1) {}
	bool operator==(const Variable* var);
	void set_position(int position);
	void set_assignment(Regs reg);
	std::string get_name() const;
	VariableType get_type();
	int get_position() const;
	Regs get_assignment();

private:
	VariableType m_type;
	std::string m_name;
	int m_value;
	int m_position;
	Regs m_assignment;
};


/**
 * This type represents list of variables from program code.
 */
typedef std::list<Variable*> Variables;

bool variable_exists(Variable* var, Variables& vars);

bool variable_exists(std::string name, Variables& vars);

void push_back_var(Variables& vars, Variable* var);

int get_num_reg_vars(Variables& vars);

Variable* get_variable(int position, Variables* vars);

Variable* get_variable(std::string name, Variables& vars);


/**
 * This class represents one instruction in program code.
 */
class Instruction
{
public:
	Instruction () : m_position(0), m_type(I_NO_TYPE) {}
	Instruction (int pos, InstructionType type, Variables& dst, Variables& src) :
		m_position(pos), m_type(type), m_dst(dst), m_src(src) {}
	Instruction(int pos, InstructionType type, Variables& dst, Variables& src, Variables& use, Variables& def) :
		m_position(pos), m_type(type), m_dst(dst), m_src(src), m_use(use), m_def(def) {}

	InstructionType get_instruction_type();
	Variables get_use();
	Variables get_def();
	Variables get_in();
	Variables get_out();
	std::list<Instruction*> get_succ();

	void set_in(Variables& in);
	void set_out(Variables& out);

	void add_pred(Instruction* instruction);
	void add_succ(Instruction* instruction);

private:
	int m_position;
	InstructionType m_type;
	
	Variables m_dst;
	Variables m_src;

	Variables m_use;
	Variables m_def;
	Variables m_in;
	Variables m_out;
	std::list<Instruction*> m_succ;
	std::list<Instruction*> m_pred;
};


/**
 * This type represents list of instructions from program code.
 */
typedef std::list<Instruction*> Instructions;

#endif
