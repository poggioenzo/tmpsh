/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   str_tagstokens.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/16 16:49:34 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/27 20:27:41 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "tagstokens.h"

static	size_t		str_get_length(t_tagstokens *self, size_t *spacing)
{
	size_t		ret;
	size_t		len_tag;
	size_t		len_token;
	char		*tag;
	char		*token;

	ret = 0;
	while (iter_tagstokens(self, &token, &tag))
	{
		len_tag = ft_strlen(tag);
		len_token = ft_strlen(token);
		ret += (len_token > len_tag) ? len_token : len_tag;
		spacing[self->iter] = ++ret;
	}
	return (ret);
}

static	void		fill_tags_tokens(t_tagstokens *self, char *str,\
									size_t *spacing)
{
	char		*tag;
	char		*token;
	size_t		i;
	size_t		remove;
	int			countdown;

	i = 0;
	remove = 0;
	countdown = 2;
	while (countdown--)
	{
		while (iter_tagstokens(self, &token, &tag))
		{
			while ((countdown ? *tag : *token))
			{
				str[i++] = (countdown ? *tag++ : *token++);
			}
			while (i - remove < spacing[self->iter])
				i++;
		}
		i--;
		str[i++] = '\n';
		remove = i;
	}
	str[i] = 0;
}

/*
** str_tagstokens:
**
** @self: actual tagstokens.
**
** Return a string representation of the tagstokens.
*/

char				*str_tagstokens(t_tagstokens *self)
{
	char		*str;
	int			len;
	size_t		*spacing;

	if (!(self->length))
		return (ft_strdup(YELLOW"Empty tagstokens\n"WHITE));
	spacing = (size_t *)ft_memalloc((self->length + 1) * sizeof(size_t));
	len = (str_get_length(self, spacing) + 1) * 2 + 1;
	str = (char *)ft_memalloc(len);
	ft_memset((void *)str, 32, len - 1);
	fill_tags_tokens(self, str, spacing);
	ft_memdel((void **)&spacing);
	str = free_join(str, "Stack: ", FALSE);
	str = free_join(str, str_chare_pylst(self->stack), TRUE);
	str = free_join(str, "Valid: ", FALSE);
	str = free_join(str, (self->valid) ? GTRUE : RFALSE, FALSE);
	str = free_join(str, " | Incomplete: ", FALSE);
	str = free_join(str, (self->incomplete) ? RTRUE : GFALSE, FALSE);
	str = free_join(str, " | Tokken Error: '", FALSE);
	str = free_join(str, (self->token_error) ? self->token_error : "", FALSE);
	str = free_join(str, "' | Length: ", FALSE);
	str = free_join(str, ft_itoa(self->length), TRUE);
	str = free_join(str, "\n", FALSE);
	return (str);
}

/*
** print_tagstokens:
**
** @self: tagstokens to print.
**
** If the tagstokens is allocated then a string version is displayed.
** Else an error message will prompt.
*/

void				print_tagstokens(t_tagstokens *self)
{
	char *to_print;

	if (self)
	{
		to_print = str_tagstokens(self);
		ft_printf(to_print);
		ft_strdel(&to_print);
	}
	else
		ft_printf(RED"Tagstokens Not Allocated\n"WHITE);
}
