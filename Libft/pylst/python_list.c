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
** vindex_pylst:
**
** Like index_pylst, but return the t_pylst->value element.
*/

void		*vindex_pylst(t_pylst *pylst, int index)
{
	t_pylst		*expect_node;

	expect_node = index_pylst(pylst, index);
	return (expect_node ? expect_node->value : NULL);
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

	concat_str = ft_strnew(0);
	while (pylst)
	{
		py_str = pylst->value;
		if (py_str)
			concat_str = ft_fstrjoin(&concat_str, &py_str, TRUE, FALSE);
		pylst = pylst->next;
		if (py_str && pylst)
			concat_str = ft_fstrjoin(&concat_str, &substr, TRUE, FALSE);
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
** iter_pylst:
**
** @pylst: chained list head selected to iterate.
** @value: void * pointer to get value one by one in the list.
**
** Used in a while loop to iterate over each element of a pylst.
** Make a for loop inspired from python.
** ! No change on the pylst should be done during the iteration !
** ! The list have to be iterate entirely (or reset iter_item) !
**
** return : - 1 if a next element if found.
**			- 0 if pylst is NULL, or if the entire list is parsed.
*/

int		iter_pylst(t_pylst *pylst, void **value)
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
** remove_pylst:
**
** @pylst: list where the element have to be removed.
** @value: Value tu remove.
**
** Delete a single value in the current list.
*/

void		remove_pylst(t_pylst **pylst, void *value)
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
** strremove_pylst:
**
** @pylst: list where the element have to be removed.
** @value: Value tu remove.
**
** Like remove_pylst, but use a char * as value.
*/

void	strremove_pylst(t_pylst **pylst, char *value)
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
** update_pylst:
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

void	update_pylst(t_pylst *pylst, int index, ...)
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
	if (size > 0)
	{
		pylst->value = ft_memalloc(size);
		ft_memcpy(pylst->value, value, size);
	}
	else
		pylst->value = value;
	pylst->size = size;
	pylst->ctype = ctype;
	va_end(args);
}

int			str_in_pylst(t_pylst *pylst, char *search)
{
	char	*tmp_value;

	while (pylst)
	{
		tmp_value = (char *)pylst->value;
		if (ft_strequ(search, tmp_value))
			return (1);
		pylst = pylst->next;
	}
	return (0);
}

/*
** insert_sort_pylst:
**
** Utils for sort_pylst. Insert a new element inside a sorted list.
*/

static void	insert_sort_pylst(t_pylst **new_pylst, t_pylst *new_node, \
		int (*cmp)(t_pylst *, t_pylst *))
{
	t_pylst		*prev;
	t_pylst		*curr;

	prev = NULL;
	curr = *new_pylst;
	while (curr && cmp(curr, new_node) <= 0)
	{
		prev = curr;
		curr = curr->next;
	}
	if (!prev)
		*new_pylst = new_node;
	else
		prev->next = new_node;
	if (curr)
		new_node->next = curr;
}

/*
** sort_pylst:
**
** @pylst: list to sort.
** @cmp: Compare function to perform the sort
**
** Sort the given chained list by performing an insert sort.
*/

void		sort_pylst(t_pylst **pylst, int (*cmp)(t_pylst *, t_pylst *))
{
	t_pylst		*sorted_pylst;
	t_pylst		*to_sort;
	t_pylst		*next;

	sorted_pylst = NULL;
	to_sort = *pylst;
	while (to_sort)
	{
		next = to_sort->next;
		to_sort->next = NULL;
		insert_sort_pylst(&sorted_pylst, to_sort, cmp);
		to_sort = next;
	}
	*pylst = sorted_pylst;
}



/*
** pop_pylst:
**
** Return a value and delete it from the pylst.
*/

void		*pop_pylst(t_pylst **pylst, int index)
{
	void		*pop_value;
	int			gold_index;

	gold_index = convert_neg_index(*pylst, index);
	pop_value = vindex_pylst(*pylst, gold_index);
	del_portion_pylst(pylst, gold_index, gold_index + 1);
	return (pop_value);
}

/*
** str_in_pylst:
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
  while (iter_pylst(pylst, (void **)&value))
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

	char *str;
	char *cara;

	if (!pylst)
		return ft_strdup("[]\n");
	cara = "['";
	str = join_pylst(pylst, "', '");
	str = ft_fstrjoin(&cara, &str, FALSE, TRUE);
	cara = "']\n";
	str = ft_fstrjoin(&str, &cara, TRUE, FALSE);
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
  if (!(pylst))
  {
	  ft_printf("Empty list.\n");
	  return ;
  }
  ft_printf(str_chare_pylst(pylst));
}


void	reverse_pylst(t_pylst **pylst)
{
	t_pylst		*reverse_lst;
	t_pylst		*precedence;
	t_pylst		*next;

	if (!*pylst)
		return ;
	precedence = NULL;
	reverse_lst = *pylst;
	while (reverse_lst)
	{
		next = reverse_lst->next;
		reverse_lst->next = precedence;
		precedence = reverse_lst;
		reverse_lst = next;
	}
	*pylst = precedence;
}
