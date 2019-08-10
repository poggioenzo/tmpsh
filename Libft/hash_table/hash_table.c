/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   hash_table.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/26 19:49:39 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/16 16:21:59 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include "hash_table.h"

/*
** extract_alveol:
**
** Delete a given alveol who match the key in the chained list.
*/

static int		extract_alveol(t_ht_alveol **alveol, char *key)
{
	t_ht_alveol		*tmp_alveol;
	t_ht_alveol		*prev_alveol;

	tmp_alveol = *alveol;
	prev_alveol = NULL;
	while (tmp_alveol && !ft_strequ(tmp_alveol->key, key))
	{
		prev_alveol = tmp_alveol;
		tmp_alveol = tmp_alveol->next;
	}
	if (!tmp_alveol)
		return (0);
	if (!prev_alveol)
		*alveol = tmp_alveol->next;
	else
		prev_alveol->next = tmp_alveol->next;
	return (free_alveol(&tmp_alveol, 1));
}

static t_ht_alveol *retrieve_alveol(t_ht_alveol *alveol, char *key)
{
	while (alveol)
	{
		if (ft_strequ(key, alveol->key))
			return (alveol);
		alveol = alveol->next;
	}
	return (NULL);
}

/*
** User functions.
*/

/*
** search_value:
**
** Search for the value associated to the given key.
**
** return value:
** - The value associated to the key, NULL if nothing is associated.
*/

void		*search_value(t_ht_table *table, char *key)
{
	int				hash;
	t_ht_alveol		*alveol;

	hash = hash_function(key, table->seed, table->size);
	alveol = retrieve_alveol(table->items[hash], key);
	return (alveol ? alveol->value : NULL);
}

void		**search_value_addr(t_ht_table *table, char *key)
{
	int				hash;
	t_ht_alveol		*alveol;

	hash = hash_function(key, table->seed, table->size);
	alveol = retrieve_alveol(table->items[hash], key);
	return (alveol ? &alveol->value : NULL);
}

/*
** delete_value:
**
** Delete the value associated to the key, in the given hash table.
*/

void			delete_value(t_ht_table *table, char *key)
{
	int		hash;

	hash = hash_function(key, table->seed, table->size);
	extract_alveol(&table->items[hash], key);
}

static t_ht_alveol *alveol_iterator(t_ht_table *table)
{
	while (table->iter_index < table->size)
	{
		if (table->iter_alveol)
		{
			table->iter_alveol = table->iter_alveol->next;
			if (table->iter_alveol)
				return (table->iter_alveol);
		}
		table->iter_index++;
		table->iter_alveol = table->items[table->iter_index];
		if (table->iter_alveol)
			return (table->iter_alveol);
	}
	table->iter_index = -1;
	return (NULL);
}

int				ht_iter(t_ht_table *table, char **key, void **value)
{
	t_ht_alveol		*next_alveol;

	next_alveol = alveol_iterator(table);
	if (!next_alveol)
		return (0);
	*key = next_alveol->key;
	*value = next_alveol->value;
	return (1);
}
