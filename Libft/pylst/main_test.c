#include "libft.h"

/*
** MAIN TEST
*/

void	print_tab(char **tab)
{
	while (*tab)
		ft_printf("%s\n", *tab++);
}
int		main(int argc, char **argv)
{
	setup_pyfreefct();

	char		**tab;
	int			len;
	t_pylst		*pylst;

	tab = ft_strsplit(argv[1], " ");
	len = ft_arraylen(tab);
	pylst = NULL;
	push_pylst(&pylst, tab, NO_COPY_BUT_FREE, _charee);


	char **elem = pylst->value;
	print_tab(elem);

	t_pylst		*newlst;

	newlst = NULL;
	push_pylst(&newlst, pylst, NO_COPY_BUT_FREE, _pylst);
	char **test;

	test = ((t_pylst *)newlst->value)->value;
	print_tab(test);

	free_pylst(&newlst, 0);
	return (0);
}
