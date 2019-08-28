#include "libft.h"
#include "cd_canon.h"

/*
** canonicalize:
**
** From an absolute path, remove .. and . whenever it's possible.
** Edit the given path to be the absolute filename in his
** canonical form.
*/

void		canonicalize(char *path)
{
	char	*curr;

	remove_double_slash(path);
	curr = path;
	while (curr && *curr)
	{
		if (next_fileis(curr, "."))
			remove_dot(path, curr);
		else if (next_fileis(curr, ".."))
			reset_previous_dir(path, &curr);
		else
			curr = ft_strchr(curr + 1, '/');
	}
}
