#include "replace_home.h"
#include "libft.h"

char		*replace_home(char *filename)
{
	char	*home;
	int		home_len;
	char	*new_name;
	int		new_len;

	if (!ft_start_with(filename, "~"))
		return (ft_strdup(filename));
	if (!(home = ft_getenv("HOME")))
		return (ft_strdup(filename));
	home_len = ft_strlen(home);
	new_len = home_len + (ft_strlen(filename) - 1) + 1;
	if (!(new_name = (char *)MALLOC(sizeof(char) * new_len)))
		return (NULL);
	ft_strcpy(new_name, home);
	ft_strcpy(new_name + home_len, filename + 1);
	return (new_name);
}
