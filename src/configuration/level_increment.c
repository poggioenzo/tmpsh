#include "libft.h"
#include "tmpsh.h"
#include "variables.h"

/*
** set_shlvl:
**
** Increment SHLVL environnement variable.
** Set it to 1 if not available.
*/

void		set_shlvl(void)
{
	char	*current_lvl;
	int		int_lvl;

	if ((current_lvl = ft_getenv("SHLVL")))
	{
		int_lvl = ft_atoi(current_lvl);
		current_lvl = ft_itoa(int_lvl + 1);
	}
	else
		current_lvl = ft_strdup("1");
	ft_setenv("SHLVL", current_lvl);
	ft_strdel(&current_lvl);
}
