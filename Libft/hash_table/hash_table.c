/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   hash_table.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/26 19:49:39 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/10 12:40:57 by simrossi    ###    #+. /#+    ###.fr     */
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
	alveol = table->items[hash];
	while (alveol)
	{
		if (ft_strequ(key, alveol->key))
			return (alveol->value);
		alveol = alveol->next;
	}
	return (NULL);
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
