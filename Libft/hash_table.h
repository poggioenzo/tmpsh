/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   hash_table.h                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/26 19:50:57 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/26 19:51:20 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef HASH_TABLE_H
# define HASH_TABLE_H

typedef struct s_ht_alveol	t_ht_alveol;

struct				s_ht_alveol
{
	char		*key;
	char		*value;
	t_ht_alveol	*next;
};

typedef struct		s_ht_table
{
	int			size;
	int			count;
	int			seed;
	t_ht_alveol	**items;
}					t_ht_table;

int					free_hash_table(t_ht_table **hash_table, int status);
int					ht_new_table(t_ht_table **hash_table, int seed, int size);

void				delete_value(t_ht_table *table, char *key);
char				*search_value(t_ht_table *table, char *key);
int					insert_value(t_ht_table *table, char *key, char *value);
int					free_alveol(t_ht_alveol **alveol, int status);
int					free_alveol_list(t_ht_alveol **alveol, int status);
int					hash_function(const char *string, int seed, int size);

#endif
