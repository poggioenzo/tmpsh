/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   hash_table.h                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/26 19:50:57 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/15 11:51:27 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef HASH_TABLE_H
# define HASH_TABLE_H

typedef struct s_ht_alveol	t_ht_alveol;

struct				s_ht_alveol
{
	char		*key;
	void		*value;
	int			ctype;
	t_ht_alveol	*next;
};

typedef struct		s_ht_table
{
	int			size;
	int			count;
	int			seed;
	int			iter_index;
	t_ht_alveol	*iter_alveol;
	t_ht_alveol	**items;
}					t_ht_table;

int					free_hash_table(t_ht_table **hash_table, int status);
void				ht_new_table(t_ht_table **hash_table, int seed, int size);

void				delete_value(t_ht_table *table, char *key);
void				*search_value(t_ht_table *table, char *key);
void				**search_value_addr(t_ht_table *table, char *key);
void				insert_value(t_ht_table *table, char *key, void *value, \
								int ctype);
int					free_alveol(t_ht_alveol **alveol, int status);
int					free_alveol_list(t_ht_alveol **alveol, int status);
int					hash_function(const char *string, int seed, int size);

int					ht_iter(t_ht_table *table, char **key, void **value);

void				empty_ht(t_ht_table *table);
/*
** Debug functions.
*/

void				show_tab(t_ht_table *table);
#endif
