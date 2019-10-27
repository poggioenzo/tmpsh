/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   routine_tagstokens.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/04 16:42:44 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/10/18 16:58:09 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "tagstokens.h"
#include "ttm.h"

static void	remove_end_line(char *str)
{
	char	*newline;

	if ((newline = ft_strchr(str, '\n')))
		ft_strcpy(str, newline);
	else
		ft_bzero(str, ft_strlen(str));
}

static void	remove_comments(char *str)
{
	int		escaped;

	escaped = false;
	while (*str)
	{
		if (*str == '\\' && escaped == false)
			escaped = true;
		else
		{
			if (*str == '#' && escaped == false)
				remove_end_line(str);
			escaped = false;
		}
		str++;
	}
}

void reset_routine(void)
{
	t_tags_tokens_monitor *self;

	self = NULL;
	is_newline_ttm(self, true);
	free_pylst(&g_actual_alias, 42);
	free_pylst(&g_passed_alias, 42);
	free_pylst(&g_heredocs, 42);
	g_aliasindepth = 0;
}

void		routine_tagstokens(t_tagstokens **self, char *shell_content)
{
	remove_comments(shell_content);
	reset_routine();
	input_init_tagstokens(self, shell_content);
}
