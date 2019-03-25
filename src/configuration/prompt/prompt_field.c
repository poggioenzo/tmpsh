/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   prompt_field.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/10 16:12:45 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/10 16:12:54 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#ifdef __linux
 #include <time.h>
#endif

/*
** add_date:
**
** Get the current date, and format it to have
** only hour and minute, like hh:mm.
*/

char		*add_date(void)
{
	struct tm	*date;
	time_t		curr_timestamp;
	char		*time_tmp;
	char		*formatted_date;
	char		*colon_tmp;

	curr_timestamp = time(NULL);
	date = localtime(&curr_timestamp);
	if (!(time_tmp = ft_itoa(date->tm_hour)))
		return (NULL);
	colon_tmp = ":";
	if (!(formatted_date = ft_fstrjoin(&time_tmp, &colon_tmp, 1, 0)))
		return (NULL);
	if (!(time_tmp = ft_itoa(date->tm_min)))
	{
		ft_strdel(&formatted_date);
		return (NULL);
	}
	return (ft_fstrjoin(&formatted_date, &time_tmp, 1, 1));
}

/*
** add_user:
**
** Return an allocated string who contain the USER variable.
*/

char		*add_user(void)
{
	char	*user;

	user = getenv("USER");
	return (user ? ft_strdup(user) : NULL);
}

/*
** add_cwd:
**
** Return the current directory.
** Replace the beginning of the current directory by tild
** if it start by $HOME.
*/

char		*add_cwd(void)
{
	char	*home;
	char	*cwd;
	int		len_home;

	cwd = getcwd(NULL, 0);
	home = getenv("HOME");
	if (home && *home && cwd && ft_start_with(cwd, home))
	{
		len_home = ft_strlen(home);
		ft_strmove(cwd, cwd + len_home - 1);
		cwd[0] = '~';
	}
	return (cwd);
}
