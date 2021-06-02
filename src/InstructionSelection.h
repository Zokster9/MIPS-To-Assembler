#pragma once
#include "IR.h"
#include "Token.h"
#include "LexicalAnalysis.h"
#include "Label.h"

void fill_instruction_list(Instructions& instructions, Variables& variables, TokenList& tokenList, Labels& labels);

void add_variable(Variables& variables, TokenType& token_type, TokenList::iterator it);

void add_ADD_instruction(Instructions& instructions, Variables& variables, TokenList::iterator it, int& position, Labels& labels, bool has_neighbour_label, string lab_name);

void add_ADDI_instruction(Instructions& instructions, Variables& variables, TokenList::iterator it, int& position, Labels& labels, bool has_neighbour_label, string lab_name);

void add_LA_instruction(Instructions& instructions, Variables& variables, TokenList::iterator it, int& position, Labels& labels, bool has_neighbour_label, string lab_name);

void add_LW_instruction(Instructions& instructions, Variables& variables, TokenList::iterator it, int& position, Labels& labels, bool has_neighbour_label, string lab_name);

void add_LI_instruction(Instructions& instructions, Variables& variables, TokenList::iterator it, int& position, Labels& labels, bool has_neighbour_label, string lab_name);

void add_B_instruction(Instructions& instructions, Variables& variables, TokenList::iterator it, int& position, Labels& labels, bool has_neighbour_label, string lab_name);

void add_BLTZ_instruction(Instructions& instructions, Variables& variables, TokenList::iterator it, int& position, Labels& labels, bool has_neighbour_label, string lab_name);

void add_NOP_instruction(Instructions& instructions, int& position, Labels& labels, bool has_neighbour_label, string lab_name);

void add_SUB_instruction(Instructions& instructions, Variables& variables, TokenList::iterator it, int& position, Labels& labels, bool has_neighbour_label, string lab_name);

void add_SW_instruction(Instructions& instructions, Variables& variables, TokenList::iterator it, int& position, Labels& labels, bool has_neighbour_label, string lab_name);

void add_DIV_instruction(Instructions& instructions, Variables& variables, TokenList::iterator it, int& position, Labels& labels, bool has_neighbour_label, string lab_name);

void add_NOT_instruction(Instructions& instructions, Variables& variables, TokenList::iterator it, int& position, Labels& labels, bool has_neighbour_label, string lab_name);

void add_SEQ_instruction(Instructions& instructions, Variables& variables, TokenList::iterator it, int& position, Labels& labels, bool has_neighbour_label, string lab_name);

void add_variable_to_instruction(std::string name, Variables& vars, Variables& instr_vars, int& position);

void add_instruction_to_label(Instruction* instr, Instruction* pred_instr, string lab_name, Labels& labels);

void set_variable_position(Variable* var, int& position);

void fill_def(Variables& def, Variables& dst);

void fill_use(Variables& use, Variables& src);

Instruction* get_pred_instr(Instructions& instructions);

void set_jump_relations(Instructions& instructions, Labels& labels);

void add_jump_succ(Instruction* instruction, Labels& labels);

bool instruction_exists(Instructions& instructions, Instruction* instruction);
