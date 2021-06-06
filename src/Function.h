#pragma once

/* Autor: Zoran Bukorac
Datum: 06.06.2021. */

#include <string>

class Function
{
public:
	Function() {}
	
	std::string get_name();
	void set_name(std::string name);

private:
	std::string m_name;

};

