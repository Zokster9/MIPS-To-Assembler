#pragma once
#include "Constants.h"
#include "IR.h"
#include <vector>

using namespace std;

class InterferenceGraph 
{

public:
	InterferenceGraph() {}

	void set_matrix(std::vector<std::vector<int>> matrix);
	void set_variables(Variables* variables);
	void add_matrix_row(vector<int>& row);

	/**
	 * Prints the interference graph
	 */
	void printInterferenceMatrix();

private:
	Variables* m_variables;
	std::vector<std::vector<int>> m_matrix;
};

/**
 * This type represents matrix of integers.
 */
typedef std::vector<std::vector<int>> InterferenceMatrix;

void build_interference_graph(InterferenceGraph& interference_graph, Instructions& instructions, int matrix_size);

bool interference_graph_exists(vector<int>& interferences, int position);

bool compare_variable_positions(const Variable* v1, const Variable* v2);
