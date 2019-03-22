#include "char_concatenation.h"
#include "libft.h"
#include "t_char_utils.h"
#include "screen_size.h"

static int		get_repr_len(t_char *char_lst, t_cursor *cursor, int line)
{
	int		line_len;

	line_len = 0;
	line_len += char_lst_len(char_lst);
	if (cursor->row == line)
	{
		if (cursor->column == line_len)
			line_len += 1;
		line_len += ft_strlen(g_caps->video) + ft_strlen(g_caps->reset_video);
	}
	line_len += 1;
	return (line_len);
}

static void	add_cursor_repr(char *line, int *str_index, char cursor_letter)
{
	ft_strcpy(line + *str_index, g_caps->video);
	*str_index += ft_strlen(g_caps->video);
	line[*str_index] = cursor_letter;
	*str_index += 1;
	ft_strcpy(line + *str_index, g_caps->reset_video);
	*str_index += ft_strlen(g_caps->reset_video);
}


char		*format_char_lst(t_char *char_lst, t_cursor *cursor, int line)
{
	char	*line_repr;
	int		line_len;
	int		index;
	int		cursor_displayed;

	line_len = get_repr_len(char_lst, cursor, line);
	if (!(line_repr = (char *)malloc(sizeof(char) * (line_len))))
		return (NULL);
	index = 0;
	cursor_displayed = FALSE;
	while (char_lst)
	{
			if (line == cursor->row && cursor->column == char_lst->position)
			{
				add_cursor_repr(line_repr, &index, char_lst->letter);
				cursor_displayed = TRUE;
			}
			else
				line_repr[index++] = char_lst->letter;
			char_lst = char_lst->next;
	}
	if (cursor_displayed == FALSE && line == cursor->row)
		add_cursor_repr(line_repr, &index, ' ');
	line_repr[index] = '\0';
	return (line_repr);
}

char			*concat_shell(t_line *prompt_lines, t_cursor *cursor, \
		int *total_lines)
{
	char	*shell_str;
	char	*new_line;
	int		line_len;
	t_win	window;
	char	*newline_tmp;

	if (!(shell_str = ft_strnew(0)))
		return (NULL);
	*total_lines = 0;
	screen_size(&window);
	while (prompt_lines)
	{
		if (!(new_line = format_char_lst(prompt_lines->chars, cursor, \
						prompt_lines->position)))
			return (NULL);
		if (!(shell_str = ft_fstrjoin(&shell_str, &new_line, 1, 1)))
			return (NULL);
		line_len = char_lst_len(prompt_lines->chars);
		if (cursor->row == prompt_lines->position && cursor->column == line_len)
			line_len++;
		*total_lines += line_len / window.ws_col;
		*total_lines += line_len % window.ws_col > 0;
		prompt_lines = prompt_lines->next;
		newline_tmp = "\n";
		if (prompt_lines)
			shell_str = ft_fstrjoin(&shell_str, &newline_tmp, 1, 0);
	}
	return (shell_str);
}

char			*render_shell(t_line *prompt_lines)
{
	char	*shell_str;
	char	*new_line;
	char	*newline_tmp;
	t_cursor	fake_cursor;

	if (!(shell_str = ft_strnew(0)))
		return (NULL);
	fake_cursor = (t_cursor){.row = -1, .column = -1};
	while (prompt_lines)
	{
		if (!(new_line = format_char_lst(prompt_lines->chars, &fake_cursor, \
						prompt_lines->position)))
			return (NULL);
		if (!(shell_str = ft_fstrjoin(&shell_str, &new_line, 1, 1)))
			return (NULL);
		prompt_lines = prompt_lines->next;
		newline_tmp = "\n";
		if (prompt_lines)
			shell_str = ft_fstrjoin(&shell_str, &newline_tmp, 1, 0);
	}
	return (shell_str);
}
