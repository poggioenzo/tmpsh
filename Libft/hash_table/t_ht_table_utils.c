/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   t_ht_table_utils.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/26 19:50:15 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/15 11:47:50 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "hash_table.h"
#include "libft.h"

/*
** alloc_item_table:
**
** Allocate an array of t_ht_alveol and set all pointer to NULL
*/

static t_ht_alveol	**alloc_item_table(int size)
{
	t_ht_alveol	**table;
	int			index;

	table = (t_ht_alveol **)MALLOC(sizeof(t_ht_alveol *) * size);
	if (!table)
		exit(-1);
	index = 0;
	while (index < size)
		table[index++] = NULL;
	return (table);
}

/*
** free_hash_table:
**
** Free each attribute of a t_ht_table, return the given status.
*/

int					free_hash_table(t_ht_table **hash_table, int status)
{
	int		index;

	if (!*hash_table)
		return (status);
	index = 0;
	while (index < (*hash_table)->size)
		free_alveol_list(&(*hash_table)->items[index++], 0);
	FREE((*hash_table)->items);
	(*hash_table)->items = NULL;
	FREE(*hash_table);
	*hash_table = NULL;
	return (status);
}

/*
** ht_new_table:
**
** Allocate a t_ht_table structure.
*/

void				ht_new_table(t_ht_table **hash_table, int seed, int size)
{
	if (!(*hash_table = (t_ht_table *)MALLOC(sizeof(t_ht_table))))
		exit(-1);
	(*hash_table)->size = size;
	(*hash_table)->seed = seed;
	(*hash_table)->items = alloc_item_table((*hash_table)->size);
}
