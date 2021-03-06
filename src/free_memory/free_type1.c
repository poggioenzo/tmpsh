/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free_type1.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/10 10:21:29 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/16 12:49:50 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

/*
** no_free:
**
** Use when a data type should not be freed.
*/

void			free_ptr(void *ptr)
{
	ft_memdel((void **)ptr);
}

/*
** free_chare:
**
** Free a single char * element.
*/

void			free_chare(void *str_ptr)
{
	char	**real_str;

	real_str = (char **)str_ptr;
	ft_strdel(real_str);
}

/*
** free_charee:
**
** Free an entire char ** element.
*/

void			free_charee(void *array_ptr)
{
	free_str_array((char ***)array_ptr, NO_STATUS);
}

/*
** free_pylst:
**
** Free a chained list of t_pylst.
*/

void			free_pylst_type(void *pylst_ptr)
{
	free_pylst((t_pylst **)pylst_ptr, NO_STATUS);
}

/*
** free_hash_table:
**
** Free an entire t_ht_table.
*/

void			free_hash_table_type(void *table_ptr)
{
	free_hash_table((t_ht_table **)table_ptr, NO_STATUS);
}
