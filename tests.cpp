#include "calk.h"
#include <string> 
#include <gtest/gtest.h>

calk C;

TEST(calk_arifm_expression, tests_from_test_task)
{
	ASSERT_TRUE(C.calk_arifm_expression("-1 + 5 - 3") == 1);
	ASSERT_TRUE(C.calk_arifm_expression("-10 + (8 * 2.5) - (3 / 1,5)") == 8);
	ASSERT_TRUE(C.calk_arifm_expression("1 + (2 * (2.5 + 2.5 + (3 - 2))) - (3 / 1.5)") == 11);
	
	std::string msg = "incorrect arithmetic exression";
	try
	{
		C.calk_arifm_expression("1.1 + 2.1 + abc");	
	}catch(std::exception& e)
	{
		ASSERT_TRUE(msg.compare(e.what()) == 0);
	}
}

TEST(calk_arifm_expression_positive_tests, negative_operand_test)
{
	ASSERT_TRUE(C.calk_arifm_expression("-6") == -6);
	ASSERT_TRUE(C.calk_arifm_expression("  -6") == -6);
	ASSERT_TRUE(C.calk_arifm_expression("-10000000") == -10000000);
}

TEST(calk_arifm_expression_positive_tests, positive_operand_test)
{
	ASSERT_TRUE(C.calk_arifm_expression("6") == 6);
	ASSERT_TRUE(C.calk_arifm_expression("  6") == 6);
	ASSERT_TRUE(C.calk_arifm_expression("10000000") == 10000000);
}

TEST(calk_arifm_expression_positive_tests, round_test)
{
	ASSERT_TRUE(C.calk_arifm_expression("6.875") == 6.88);
	ASSERT_TRUE(C.calk_arifm_expression("6,874") == 6.87);
	ASSERT_TRUE(C.calk_arifm_expression("6.795") == 6.80);
		
	ASSERT_TRUE(C.calk_arifm_expression("10000000,879") == 10000000.88);
}	

TEST(calk_arifm_expression_positive_tests, arithmetic_expression_without_delimiters_test)
{
	ASSERT_TRUE(C.calk_arifm_expression("-12.34-444.21-91.32-71.87") == -619.74); //only - operation
	ASSERT_TRUE(C.calk_arifm_expression("12.34+6.34-88.12+1244.87") == 1175.43); //only + operation
	ASSERT_TRUE(C.calk_arifm_expression("223*45*123*3") == 3702915); //only * operation
	ASSERT_TRUE(C.calk_arifm_expression("223/45/123/3") == 0.01); //only / operation
	ASSERT_TRUE(C.calk_arifm_expression("  6.875  +  32,654-12.8734  +972.331") == 998.99); //-+ operations
	ASSERT_TRUE(C.calk_arifm_expression("23.65*873.41/7.29*2.32/6.9812*12*43*4.54") == 2205897.03); //*/ operation
	ASSERT_TRUE(C.calk_arifm_expression("24.12*87,2/566*391+34 - 12,78") == 1474.18); // /*-+ operations	
}

TEST(calk_arifm_expression_positive_tests, arithmetic_expression_with_delimiters_test)
{
	ASSERT_TRUE(C.calk_arifm_expression("(-777.3234)") == -777.32);
	ASSERT_TRUE(C.calk_arifm_expression("(((-777.3234)))") == -777.32);
	ASSERT_TRUE(C.calk_arifm_expression("(777.3234 + 1233)/345") == 5.83);
	ASSERT_TRUE(C.calk_arifm_expression("(-777.3234 - 1233)/345") == -5.83);
	ASSERT_TRUE(C.calk_arifm_expression("(-777,3234 - 1233)/(345+3,89)") == -5.76);
	ASSERT_TRUE(C.calk_arifm_expression("-23*78.23-87*(-12+983/4*2-81+(234-12+8*9-(87-123-455/(982-864*2))))") == -65125.73);
}

TEST(calk_arifm_expression_negative_tests, incorrect_arithmetic_expression_without_delimiters)
{
	std::string msg = "incorrect arithmetic exression";
	const char* buff[] = {"hhhuefheu", "34m6", "+455.23", "--3445.23", "34**834", "45//12", "9--89", "/4", "*9", "4 + q"};
	
	for(int i = 0; i < 10; i++)
	{
		try
		{
			C.calk_arifm_expression(std::string(buff[i]));
		}catch(std::exception& e)
		{
			ASSERT_TRUE(msg.compare(e.what()) == 0);
		}
	}
}

TEST(calk_arifm_expression_negative_tests, incorrect_arithmetic_expression_with_delimiters)
{
	std::string msg = "incorrect arithmetic exression";
	const char* buff[] = {"(5+1))", "((5+1)", "+(343+4)", "(4+(/6+2))", "(4+(*6+2))", "(4+(+6+2))", "(4(6+2))"};
	
	for(int i = 0; i < 7; i++)
	{
		try
		{
			C.calk_arifm_expression(std::string(buff[i]));
		}catch(std::exception& e)
		{
			ASSERT_TRUE(msg.compare(e.what()) == 0);
		}
	}
}



int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS(); 
}
