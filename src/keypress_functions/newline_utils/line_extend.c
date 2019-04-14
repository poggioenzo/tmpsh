#include "line_extend.h"
#include "t_operand_allocation.h"
#include "newline_keypress.h"
#include "line_utils.h"
#include "char_utils.h"
#include "t_char_insert.h"
#include "libft.h"

/*
** fill_operand_table:
**
** Fill up the a char ** element with all needed strings
** to prepare the prompt whenever the shell is still nested.
*/

static char	**fill_operand_table(void)
{
	char	**operand_strings;

	if (!(operand_strings = (char **)MALLOC(sizeof(char *) * NBRE_OPERAND + 100))) /// AVOID +100
		return (NULL);
	operand_strings[CMDSUBST] = CMDSUBST_STR;
	operand_strings[BRACEPARAM] = BRACEPARAM_STR;
	operand_strings[CURSH] = CURSH_STR;
	operand_strings[SUBSH] = SUBSH_STR;
	operand_strings[DQUOTE] = DQUOTE_STR;
	operand_strings[QUOTE] = QUOTE_STR;
	operand_strings[CMDAND ^ SEPARATOR] = CMDAND_STR;
	operand_strings[CMDOR ^ SEPARATOR] = CMDOR_STR;
	operand_strings[PIPE ^ SEPARATOR] = PIPE_STR;
	return (operand_strings);
}

/*
** free_operand_table:
**
** Free a char ** pointer and set it to NULL.
*/

static int		free_operand_table(char ***operand_strings, int status)
{
	FREE(*operand_strings);
	*operand_strings = NULL;
	return (status);
}

/*
** fill_all_strings:
**
** Use the array allocated by fill_operand_table to prepare the locked part of 
** the new added line. Add operand in their apparition order.
*/

static int		fill_all_strings(char ***operand_strings, t_operand *operand_list, \
				char **joined_separator)
{
	int		allocated;
	char	*tmp_str;
	char	*new_operand;

	if (!(*joined_separator = ft_strnew(0)))
		return (MALLOC_ERROR);
	tmp_str = " ";
	while (operand_list)
	{
		allocated = FALSE;
		new_operand = (*operand_strings)[operand_list->type % SEPARATOR];
		if (operand_list->next)
		{
			allocated = TRUE;
			if (!(new_operand = ft_strjoin(new_operand, tmp_str)))
				return (MALLOC_ERROR);
		}
		*joined_separator = ft_fstrjoin(joined_separator, &new_operand, 1, allocated);
		if (*joined_separator == NULL)
			return (MALLOC_ERROR);
		operand_list = operand_list->next;
	}
	return (MALLOC_SUCCESS);
}

/*
** format_operand_string:
**
** Prepare elements to set all operand string in a new t_line node,
** and set them all with fill_all_strings.
**
** return value:
** - MALLOC_SUCCESS if the string have been formated properly, MALLOC_ERROR
** otherwise.
*/

static int	format_operand_string(t_operand *operand_list, char **operand_str)
{
	int		status;
	char	**operand_strings;
	char	*joined_separator;

	if (!(operand_strings = fill_operand_table()))
		return (MALLOC_ERROR);
	if (!(*operand_str = (char *)MALLOC(sizeof(char) * 3)))
		return (free_operand_table(&operand_strings, MALLOC_ERROR));
	ft_strcpy(*operand_str, "> ");
	status = fill_all_strings(&operand_strings, operand_list, &joined_separator);
	free_operand_table(&operand_strings, 0);
	if (status == MALLOC_ERROR)
		return (ft_strdel_out(operand_str, MALLOC_ERROR));
	*operand_str = ft_fstrjoin(&joined_separator, operand_str, TRUE, TRUE);
	return (*operand_str ? MALLOC_SUCCESS : MALLOC_ERROR);
}

/*
** add_new_line:
**
** Extend into the current shell, when it's nested, a new line.
** Format this new line depending of the current operand chained list.
*/

int			add_new_line(t_line *shell_repr, t_operand *operand_list, \
				t_cursor *cursor)
{
	char	*operand_str;
	int		status;

	if (push_end_line(&shell_repr) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	if (format_operand_string(operand_list, &operand_str) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	shell_repr = get_last_line(shell_repr);
	status = insert_string(&shell_repr->chars, operand_str, TRUE);
	ft_strdel(&operand_str);
	if (status == MALLOC_ERROR)
		return (status);
	cursor->row = shell_repr->position;
	cursor->column = char_lst_len(shell_repr->chars);
	return (status);
}
