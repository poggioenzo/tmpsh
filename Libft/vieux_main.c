#include "libft.h"

int		cmp_fct(t_pylst *val1, t_pylst *val2)
{
	char	*value_a;
	char		*value_b;

	value_a = val1->value;
	value_b = val2->value;
	return (ft_strcmp(value_a, value_b));
}
int		show_lst(t_pylst *lst)
{
	char		*value;
	while (lst)
	{
		value = lst->value;
		ft_printf("%s -> ", value);
		lst = lst->next;
	}
	ft_printf("NULL\n");
}

int		main(int argc, char **argv)
{
	t_pylst		*unsort;

	unsort = NULL;
	push_pylst(&unsort, "RANDOM", 0, _ptr);
	push_pylst(&unsort, "STMT", 0, _ptr);
	push_pylst(&unsort, "A", 0, _ptr);
	show_lst(unsort);
	sort_pylst(&unsort, cmp_fct);
	show_lst(unsort);
}
