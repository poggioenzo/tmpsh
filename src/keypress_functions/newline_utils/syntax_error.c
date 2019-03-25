#include "libft.h"
#include "tmpsh.h"

/*
** syntax_error:
**
** Small utils to write the char who is raising a syntax error.
*/

int		syntax_error(char operator)
{
	ft_dprintf(2, "tmpsh: Invalid syntax near %c\n", operator);
	return (invalid_syntax);
}
