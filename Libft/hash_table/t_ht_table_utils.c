/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   t_ht_table_utils.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/26 19:50:15 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/06 11:06:15 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "hash_table.h"
#include <stdlib.h>

/*
** alloc_item_table:
**
** Allocate an array of t_ht_alveol and set all pointer to NULL
*/

static t_ht_alveol	**alloc_item_table(int size)
{
	t_ht_alveol	**table;
	int			index;

	table = (t_ht_alveol **)malloc(sizeof(t_ht_alveol *) * size);
	if (!table)
		return (NULL);
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
	free((*hash_table)->items);
	(*hash_table)->items = NULL;
	free(*hash_table);
	*hash_table = NULL;
	return (status);
}

/*
** ht_new_table:
**
** Allocate a t_ht_table structure.
*/

int					ht_new_table(t_ht_table **hash_table, int seed, int size)
{
	if (!(*hash_table = (t_ht_table *)malloc(sizeof(t_ht_table))))
		return (0);
	(*hash_table)->size = size;
	(*hash_table)->seed = seed;
	if (!((*hash_table)->items = alloc_item_table((*hash_table)->size)))
		return (free_hash_table(hash_table, 0));
	return (1);
}
