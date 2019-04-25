#include "errors_builder.h"
#include "libft.h"

/*
** Set of functions to check if 2 t_char *element are different.
** Get 3 kind of function check + display the result:
**
** - 1 Comparaison function
** - 1 Printing function
** - 1 One to perform the entire process
*/

static int		compare_t_char(t_char *to_test, t_char *reference)
{
	while (to_test && reference && to_test == reference)
	{
		to_test = to_test->next;
		reference = reference->next;
	}
	return (!to_test && !reference ? SUCCESS : FAILURE);
}

static void	t_char_printing(t_char *char_lst, char *error_msg)
{
	ft_printf("%s : ", error_msg);
	while (char_lst)
	{
		ft_printf("(%d, '%c')->", char_lst->position, char_lst->letter);
		char_lst = char_lst->next;
	}
	ft_printf("NULL\n");
}

static void	_t_char_error_display(int nb_error, _t_char_type *errors)
{
	int	index = 0;

	while (index < nb_error)
	{
		ft_printf("\n----------------------------\n");
		ft_printf("Test %d :\n", errors[index].test);
		t_char_printing(errors[index].result, "result : ");
		t_char_printing(errors[index].reference, "reference : ");
		ft_printf("\n----------------------------\n");
		index++;
	}
}

FUNCTION_ERROR_MAKER2(t_char_error_fct, compare_t_char, \
	_t_char_type, t_char *, _t_char_error_display)
