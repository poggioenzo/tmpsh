#include "errors_builder.h"
#include "libft.h"
#include "t_char_allocation.h"
#include "t_line_allocation.h"

/*
** Set of functions to check if 2 t_char *element are different.
** Get 3 kind of function check + display the result:
**
** - 1 Comparaison function
** - 1 Printing function
** - 1 One to perform the entire process
*/

t_char	*create_ref_list(char *string)
{
	t_char	*char_ref = NULL;
	int		lock = TRUE;

	while (*string)
		push_end_char(&char_ref, *string++, lock);
	return (char_ref);
}

static int		compare_t_char(t_char *to_test, t_char *reference)
{
	while (to_test && reference)
	{
		if (to_test->letter != reference->letter)
			break ;
		if (to_test->position != reference->position)
			break ;
		reference = reference->next;
		to_test = to_test->next;
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

/*
** create_ref_shell:
**
** Create a shell like structure with t_line.
** Add each character of the string in a t_char list,
** creating a new t_line at each newline.
*/

t_line	*create_ref_shell(char *str)
{
	t_line	*shell_repr = NULL;
	t_line	*start_line;

	push_end_line(&shell_repr);
	start_line = shell_repr;
	while (*str)
	{
		if (*str == '\n')
		{
			push_end_line(&shell_repr);
			shell_repr = shell_repr->next;
		}
		else
			push_end_char(&shell_repr->chars, *str, FALSE);
		str++;
	}
	return (start_line);
}

/*
** Set of function to perform test on t_line *
*/

static int	compare_t_line(t_line *result_sh, t_line *reference_sh)
{
	while (result_sh && reference_sh)
	{
		if (!compare_t_char(result_sh->chars, reference_sh->chars))
			return (0);
		if (result_sh->position != reference_sh->position)
			return (0);
		result_sh = result_sh->next;
		reference_sh = reference_sh->next;
	}
	return (!result_sh && !reference_sh);
}

static void	_chars_list_representation(t_char *char_lst)
{
	while (char_lst)
	{
		ft_printf("(%d, %c)->", char_lst->position, char_lst->letter);
		char_lst = char_lst->next;
	}
	ft_printf("NULL\n");
}

static void	_single_line_representation(t_line *shell_repr, char *line_name)
{
	ft_printf("%s :\n", line_name);
	while (shell_repr)
	{
		_chars_list_representation(shell_repr->chars);
		shell_repr = shell_repr->next;
	}
}

static void	_t_line_error_display(int nb_error, _t_line_type *errors)
{
	int		index = 0;

	while (index < nb_error)
	{
		ft_printf("---- Test %d ----\n", errors[index].test);
		_single_line_representation(errors[index].result, "Result");
		_single_line_representation(errors[index].reference, "Reference");
		index++;
	}

}

FUNCTION_ERROR_MAKER2(t_line_error_fct, compare_t_line, \
	_t_line_type, t_line *, _t_line_error_display)




