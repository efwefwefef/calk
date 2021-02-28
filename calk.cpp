#include <cmath>
#include <stack>
#include <algorithm>
#include <exception> 
#include "calk.h"

void remove_all_spaces_and_replace_commas(std::string& str)
{
	str.erase(std::remove_if(str.begin(), str.end(), [](char& c) {return (c == ' ') ? true : false;}), str.end());
	std::replace(str.begin(), str.end(), ',', '.');
}

bool calk::is_operation(char c)
{
	if (c == '*' || c == '+' || c == '/' || c == '-') return true;
	return false;
}

int calk::get_operation_priority(char c)
{
	if (c == '+' || c == '-') return 1;
	if (c == '*') return 2;
	if (c == '/') return 3;
	else return 0; //( ) prior
}

int calk::get_next(std::istringstream& s, double& operand, char& operation)
{
	double tmp = 0;
	std::streampos cur_pos = s.tellg();
	std::streampos prev_pos = cur_pos - std::streamoff(1);

	char c;

	if ((c = s.peek()) == std::char_traits<char>::eof()) return -1;

	if (c == '-')
	{
		if (s >> tmp)
		{
			bool flg = false;
			if (s.seekg(prev_pos))
			{
				s >> c;
				if (c == '(')
				{
					flg = true;
				}
			}
			else
			{
				s.clear();
				flg = true;
			}

			if (flg == true)
			{
				s.seekg(cur_pos);
				s >> tmp;
				operand = tmp;
				return 0;
			}
		}

		s.clear();
		s.seekg(cur_pos);
		s >> operation;
		return 1;
	}
	else if (is_operation(c))
	{
		s >> operation;
		return 1;
	}
	else
	{
		if (s >> tmp)
		{
			operand = tmp;
			return 0;
		}
		else
		{
			s.clear();
			s.seekg(cur_pos);
			s >> operation;
			return 1;
		}
	}
}

void calk::check_arifm_expression(const std::string& str)
{
	std::istringstream ss(str);
	bool err_flag = false;
	int state = 0;
	int s = 0;

	double op;
	char oper;
	int oper_type;
	while ((oper_type = get_next(ss, op, oper)) != -1)
	{
		switch (state)
		{
		case 0:
		{
			if (oper_type == 0) state = 1;
			else if (oper != '(')  err_flag = true;
			else s++;
			break;
		}
		case 1:
		{
			if (oper_type == 0) err_flag = true;
			else if (is_operation(oper)) state = 0;
			else if (oper != ')') err_flag = true;
			else s--;
			break;
		}
		}
		if (err_flag == true || s < 0) throw std::runtime_error("incorrect arithmetic exression");
	}
	if (s != 0 || state != 1) throw std::runtime_error("incorrect arithmetic exression");
}

std::string calk::convert_from_normal_to_postfix(std::string str)
{
	std::string tmp = "";
	std::stack<char> stk;
	std::istringstream ss(str);

	double operand;
	char operation;
	int oper_type;

	while ((oper_type = get_next(ss, operand, operation)) != -1)
	{
		if (oper_type == 1)
		{
			if (is_operation(operation))
			{
				if (!stk.empty())
				{
					char& t = stk.top();
					int cur_prior = get_operation_priority(operation);

					while (get_operation_priority(t) >= cur_prior)
					{
						tmp += t;
						stk.pop();
						if (!stk.empty()) t = stk.top();
						else break;
					}
				}
				stk.push(operation);
			}
			else if (operation == '(')
			{
				stk.push(operation);
			}
			else if (operation == ')')
			{
				char& t = stk.top();

				while (t != '(')
				{
					tmp += t;
					stk.pop();
					t = stk.top();
				}
				stk.pop();
			}
		}
		else
		{
			tmp += ("(" + std::to_string(operand) + ")");
		}
	}

	while (!stk.empty())
	{
		tmp += stk.top();
		stk.pop();
	}

	return tmp;
}

double calk::calk_arifm_expression(std::string str)
{
	remove_all_spaces_and_replace_commas(str);
	check_arifm_expression(str);
	std::string p_str = convert_from_normal_to_postfix(str);

	std::istringstream ss(p_str);
	std::stack<double> stack;
	double val;
	char operation;
	int type;

	auto get_next_val_or_operation = [](std::istringstream & ss, double& val, char& operation)
	{
		if (ss.peek() != std::char_traits<char>::eof())
		{
			char tmp;
			ss >> tmp;

			if (tmp == '(')
			{
				ss >> val;
				ss >> tmp;
				return 0;
			}
			else
			{
				operation = tmp;
				return 1;
			}
		}
		else return -1;
	};

	while ((type = get_next_val_or_operation(ss, val, operation)) != -1)
	{
		if (type == 0) stack.push(val);
		else
		{
			double s_operand;
			double f_operand;
			double res;
			s_operand = stack.top();
			stack.pop();
			f_operand = stack.top();
			stack.pop();

			switch (operation)
			{
			case '*': stack.push(f_operand * s_operand); break;
			case '-': stack.push(f_operand - s_operand); break;
			case '+': stack.push(f_operand + s_operand); break;
			case '/': stack.push(f_operand / s_operand); break;
			}
		}
	}
	return std::round(double(stack.top()) * 100) / 100;
}
