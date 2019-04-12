/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pylst.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/10 09:56:55 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/10 13:19:47 by simrossi    ###    #+. /#+    ###.fr     */
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
};


void		setup_pyfreefct(void);
int			push_pylst(t_pylst **pylst, void *value, int size, int ctype);

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

#endif
