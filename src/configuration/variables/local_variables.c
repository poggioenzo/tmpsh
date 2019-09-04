/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   determine_bytes.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/27 15:04:52 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/27 15:04:55 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "tmpsh.h"
#include "libft.h"

t_ht_table		*g_variables = NULL;

/*
** ft_getvar:
**
** Return the value of the given variable.
*/

char	*ft_getvar(char *var)
{
	return (search_value(g_variables, var));
}

/*
** ft_setvar:
**
** Store the given variable value.
*/

void	ft_setvar(char *variable, char *value)
{
	insert_value(g_variables, variable, value, _chare);
}

/*
** ft_unsetvar:
**
** Remove a variable from the local variables.
*/

void	ft_unsetvar(char *variable)
{
	delete_value(g_variables, variable);
}

/*
** setup_var_table:
**
** Allocate the global hash table g_variables to store local variables.
*/

void	setup_var_table(void)
{
	int seed;
	int size;

	seed = 47;
	size = 100;
	ht_new_table(&g_variables, seed, size);
}
