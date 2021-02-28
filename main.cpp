#include <iostream>
#include "calk.h"

int main()
{
	std::string expr;
	calk C = calk();
	std::cout << "enter arithmetic expression: ";
	std::getline(std::cin, expr);

	try {
		double new_val = C.calk_arifm_expression(expr);
		printf("result: %.2f\n", new_val);
	}
	catch (std::exception & exp)
	{
		std::cout << "Error: " << exp.what() << std::endl;
	}
}
