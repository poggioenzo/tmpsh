/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pylst.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/10 09:56:55 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/08/28 11:58:46 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef PYLST_H
# define PYLST_H

# include "libft.h"

/*
** struct s_pylst (aka t_pylst):
**
** Structure to create a chained list of value.
** Each value can be different C data type.
** The type must be store in the ctype attribute using
** the e_ctype enum.
*/

typedef	struct s_pylst	t_pylst;

struct		s_pylst
{
	void		*value;
	int			size;
	int			ctype;
	t_pylst		*next;
	t_pylst		*iter_item;
};

void		push_pylst(t_pylst **pylst, void *value, int size, int ctype);


int		free_pylst(t_pylst **pylst, int status);
int		free_pylst_node(t_pylst **py_node, int status);

void	pylst_clean_node(t_pylst *node);
void	pylst_clean(t_pylst *pylst);

/*
** Manipulation lists
*/

t_pylst		*pylst_shacpy(t_pylst *pylst);
t_pylst		*pylst_deepcpy(t_pylst *pylst);

int			len_pylst(t_pylst *pylst);
t_pylst		*index_pylst(t_pylst *pylst, int index);
void		*vindex_pylst(t_pylst *pylst, int index);
void		update_pylst(t_pylst *pylst, int index, ...);
t_pylst		*slice_pylst(t_pylst *pylst, int from, int to);



char		*join_pylst(t_pylst *pylst, char *substr);
void		pylst_extend(t_pylst **start, t_pylst *end, int deep_cpy);
void		del_portion_pylst(t_pylst **pylst, int from, int to);
void		del_after_pylst(t_pylst **pylst, int index);
void		replace_pylst(t_pylst **old_pylst, t_pylst *new_pylst, int from, int to);
int			iter_pylst(t_pylst *pylst, void **value);
void		remove_pylst(t_pylst **pylst, void *value);
void		strremove_pylst(t_pylst	**pylst, char *value);
void		*pop_pylst(t_pylst **pylst, int index);
int			str_in_pylst(t_pylst *pylst, char *search);
void		sort_pylst(t_pylst **pylst, int (*cmp)(t_pylst *, t_pylst *));
void	print_pylst_chare(t_pylst *pylst);
char 	*str_chare_pylst(t_pylst *pylst);
void	reverse_pylst(t_pylst **pylst);
int in_pylst_chare(char *str, t_pylst *pylst);

#endif
