#include "replace_home.h"
#include <pwd.h>
#include "libft.h"

/*
** getuser_home:
**
** Retrieve an user HOME according to his username
** or his uid.
*/

char		*getuser_home(char *username, int uid)
{
	struct passwd	*user_info;
	char			*home_dir;

	user_info = NULL;
	if (username)
		user_info = getpwnam(username);
	else if (uid)
		user_info = getpwuid(uid);
	if (!user_info)
		return (NULL);
	if (!(home_dir = ft_strdup(user_info->pw_dir)))
		exit(-1);
	return (home_dir);
}

/*
** user_home:
**
** When a username is found after a '~', get this username
** and get his home directory.
** Remove his name from the filename when it's done.
*/


char		*specific_user_home(char *filename)
{
	char	*username;
	int		len;
	char	*user_home;

	len = 0;
	while (filename[len] && filename[len] != '/')
		len++;
	if (!(username = ft_strsub(filename, 0, len)))
		exit(-1);
	user_home = getuser_home(username, 0);
	FREE(username);
	ft_strmove(filename, filename + len);
	return (user_home);
}

/*
** replace_home:
**
** Replace in a filename the '~' (tilde) part if needed.
** Check if the tild need to be replaced by a specific user or
** if we user the home of the process owner. If no tild are present
** or if two of them are present at the start, avoid replacement.
**
** WARNING : allocated the a new string without freeing the old one.
**
** return value:
** - A new allocated filename with the tild replaced.
** - NULL if there is a probleme to get a user home, or if tild is followed by a number.
*/

char		*replace_home(char *filename)
{
	char		*new_filename;
	char		*user_home;

	if (!ft_start_with(filename, "~") || ft_start_with(filename, "~~"))
		new_filename = ft_strdup(filename);
	else
	{
		user_home = NULL;
		if (ft_isalpha(filename[1]))
			user_home = specific_user_home(filename + 1);
		else if (filename[1] == '\0' || filename[1] == '/')
			user_home = getuser_home(NULL, getuid());
		if (!user_home)
			return (NULL);
		filename = filename + 1;
		new_filename = ft_fstrjoin(&user_home, &filename, 1, 0);
	}
	if (!new_filename)
		exit(-1);
	return (new_filename);
}
