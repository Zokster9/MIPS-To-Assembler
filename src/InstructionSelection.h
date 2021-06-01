#pragma once
#include "IR.h"
#include "Token.h"
#include "LexicalAnalysis.h"

void fill_instruction_list(Instructions& instructions, Variables& variables, TokenList& tokenList);

void add_variable(Variables& variables, TokenType& token_type, TokenList::iterator it);

void add_ADD_instruction(Instructions& instructions, Variables& variables, TokenList::iterator it, int& position);

void add_ADDI_instruction(Instructions& instructions, Variables& variables, TokenList::iterator it, int& position);

void add_LA_instruction(Instructions& instructions, Variables& variables, TokenList::iterator it, int& position);

void add_LW_instruction(Instructions& instructions, Variables& variables, TokenList::iterator it, int& position);

void add_LI_instruction(Instructions& instructions, Variables& variables, TokenList::iterator it, int& position);

void add_B_instruction(Instructions& instructions, Variables& variables, TokenList::iterator it, int& position);

void add_BLTZ_instruction(Instructions& instructions, Variables& variables, TokenList::iterator it, int& position);

void add_NOP_instruction(Instructions& instructions);

void add_SUB_instruction(Instructions& instructions, Variables& variables, TokenList::iterator it, int& position);

void add_SW_instruction(Instructions& instructions, Variables& variables, TokenList::iterator it, int& position);

void add_variable_to_instruction(std::string name, Variables& vars, Variables& instr_vars, int& position);

void set_variable_position(Variable* var, int& position);

void fill_def(Variables& def, Variables& dst);

void fill_use(Variables& use, Variables& src);

Instruction* get_pred_instr(Instructions& instructions);
