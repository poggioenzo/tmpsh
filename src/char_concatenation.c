#include "char_concatenation.h"
#include "libft.h"
#include "t_char_utils.h"
#include "screen_size.h"

static int		get_repr_len(t_char *char_lst, t_cursor *cursor, int line)
{
	int		line_len;

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
	if (!(line_repr = malloc(sizeof(char) * (line_len))))
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
