#include "errors_builder.h"
#include "libft.h"
#include <stdarg.h>

static void		show_lst(t_pylst *pylst)
{
	while (pylst)
	{
		ft_printf("%s-->", (char*)pylst->value);
		pylst = pylst->next;
	}
	ft_printf("NULL\n");
}

t_pylst		*create_ref_pylist(int nb_args, ...)
{
	va_list		args;
	t_pylst		*pylst = NULL;
	char		*str;
	int			len_str;

	va_start(args, nb_args);
	while (nb_args)
	{
		str = va_arg(args, char *);
		len_str = ft_strlen(str);
		push_pylst(&pylst, str, sizeof(char) * (len_str + 1), _chare);
		nb_args--;
	}
	return (pylst);
}

static int	compare_t_pylst(t_pylst	*result, t_pylst *reference)
{
	while (result && reference)
	{
		if (!ft_strequ((char *)result->value, (char *)reference->value))
			return (0);
		result = result->next;
		reference = reference->next;
	}
	return (!reference && !result);
}

static void t_pylst_printing(t_pylst *pylst, char *error_msg)
{
	ft_printf("%s : ", error_msg);
	ft_printf("[");
	while (pylst)
	{
		ft_printf("\"%s\"", (char *)pylst->value);
		pylst = pylst->next;
	}
	ft_printf("]\n");
}

static void _t_pylst_error_display(int nb_error, _t_pylst_type *errors)
{
	int		index = 0;
	t_pylst	*reference_lst;

	while (index < nb_error)
	{
		ft_printf("\n----------------------------\n");
		ft_printf("Test %d :\n", errors[index].test);
		t_pylst_printing((t_pylst *)errors[index].result, "result:");
		reference_lst = (t_pylst *)errors[index].reference;
		t_pylst_printing(reference_lst, "reference : ");
		free_pylst(&reference_lst, 0);
		ft_printf("\n----------------------------\n");
		index++;
	}
}


FUNCTION_ERROR_MAKER2(t_pylst_error_fct, compare_t_pylst, \
		_t_pylst_type, void *, _t_pylst_error_display)
