/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free_pylst.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/10 10:44:23 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/14 09:11:15 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static int		is_value_allocated(t_pylst *py_node)
{
	return (py_node->size > 0 || py_node-> size == NO_COPY_BUT_FREE);
}

/*
** free_pylst_node:
**
** Free a single t_pylst node and set his pointer to NULL.
*/

int		free_pylst_node(t_pylst **py_node, int status)
{
	t_free_fct	free_fct;

	if (!*py_node)
		return (status);
	if (is_value_allocated(*py_node))
	{
		free_fct = g_free_fct[(*py_node)->ctype];
		free_fct(&(*py_node)->value);
	}
	FREE(*py_node);
	*py_node = NULL;
	return (status);
}

/*
** free_pylst:
**
** Free an entire chaine list of t_pylst element.
** Set his pointer to NULL and return the status value.
*/

int		free_pylst(t_pylst **pylst, int status)
{
	t_pylst		*curr_node;
	t_pylst		*next_node;

	curr_node = *pylst;
	while (curr_node)
	{
		next_node = curr_node->next;
		free_pylst_node(&curr_node, status);
		curr_node = next_node;
	}
	*pylst = NULL;
	return (status);
}

/*
** pylst_clean_node:
**
** @node: single to clean the value.
*/

void	pylst_clean_node(t_pylst *node)
{
	if (is_value_allocated(node))
		g_free_fct[node->ctype](&node->value);
	node->value = NULL;
	node->ctype = _ptr;
	node->size = 0;
}

/*
** pylst_clean:
**
** Clean each value of an entire pylst with the appropriate freeing
** function
*/

void	pylst_clean(t_pylst *pylst)
{
	while (pylst)
	{
		pylst_clean_node(pylst);
		pylst = pylst->next;
	}
}
