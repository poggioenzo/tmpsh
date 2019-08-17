/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pylst.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/10 09:56:55 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/16 12:50:20 by simrossi    ###    #+. /#+    ###.fr     */
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

void		setup_pyfreefct(void);
void		push_pylst(t_pylst **pylst, void *value, int size, int ctype);

/*
** Freeing function for each data type
*/

int		free_pylst(t_pylst **pylst, int status);
int		free_pylst_node(t_pylst **py_node, int status);

void			no_free(void *ptr);
void			free_chare(void *str_ptr);
void			free_charee(void *array_ptr);
void			free_inte(void *array_ptr);
void			free_pylst_type(void *pylst_ptr);
void			free_hash_table_type(void *table_ptr);

void	pylst_clean_node(t_pylst *node);
void	pylst_clean(t_pylst *pylst);

/*
** Manipulation lists
*/

t_pylst		*pylst_shacpy(t_pylst *pylst);
t_pylst		*pylst_deepcpy(t_pylst *pylst);

int			len_pylst(t_pylst *pylst);
t_pylst		*index_pylst(t_pylst *pylst, int index);
void	pylst_replace(t_pylst *pylst, int index, ...);
t_pylst		*slice_pylst(t_pylst *pylst, int from, int to);
char	*join_pylst(t_pylst *pylst, char *substr);
void	pylst_extend(t_pylst **start, t_pylst *end, int deep_cpy);
void	del_portion_pylst(t_pylst **pylst, int from, int to);
void	del_after_pylst(t_pylst **pylst, int index);
void	replace_pylst(t_pylst **old_pylst, t_pylst *new_pylst, int from, int to);
int		pylst_iter(t_pylst *pylst, void **value);
void		pylst_remove(t_pylst **pylst, void *value);
void	pylst_strremove(t_pylst	**pylst, char *value);
int in_pylst_chare(char *str, t_pylst *pylst);
void			*get_value_pylst(t_pylst *pylst, int index);


/*
** Printing
*/

void	print_pylst_chare(t_pylst *pylst);
char 	*str_chare_pylst(t_pylst *pylst);


#endif
