#include "libft.h"
#include "tmpsh.h"

void	show_tab(t_ht_table *table)
{
	char *key;
	t_ht_alveol *alveol;
	int index = 0;

	while (index < table->size)
	{
		ft_printf("%d:", index);
		alveol = table->items[index];
		while (alveol)
		{
			ft_printf("'%s':'%s', ", alveol->key, alveol->value);
			alveol = alveol->next;
		}
		ft_printf("\n");
		index++;
	}

}


