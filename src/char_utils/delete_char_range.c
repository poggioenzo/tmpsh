#include "delete_char_range.h"
#include "libft.h"
#include "char_utils.h"
#include "char_selection.h"
#include "char_concatenation.h"

/*
** delete_char_range:
**
** Delete inside a t_char list a range of t_char element, starting from from,
** going to to.
** Can return the string of the deleted pointer if expected.
**
** return value:
** - The string between from and to newly allocated, NULL if an allocation
** error occur.
** - Return NULL if the no string is expected, just free pointers.
*/

char	*delete_char_range(t_char *char_lst, t_char *from,\
				t_char *to, int get_str)
{
	t_char	*prev_char;
	char	*cutted_str;
	t_cursor	fake_cursor;

	fake_cursor = (t_cursor){.row = -1, .column = -1};
	cutted_str = NULL;
	if (!from)
		from = get_unlocked_char(char_lst);
	if (!to)
		get_last_char(char_lst, &to);
	if (!from || !to)
		return (get_str ? ft_strnew(0) : NULL);
	search_prev_char(char_lst, &prev_char, from);
	prev_char->next = to->next;
	to->next = NULL;
	if (get_str)
		cutted_str = format_char_lst(from, &fake_cursor, 0);
	free_t_char_lst(&from, 0);
	update_position(char_lst);
	return (cutted_str);
}
