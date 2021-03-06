/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   grammar_print_attributes.c                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/03 21:47:26 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/03 21:47:29 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include "tmpsh.h"

static void		ft_puthidestr(char *str)
{
	while (*str)
	{
		if (*str == '\t')
			ft_putstr("\\t");
		else if (*str == '\n')
			ft_putstr("\\n");
		else if (*str == '\r')
			ft_putstr("\\r");
		else if (*str == '\v')
			ft_putstr("\\v");
		else if (*str == '\f')
			ft_putstr("\\f");
		else
			ft_putchar(*str);
		str++;
	}
}

void			print_opening_tags(void)
{
	char	*value;
	char	*key;

	ft_printf("opening_tags:\n");
	ft_printf("{\n");
	while (ht_iter(g_grammar->opening_tags, &key, (void **)&value))
		ft_printf("    \"%s\" : \"%s\",\n", key, value);
	ft_printf("}\n");
}

void			print_spaces(void)
{
	ft_printf("spaces:\n[");
	ft_puthidestr(g_grammar->spaces);
	ft_printf("]\n");
}

void			print_leaf_op(void)
{
	char *operator;

	ft_printf("leaf_op:\n");
	ft_printf("[");
	while (iter_pylst(g_grammar->leaf_op, (void **)&operator))
	{
		ft_printf("'");
		ft_puthidestr(operator);
		ft_printf("',\n");
	}
	ft_printf("]\n");
}

void			print_dquotes_opening_tags(void)
{
	char	*value;
	char	*key;

	ft_printf("dquotes_opening_tags:\n");
	ft_printf("{");
	while (ht_iter(g_grammar->dquotes_opening_tags, &key, (void **)&value))
		ft_printf("\"%s\" : \"%s\", ", key, value);
	ft_printf("}\n");
}
