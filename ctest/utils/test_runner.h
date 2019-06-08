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

t_char	*create_ref_list(char *string);
t_pylst		*create_ref_pylist(int nb_args, ...);
t_line	*create_ref_shell(char *str);

#define STORE_ERROR	0
#define SHOW_ERROR	1
#define TEST_FUNCTION	2

#define RED		"\033[0;1;31m"
#define GREEN	"\033[0;1;32m"
#define RESET	"\033[0m"

#define VALID_TEST		display('.', GREEN)
#define INVALID_TEST	display('.', RED)

#define ASSERT_STANDARD(test_nbr, res, ref, check_function) \
	if (check_function(test_nbr++, res, ref, STORE_ERROR)) \
		VALID_TEST; \
	else \
		INVALID_TEST;

#define ASSERT_TCHARCMP(test_nbr, res, ref); \
		ASSERT_STANDARD(test_nbr, res, ref, t_char_error_fct)

#define ASSERT_PYLSTCMP(test_nbr, res, ref); \
		ASSERT_STANDARD(test_nbr, res, ref,  t_pylst_error_fct)

#define ASSERT_TLINECMP(test_nbr, res, ref); \
		ASSERT_STANDARD(test_nbr, res, ref, t_line_error_fct)

#define ASSERT_STRCMP(test_nbr, res, ref) \
	ASSERT_STANDARD(test_nbr, res, ref, _chare_error2) 

#define ASSERT_INTCMP(test_nbr, res, ref) \
	ASSERT_STANDARD(test_nbr, res, ref, _int_error2)

#define ASSERT_PTRCMP(test_nbr, res, ref) \
	ASSERT_STANDARD(test_nbr, res, ref,_ptr_error2)

#define ASSERT_PTROPE(test_nbr, operation, res, ref) test_nbr++;\
	ASSERT_STANDARD(test_nbr, res, ref, _ptr_diff_error)

#define ASSERT_TEST(test_nbr, result) test_nbr++; \
	if (result) \
		display('.', GREEN);\
	else \
		display('.', RED);

#endif
