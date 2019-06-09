#include "test_runner.h"

/*
** Simple example
*/

void		grammar_test(void)
{
	int		x_test = 0;

	//Var to tests;
	int		test_value = 125;
	int		reference_value = 125;

	ASSERT_INTCMP(x_test, test_value, reference_value);
}
