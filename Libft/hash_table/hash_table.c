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

void			show_tab(t_ht_table *table)
{
	t_ht_alveol		*alveol;
	int				index;

	index = 0;
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

/*
** delete_value:
**
** Delete the value associated to the key, in the given hash table.
*/

void			delete_value(t_ht_table *table, char *key)
{
	int		hash;

	hash = hash_function(key, table->seed, table->size);
	if (extract_alveol(&table->items[hash], key) == 1)
		table->count--;
}

/*
** empty_ht:
**
** Remove all stored value inside an hash table.
*/

void			empty_ht(t_ht_table *table)
{
	int		index;

	index = 0;
	while (index < table->size)
		free_alveol_list(&table->items[index++], 0);
	table->count = 0;
}
