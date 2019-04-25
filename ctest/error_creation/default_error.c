#include "errors_builder.h"
#include "libft.h"

/*
** Basic functions to perform test on standard type.
** void *, char *, int.
**
** 3 functions for each type test.
** - One comparaison function
** - One printing function
** - One macro to create the entire error check function
*/

/*
** Test functions for char * type.
*/

static int		char_error_cmp(char *result, char *reference)
{
	return (!strcmp(result, reference));
}

static void	char_error_show(int nb_error, char_tests *char_lst)
{
	ft_printf("Test %d :\nresult : |%s|\nreference : |%s|\n", \
			char_lst[0].test, char_lst[0].result, char_lst[0].reference);
}

FUNCTION_ERROR_MAKER2(_chare_error2, char_error_cmp, char_tests, char *, \
		char_error_show)
/*
** Test functions for int type.
*/

static int		int_error_cmp(int result, char reference)
{
	return (result == reference);
}

static void	int_error_show(int nb_error, _int_tests *int_list)
{
	int		index = 0;

	while (index < nb_error)
	{
		ft_printf("Test %d :\nresult : %p  | reference : %p\n", \
				int_list[index].test, int_list[index].result, \
				int_list[index].reference);
		index++;
	}
}

FUNCTION_ERROR_MAKER2(_int_error2, int_error_cmp, _int_tests, int, \
		int_error_show)

/*
** Test functions for void * type.
*/

static int		ptr_error_cmp(void *result, void *reference)
{
	return (result == reference);
}

static void	ptr_error_show(int nb_error, _ptr_tests *ptr_lst)
{
	int		index = 0;

	while (index < nb_error)
	{
		ft_printf("Test %d :\nresult : %p  | reference : %p\n", \
				ptr_lst[index].test, ptr_lst[index].result, \
				ptr_lst[index].reference);
		index++;
	}
}

FUNCTION_ERROR_MAKER2(_ptr_error2, ptr_error_cmp, _ptr_tests, void *, \
		ptr_error_show)

