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
#include <stdarg.h>

/*
** alloc_pylst_node:
**
** Allocate a single t_pylst * (aka struct s_pylst *) element.
** Duplicate his value content if the size is given.
*/

static void		alloc_pylst_node(t_pylst **py_node, void *value, int size, \
		int ctype)
{
	*py_node = (t_pylst *)ft_memalloc(sizeof(t_pylst));
	if (size > 0)
	{
		(*py_node)->value = ft_memalloc(size);
		ft_memcpy((*py_node)->value, value, size);
	}
	else
		(*py_node)->value = value;
	(*py_node)->ctype = ctype;
	(*py_node)->size = size;
	(*py_node)->next = NULL;
	(*py_node)->iter_item = NULL;
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
** get_value_pylst:
**
** Arguments, in order :
** @pylst: choosen list.
** @index: index of chosen element.
**
** Return the value of the t_pylst element of the given index.
** Allow performing negativ research.
** WARNING : Will segfault if wrong index (IndexError)
*/

void			*get_value_pylst(t_pylst *pylst, int index)
{
	int length;

	length = len_pylst(pylst);
	if (pylst && index < length)
		return (index_pylst(pylst, index)->value);
	ft_printf("Index out range. Pylst length is %d.\n", length);
	exit(0);
	return (NULL);
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
** pylst_deepcpy:
**
** Return a deep copy of the given t_pylst.
** Allocate new fresh node, and copy all possible
** value within a node.
*/

t_pylst		*pylst_deepcpy(t_pylst *pylst)
{
	return (slice_pylst(pylst, 0, len_pylst(pylst)));
}

/*
** pylst_shacpy:
**
** @pylst : t_pylst to copy.
**
** Return a shallow copy of the pylst.
** Juste allocate node of pylst.
**
** return : - Shallow copy of the list.
*/

t_pylst		*pylst_shacpy(t_pylst *pylst)
{
	t_pylst		*shallow_cpy;

	shallow_cpy = NULL;
	while (pylst)
	{
		push_pylst(&shallow_cpy, pylst->value, 0, pylst->ctype);
		pylst = pylst->next;
	}
	return (shallow_cpy);
}

void	pylst_extend(t_pylst **start, t_pylst *end, int deep_cpy)
{
	t_pylst		*end_cpy;

	if (!*start && !end)
		return ;
	end_cpy = deep_cpy ? pylst_deepcpy(end) : pylst_shacpy(end);
	while (*start && (*start)->next)
		start = &(*start)->next;
	if (!*start)
		*start = end_cpy;
	else
		(*start)->next = end_cpy;
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
		if (py_str && !(concat_str = ft_fstrjoin(&concat_str, &py_str, TRUE, FALSE)))
			exit(-1);
		pylst = pylst->next;
		if (py_str && pylst)
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
** You're not in Python ! And it seem stupid.
** Use different index please because it will have an UNDEFINED BEHAVIOR
** otherwise, like I don't know what.
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

/*
** pylst_iter:
**
** @pylst: chained list head selected to iterate.
** @value: void * pointer to get value one by one in the list.
**
** Used in a while loop to iterate over each element of a pylst.
** Make a for loop inspired from python.
** ! No change on the pylst should be done during the iteration !
**
** return : - 1 if a next element if found.
**			- 0 if pylst is NULL, or if the entire list is parsed.
*/

int		pylst_iter(t_pylst *pylst, void **value)
{
	if (!pylst)
		return (0);
	if (!pylst->iter_item)
		pylst->iter_item = pylst;
	else
		pylst->iter_item = pylst->iter_item->next;
	if (pylst->iter_item)
	{
		*value = pylst->iter_item->value;
		return (1);
	}
	return (0);
}

/*
** pylst_remove:
**
** @pylst: list where the element have to be removed.
** @value: Value tu remove.
**
** Delete a single value in the current list.
*/

void		pylst_remove(t_pylst **pylst, void *value)
{
	t_pylst		*prev;
	t_pylst		*curr;

	prev = NULL;
	curr = *pylst;
	while (curr && curr->value != value)
	{
		prev = curr;
		curr = curr->next;
	}
	if (!curr)
		return ;
	if (!prev)
		*pylst = (*pylst)->next;
	else
		prev->next = curr->next;
	free_pylst_node(&curr, 0);
}

/*
** pylst_strremove:
**
** @pylst: list where the element have to be removed.
** @value: Value tu remove.
**
** Like pylst_remove, but use a char * as value.
*/

void	pylst_strremove(t_pylst	**pylst, char *value)
{
	t_pylst		*prev;
	t_pylst		*curr;

	prev = NULL;
	curr = *pylst;
	while (curr && !ft_strequ(value, curr->value))
	{
		prev = curr;
		curr = curr->next;
	}
	if (!curr)
		return ;
	if (!prev)
		*pylst = (*pylst)->next;
	else
		prev->next = curr->next;
	free_pylst_node(&curr, 0);
}

/*
** pylst_replace:
**
** Arguments, in order :
** @pylst: choosen list.
** @index: index to modify.
** @value: value to change.
** @size: size of the new value.
** @ctype: C type of the new value.
**
** Facility to change an element of a specific index in a pylst.
** Is an equivalent in python to 'my_lst[x] = y'.
*/

void	pylst_replace(t_pylst *pylst, int index, ...)
{
	va_list		args;
	void		*value;
	int			size;
	enum e_ctype	ctype;


	va_start(args, index);
	value = va_arg(args, void *);
	size = va_arg(args, int);
	ctype = va_arg(args, enum e_ctype);
	pylst = index_pylst(pylst, index);
	pylst_clean_node(pylst);
	pylst->value = value;
	pylst->size = size;
	pylst->ctype = ctype;
	va_end(args);
}

/*
** in_pylst_chare:
**
** Arguments, in order :
** @str: searched string.
** @pylst: choosen list.
**
** Return True if str is a value of pylst else return False.
** ! If str is founded pylst->iter_item is set to NULL !
*/

int in_pylst_chare(char *str, t_pylst *pylst)
{
  char  *value;
  int ret;

  ret = 0;
  while (pylst_iter(pylst, (void **)&value))
  {
    if (value && ft_strequ(str, value))
    {
      ret = 1;
      pylst->iter_item = NULL;
      break ;
    }
  }
  return (ret);
}

/*
** str_chare_pylst:
**
** Arguments, in order :
** @pylst: choosen list.
**
** Return a string of python'style list of pylst.
** ! Work only if pylst values are char * !
*/

char	*str_chare_pylst(t_pylst *pylst)
{
	int		len;
	char	*str;
	char 	*value;

	len = 3;
	while (pylst_iter(pylst, (void **)&value) && value)
		len += ft_strlen(value) + 3;
	str = (char *)ft_memalloc((len + 1) * sizeof(char));
	len = 0;
	str[len++] = '[';
	while (pylst_iter(pylst, (void **)&value))
	{
		str[len++] = '\'';
		while (*value)
			str[len++] = *value++;
		str[len++] = '\'';
		str[len++] = ',';
	}
	str[len++] = ']';
	str[len++] = '\n';
	str[len] = 0;
	return (str);
}

/*
** print_pylst_chare:
**
** Arguments, in order :
** @pylst: choosen list.
**
** Print a python'style list of string.
** ! Work only if pylst values are char * !
*/

void	print_pylst_chare(t_pylst *pylst)
{
  char  *value;
  int first;

  first = 1;
  if (!(pylst))
  {
	  ft_printf("Empty list.\n");
	  return ;
  }
  ft_printf("[");
  while (pylst_iter(pylst, (void **)&value))
  {
    if (!first)
      ft_printf(",", value);
    ft_printf("'%s'", value);
    first = 0;
  }
  ft_printf("]\n");
}
