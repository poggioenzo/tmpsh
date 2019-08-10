/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   hash_alveol.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/26 19:47:28 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/16 16:13:48 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include "hash_table.h"

/*
** Alveoles utils
*/

int				free_alveol(t_ht_alveol **alveol, int status)
{
	t_free_fct	freeing_fct;

	ft_strdel(&(*alveol)->key);
	freeing_fct = g_free_fct[(*alveol)->ctype];
	freeing_fct(&(*alveol)->value);
	FREE(*alveol);
	*alveol = NULL;
	return (status);
}

/*
** free_alveol_list:
**
** Free en entire chained list of alveol.
*/

int				free_alveol_list(t_ht_alveol **alveol, int status)
{
	t_ht_alveol	*tmp_alveol;
	t_ht_alveol	*next_alveol;

	tmp_alveol = *alveol;
	while (tmp_alveol)
	{
		next_alveol = tmp_alveol->next;
		free_alveol(&tmp_alveol, status);
		tmp_alveol = next_alveol;
	}
	*alveol = NULL;
	return (status);
}

/*
** create_alveol:
**
** Create a new alveol element from a pair key/value.
*/

static void		create_alveol(const char *key, void *value, \
		t_ht_alveol **alveol, int ctype)
{
	if (!(*alveol = (t_ht_alveol *)MALLOC(sizeof(**alveol))))
		exit(-1);
	(*alveol)->value = value;
	if (!((*alveol)->key = ft_strdup(key)))
		exit(-1);
	(*alveol)->ctype = ctype;
	(*alveol)->next = NULL;
}

/*
** insert_in_alveol:
**
** Allocate a new t_ht_alveol with the pair key/value, push it at the end
** of the chained list. Update an alveol if the key alreay exist.
*/

static void	insert_in_alveol(t_ht_alveol **alveol, char *key, void *value,\
		int ctype)
{
	t_ht_alveol	*tmp_alveol;

	if (!*alveol)
		create_alveol(key, value, alveol, ctype);
	else
	{
		tmp_alveol = *alveol;
		while (tmp_alveol->next)
		{
			if (ft_strequ(key, tmp_alveol->key))
			{
				tmp_alveol->value = value;
				tmp_alveol->ctype = ctype;
				return ;
			}
			tmp_alveol = tmp_alveol->next;
		}
		create_alveol(key, value, &tmp_alveol->next, ctype);
	}
}

/*
** insert_value:
**
** Insert a value in the selected table, according to a key.
*/

void			insert_value(t_ht_table *table, char *key, void *value, int ctype)
{
	int			hash;
	t_ht_alveol	**alveol;

	hash = hash_function(key, table->seed, table->size);
	alveol = &table->items[hash];
	insert_in_alveol(alveol, key, value, ctype);
	table->count++;
}
