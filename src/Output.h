#ifndef __OUTPUT__
#define __OUTPUT__

#include "IR.h"
#include "Function.h"
#include "Label.h"

void write(Instructions& instructions, Variables& variables, Function& f, Labels& labels, string& fileName);

bool is_instruction_after_label(Instruction* instruction, Labels& labels);

Label* get_label(Instruction* instruction, Labels& labels);

#endif

