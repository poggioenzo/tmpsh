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
** show_tab:
**
** Debug function to print an hash table.
** Format like:
** 0: [key:value, key:value, ...]
** 1: ...
** ...
*/

void	show_tab(t_ht_table *table)
{
	t_ht_alveol *alveol;
	int index = 0;

	while (index < table->size)
	{
		ft_printf("%d:", index);
		alveol = table->items[index];
		while (alveol)
		{
			ft_printf("'%s':'%s', ", alveol->key, alveol->value);
			alveol = alveol->next;
		}
		ft_printf("\n");
		index++;
	}

}

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

/*
** alveol_iterator:
**
** @table: table selected for iteration.
**
** Utils to parse each alveol of an hash table one by one.
** Go through each item in their index order, and parse each time
** the entire chained list of alveol.
**
** return : - next alveol to use on success.
**			- NULL if the iteration is over.
*/

static t_ht_alveol *alveol_iterator(t_ht_table *table)
{
	while (table->iter_index < table->size || table->iter_alveol)
	{
		if (!table->iter_alveol)
			table->iter_alveol = table->items[table->iter_index++];
		else
			table->iter_alveol = table->iter_alveol->next;
		if (table->iter_alveol)
			return (table->iter_alveol);
	}
	table->iter_index = 0;
	return (NULL);
}

/*
** ht_iter:
**
** @table: table selected for iteration.
** @key: char * pointer to get the next key.
** @value: char * pointer to get next value.
**
** Allow the iteration of an hash table. Wrapper of alveol_iterator.
** ! No change on the hash table should be done during the iteration !
**
** return : - 1 if an next element is found.
**			- 0 if the iteration is over.
*/

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

void	empty_ht(t_ht_table *table)
{
	int		index;

	index = 0;
	while (index < table->size)
		free_alveol_list(&table->items[index++], 0);
}
