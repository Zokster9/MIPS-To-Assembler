/* Autor: Zoran Bukorac
Datum: 06.06.2021. */

#include "Function.h"

std::string Function::get_name()
{
    return m_name;
}

void Function::set_name(std::string name)
{
    m_name = name;
}
