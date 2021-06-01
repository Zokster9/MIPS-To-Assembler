#pragma once
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

