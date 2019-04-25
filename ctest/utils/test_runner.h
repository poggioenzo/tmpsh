#ifndef TEST_RUNNER_H
# define TEST_RUNNER_H
# include "libft.h"
# include "tests_functions.h"
# include "errors_builder.h"
# include <string.h>

typedef void (*test_fct)(void);

typedef struct
{
	char *name;
	test_fct	test;
}	test_store;

extern test_store	*g_tests;
extern int			total_tests;

void		display(char letter, char *color);
void		error_display();
void	signal_analysis(int status);
void	function_init(void);

/*
** Functions to display error properly
*/

void	chare_error(int test_number, char *result, char *ref_val, int action);
void	int_error(int test_number, int result, int ref_val, int action);
void	ptr_error(int test_number, void *result, void *ref_val, int action);

#define STORE_ERROR	0
#define SHOW_ERROR	1
#define TEST_FUNCTION	2

#define RED		"\033[0;1;31m"
#define GREEN	"\033[0;1;32m"
#define RESET	"\033[0m"

#define VALID_TEST		display('.', GREEN)
#define INVALID_TEST	display('.', RED)

#define ASSERT_STANDARD(test_nbr, res, ref, check_function) \
	if (check_function(test_nbr++, res, ref, STORE_ERROR) \
		VALID_TEST; \
	else \
		INVALID_TEST;

#define ASSERT_TCHARCMP(test_nbr, res, ref); \
		ASSERT_STANDARD(t_char_error_fct(test_nbr, res, ref)

#define ASSERT_STRCMP(test_nbr, res, ref) \
	ASSERT_STANDARD(_chare_error2, test_nbr, res, ref)

#define ASSERT_INTCMP(test_nbr, res, ref) test_nbr++; \
	ASSERT_STANDARD(_int_error2(test_nbr, res, ref))

#define ASSERT_PTRCMP(test_nbr, res, ref) test_nbr++; \
	ASSERT_STANDARD(_ptr_error2, test_nbr, res, ref)

#define ASSERT_PTROPE(test_nbr, operation, res, ref) test_nbr++; \
	if (operation) \
		VALID_TEST; \
	else\
		{ ptr_error(test_nbr, res, ref, STORE_ERROR); INVALID_TEST; }

#define ASSERT_TEST(test_nbr, result) test_nbr++; \
	if (result) \
		display('.', GREEN);\
	else \
		display('.', RED);

#endif
