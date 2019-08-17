/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   str_tagstokens.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/16 16:49:34 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/16 16:58:05 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdio.h>
#include "tmpsh.h"
#include "libft.h"
#include "globals.h"
#include "iter_tagstokens.h"

// char *str_chare_pylst(t_pylst pylst)
// {
//   int sum;
//
//   sum = 0;
//
// }

static	int		str_get_length(t_tagstokens *self, int *spacing)
{
	int		ret;
	int		len_tag;
	int		len_token;
	char	*tag;
	char	*token;

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

static	void	fill_tags_tokens(t_tagstokens *self, char *str, int *spacing)
{
	char	*tag;
	char	*token;
	int		i;
	int		remove;
	int		countdown;

	i = 0;
	remove = 0;
	countdown = 2;
	while (countdown--)
	{
		while (iter_tagstokens(self, &token, &tag))
		{
			while ((countdown ? *tag : *token))
				str[i++] = (countdown ? *tag++ : *token++);
			while (i - remove < spacing[self->iter])
				i++;
		}
		i--;
		str[i++] = '\n';
		remove = i;
	}
	str[i] = 0;
}

char			*str_tagstokens(t_tagstokens *self)
{
	char	*str;
	int		len;
	int		*spacing;

	// LEAKS + NORM = SHIT
	spacing = (int *)ft_memalloc(self->length * sizeof(int));
	len = (str_get_length(self, spacing) + 1) * 2 + 1;
	str = (char *)ft_memalloc(len);
	ft_memset((void *)str, 32, len - 1);
	fill_tags_tokens(self, str, spacing);
	str = ft_strjoin(str, "Stack: ");
	str = ft_strjoin(str, str_chare_pylst(self->stack));
	str = ft_strjoin(str, "Valid: ");
	str = ft_strjoin(str, (self->valid) ? GREEN"True"WHITE : RED"False"WHITE);
	str = ft_strjoin(str, " | Incomplete: ");
	str = ft_strjoin(str, (self->incomplete) ? RED"True"WHITE : GREEN"False"WHITE);
	str = ft_strjoin(str, " | Tokken Error: '");
	str = ft_strjoin(str, (self->token_error) ? self->token_error: "");
	str = ft_strjoin(str, "' | Length: ");
	str = ft_strjoin(str, ft_itoa(self->length));
	str = ft_strjoin(str, "\n");
	return (str);
}

void			print_tagstokens(t_tagstokens *self)
{
	ft_printf(str_tagstokens(self));
}

//\nValid: FALSE | Incomplete: FALSE | Token_error: "
// | Length:
