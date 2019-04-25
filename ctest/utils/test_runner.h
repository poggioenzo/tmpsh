#ifndef TEST_RUNNER_H
# define TEST_RUNNER_H
# include "libft.h"
# include "tests_functions.h"

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

#define RED		"\033[0;1;31m"
#define GREEN	"\033[0;1;32m"
#define RESET	"\033[0m"

#define VALID_TEST	display('.', GREEN)
#define INVALID_TEST	display('.', RED);

#define ASSERT_STRCMP(test_nbr, res, ref) test_nbr++;\
	if (ft_strequ(res, ref) || res == ref) \
		VALID_TEST;\
	else \
		{ chare_error(test_nbr, res, ref, STORE_ERROR); INVALID_TEST }

#define ASSERT_INTCMP(test_nbr, res, ref) test_nbr++; \
	if (res == ref)\
		VALID_TEST; \
	else \
		{ int_error(test_nbr, res, ref, STORE_ERROR) ; INVALID_TEST }

#define ASSERT_PTRCMP(test_nbr, res, ref) test_nbr++; \
	if (res == ref)\
		VALID_TEST; \
	else\
		{ ptr_error(test_nbr, res, ref, STORE_ERROR); INVALID_TEST }

#define ASSERT_PTROPE(test_nbr, operation, res, ref) test_nbr++; \
	if (operation) \
		VALID_TEST; \
	else\
		{ ptr_error(test_nbr, res, ref, STORE_ERROR); INVALID_TEST }

#define ASSERT_TEST(test_nbr, result) test_nbr++; \
	if (result) \
		display('.', GREEN);\
	else \
		display('.', RED);

#endif
