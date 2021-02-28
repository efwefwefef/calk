#pragma once
#include <string>
#include <sstream>

class calk
{
protected:
	bool is_operation(char c);
	int get_operation_priority(char c);
	int get_next(std::istringstream& s, double& operand, char& operation);

	void check_arifm_expression(const std::string& str);
	std::string convert_from_normal_to_postfix(std::string str);

public:
	double calk_arifm_expression(std::string str);
};