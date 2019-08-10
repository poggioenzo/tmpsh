#include "tmpsh.h"
#include "libft.h"

t_ht_table		*g_variables = NULL;

char	*ft_getvar(char *var)
{
	return (search_value(g_variables, var));
}

void	ft_setvar(char *variable, char *value)
{
	insert_value(g_variables, variable, value, _chare);
}

void	setup_var_table(void)
{
	int seed;
	int size;

	seed = 47;
	size = 100;
	ht_new_table(&g_variables, seed, size);
}
