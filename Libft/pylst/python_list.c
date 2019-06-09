/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   python_list.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/10 10:32:13 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/15 18:39:06 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

/*
** alloc_pylst_node:
**
** Allocate a single t_pylst * (aka struct s_pylst *) element.
** Duplicate his value content if the size is given.
*/

static void		alloc_pylst_node(t_pylst **py_node, void *value, int size, \
		int ctype)
{
	if (!(*py_node = (t_pylst *)MALLOC(sizeof(t_pylst))))
		exit(-1);
	if (size > 0)
	{
		if (!((*py_node)->value = MALLOC(size)))
			exit(-1);
		ft_memcpy((*py_node)->value, value, size);
	}
	else
		(*py_node)->value = value;
	(*py_node)->ctype = ctype;
	(*py_node)->size = size;
	(*py_node)->next = NULL;
}

/*
** push_pylst:
**
** Push at the end of the current list a new element.
** Copy the given value if a size is given.
*/

void		push_pylst(t_pylst **pylst, void *value, int size, int ctype)
{
	if (!*pylst)
		alloc_pylst_node(pylst, value, size, ctype);
	else
	{
		while ((*pylst)->next)
			pylst = &(*pylst)->next;
		alloc_pylst_node(&(*pylst)->next, value, size, ctype);
	}
}

/*
** len_pylst:
**
** Return the total length of the given list.
*/

int			len_pylst(t_pylst *pylst)
{
	int		size;

	size = 0;
	while (pylst)
	{
		pylst = pylst->next;
		size++;
	}
	return (size);
}

/*
** convert_neg_index:
**
** Whenever the user is given an negativ index, research his
** positiv relation.
*/

static int		convert_neg_index(t_pylst *pylst, int index)
{
	int		lst_len;

	if (index < 0)
	{
		lst_len = len_pylst(pylst);
		index = lst_len + index;
	}
	return (index);
}

/*
** index_pylst:
**
** Return the t_pylst element of the given index.
** Allow performing negativ research.
** WARNING : Will segfault if wrong index (IndexError)
*/

t_pylst		*index_pylst(t_pylst *pylst, int index)
{
	index = convert_neg_index(pylst, index);
	while (pylst && index--)
		pylst = pylst->next;
	return (pylst);
}

/*
** slice_pylst:
**
** Return a new allocated portion of the given list in the
** interval [from:to[.
**
** Allow negative number, -1 for the last node, etc.
*/

t_pylst		*slice_pylst(t_pylst *pylst, int from, int to)
{
	t_pylst		*start_node;
	t_pylst		*end_node;
	t_pylst		*sliced;

	sliced = NULL;
	start_node = index_pylst(pylst, from);
	end_node = index_pylst(pylst, to);
	if (start_node == end_node)
		return (NULL);
	while (1)
	{
		push_pylst(&sliced, start_node->value, start_node->size, \
				start_node->ctype);
		if (start_node->next == end_node)
			break ;
		start_node = start_node->next;
	}
	return (sliced);
}

/*
** duplicate_pylst:
**
** Return a deep copy of the given t_pylst.
*/

t_pylst		*duplicate_pylst(t_pylst *pylst)
{
	return (slice_pylst(pylst, 0, len_pylst(pylst)));
}


/*
** join_pylst:
**
** Concat each element of the pylst according to the given char.
** WARNING : Must be use with char *element.
*/

char	*join_pylst(t_pylst *pylst, char *substr)
{
	char	*concat_str;
	char	*py_str;

	if (!(concat_str = ft_strnew(0)))
		return (NULL);
	while (pylst)
	{
		py_str = pylst->value;
		if (!(concat_str = ft_fstrjoin(&concat_str, &py_str, TRUE, FALSE)))
			exit(-1);
		pylst = pylst->next;
		if (pylst)
		{
			if (!(concat_str = ft_fstrjoin(&concat_str, &substr, TRUE, FALSE)))
				exit(-1);
		}
	}
	return (concat_str);
}

/*
** precedence_pylst:
**
** Get the t_pylst element just before the given index.
*/

t_pylst		*precedence_pylst(t_pylst *pylst, int index)
{
	index = convert_neg_index(pylst, index);
	if (index == 0)
		return (NULL);
	return (index_pylst(pylst, index - 1));
}

/*
** del_portion_pylst:
**
** Delete in the given list element with range [from:to[
*/

void	del_portion_pylst(t_pylst **pylst, int from, int to)
{
	t_pylst	*start;
	t_pylst	*end;
	t_pylst	*start_precedence;

	if (from == to)
		return ;
	start_precedence = precedence_pylst(*pylst, from);
	start = start_precedence ? start_precedence->next : *pylst;
	end = precedence_pylst(*pylst, to);
	if (!start_precedence && !end)
		return ;
	if (start_precedence)
		start_precedence->next = end->next;
	else
		*pylst = end->next;
	end->next = NULL;
	free_pylst(&start, 0);
}

/*
** del_after_pylst:
**
** Delete each element from the given index
*/

void	del_after_pylst(t_pylst **pylst, int index)
{
	t_pylst		*del_node;
	t_pylst		*precedence;

	del_node = NULL;
	if (index == 0)
	{
		free_pylst(pylst, 0);
		return ;
	}
	precedence = precedence_pylst(*pylst, index);
	del_node = precedence->next;
	precedence->next = NULL;
	free_pylst(&del_node, 0);
}

/*
** replace_pylst:
**
** Change a part of the given list with the given list
** WARNING : do not duplicate the new_pylst element.
**
** Don't do that :
** var = [1,2,3,4]
** var[0:0] = [9,7,8]
** You're not in Python ! And it seem stupid. Use different index please beacause
** it will have an UNDEFINED BEHAVIOR otherwise, like I don't know what.
** Or please implement this behavior by yourself, up to you.
*/

void	replace_pylst(t_pylst **old_pylst, t_pylst *new_pylst, int from, int to)
{
	t_pylst		*precedence_from;
	t_pylst		*precedence_to;
	t_pylst		*del_slice;
	t_pylst		*save_head;

	save_head = *old_pylst;
	precedence_from = precedence_pylst(*old_pylst, from);
	precedence_to = precedence_pylst(*old_pylst, to);
	del_slice = NULL;
	*old_pylst = precedence_from ? *old_pylst : new_pylst;
	if (precedence_from)
	{
		del_slice = precedence_from->next;
		precedence_from->next = new_pylst;
	}
	new_pylst = index_pylst(new_pylst, -1);
	if (precedence_to)
	{
		new_pylst->next = precedence_to->next;
		precedence_to->next = NULL;
	}
	else
		new_pylst->next = save_head;
	free_pylst(&del_slice, 0);
}
