/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   determine_bytes.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/27 15:04:52 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/27 15:04:55 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "line_extend.h"
#include "newline_keypress.h"
#include "line_utils.h"
#include "char_utils.h"
#include "t_char_insert.h"
#include "libft.h"

/*
** lower_str:
**
** Set all character of a string in lowercase.
*/

void		lower_str(char *str)
{
	while (*str)
	{
		*str = ft_tolower(*str);
		str++;
	}
}

/*
** fill_all_strings:
**
** Use the array allocated by fill_operand_table to prepare the locked part of
** the new added line. Add operand in their apparition order.
*/

static void	fill_all_strings(t_pylst *stack, char **joined_separator)
{
	char	*tmp_str;
	char	*new_operand;

	*joined_separator = ft_strnew(0);
	tmp_str = " ";
	while (iter_pylst(stack, (void **)&new_operand))
	{
		new_operand = ft_strdup(new_operand);
		lower_str(new_operand);
		if (stack->next)
			new_operand = ft_fstrjoin(&new_operand, &tmp_str, true, false);
		*joined_separator = \
					ft_fstrjoin(joined_separator, &new_operand, true, true);
		stack = stack->next;
	}
}

/*
** format_operand_string:
**
** Prepare elements to set all operand string in a new t_line node,
** and set them all with fill_all_strings.
*/

static void	format_operand_string(t_pylst *stack, char **operand_str)
{
	char	*joined_separator;

	*operand_str = (char *)ft_memalloc(sizeof(char) * 3);
	ft_strcpy(*operand_str, "> ");
	fill_all_strings(stack, &joined_separator);
	*operand_str = ft_fstrjoin(&joined_separator, operand_str, TRUE, TRUE);
}

/*
** add_new_line:
**
** Extend into the current shell, when it's nested, a new line.
** Format this new line depending of the current operand chained list.
*/

void		add_new_line(t_line *shell_repr, t_tagstokens *tagstok, \
				t_cursor *cursor)
{
	char	*operand_str;

	push_end_line(&shell_repr);
	format_operand_string(tagstok->stack, &operand_str);
	shell_repr = get_last_line(shell_repr);
	insert_string(&shell_repr->chars, operand_str, true);
	ft_strdel(&operand_str);
	cursor->row = shell_repr->position;
	cursor->column = char_lst_len(shell_repr->chars);
}
