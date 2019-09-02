#include "libft.h"

/*
** alveol_iterator:
**
** @table: table selected for iteration.
**
** Utils to parse each alveol of an hash table one by one.
** Go through each item in their index order, and parse each time
** the entire chained list of alveol.
**
** return : - next alveol to use on success.
**			- NULL if the iteration is over.
*/

static t_ht_alveol	*alveol_iterator(t_ht_table *table)
{
	while (table->iter_index < table->size || table->iter_alveol)
	{
		if (!table->iter_alveol)
			table->iter_alveol = table->items[table->iter_index++];
		else
			table->iter_alveol = table->iter_alveol->next;
		if (table->iter_alveol)
			return (table->iter_alveol);
	}
	table->iter_index = 0;
	return (NULL);
}

/*
** ht_iter:
**
** @table: table selected for iteration.
** @key: char * pointer to get the next key.
** @value: char * pointer to get next value.
**
** Allow the iteration of an hash table. Wrapper of alveol_iterator.
** ! No change on the hash table should be done during the iteration !
**
** return : - 1 if an next element is found.
**			- 0 if the iteration is over.
*/

int					ht_iter(t_ht_table *table, char **key, void **value)
{
	t_ht_alveol		*next_alveol;

	next_alveol = alveol_iterator(table);
	if (!next_alveol)
		return (0);
	*key = next_alveol->key;
	*value = next_alveol->value;
	return (1);
}
