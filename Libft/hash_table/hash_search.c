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

#include "libft.h"

static t_ht_alveol	*retrieve_alveol(t_ht_alveol *alveol, char *key)
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

void				*search_value(t_ht_table *table, char *key)
{
	int				hash;
	t_ht_alveol		*alveol;

	hash = hash_function(key, table->seed, table->size);
	alveol = retrieve_alveol(table->items[hash], key);
	return (alveol ? alveol->value : NULL);
}

/*
** search_value_addr:
**
** @table: hash table selected to perform research.
** @key: desired key.
**
** Equivalent to search value, but return the value address.
**
** return : - NULL if no avaible item.
**			- address of the item value.
*/

void				**search_value_addr(t_ht_table *table, char *key)
{
	int				hash;
	t_ht_alveol		*alveol;

	hash = hash_function(key, table->seed, table->size);
	alveol = retrieve_alveol(table->items[hash], key);
	return (alveol ? &alveol->value : NULL);
}
