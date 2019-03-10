/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   prompt.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/10 13:30:03 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/10 13:50:06 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

#define MALLOC_ERROR	0
#define SUCCESS			1

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

/*
** insert_field:
**
** Whenever a flag is found, insert his value in the string.
*/

static int		insert_field(char **prompt, int index, char *(*data_func)(void))
{
	char	*new_prompt;
	char	*added_elem;
	char	*second_prompt_part;

	if (!(new_prompt = ft_strsub(*prompt, 0, index)))
		return (MALLOC_ERROR);
	if (!(added_elem = data_func()))
		return (ft_strdel_out(&new_prompt, MALLOC_ERROR));
	if (!(new_prompt = ft_fstrjoin(&new_prompt, &added_elem, 1, 1)))
		return (MALLOC_ERROR);
	second_prompt_part = (*prompt) + index + 2;
	if (!(new_prompt = ft_fstrjoin(&new_prompt, &second_prompt_part, 1, 0)))
		return (MALLOC_ERROR);
	ft_strdel(prompt);
	*prompt = new_prompt;
	return (SUCCESS);
}

/*
** parse_prompt_format:
**
** Go through a string which indicate the desired format for the prompt.
** Check if a flag %h, %u and %d is present, and replace it by the correponding
** value.
*/

char		*parse_prompt_format(char *format)
{
	char	*final_prompt;
	int		index;
	int		error;

	if (!(final_prompt = ft_strdup(format)))
		return (NULL);
	index = 0;
	error = 1;
	while (final_prompt[index] && error)
	{
		if (final_prompt[index] == '%' && final_prompt[index + 1] == 'h')
			error *= insert_field(&final_prompt, index, add_date);
		else if (final_prompt[index] == '%' && final_prompt[index + 1] == 'u')
			error *= insert_field(&final_prompt, index, add_user);
		else if (final_prompt[index] == '%' && final_prompt[index + 1] == 'd')
			error *= insert_field(&final_prompt, index, add_cwd);
		index++;
	}
	if (error == MALLOC_ERROR)
	{
		ft_strdel(&final_prompt);
		return (NULL);
	}
	return (final_prompt);
}

/*
** format_prompt:
**
** Check if the environnement variable PROMPT is set to format the displayed
** prompt.
** Set up a default format if the variable is not set.
**
** Avaible format :
** - %h : Display hour and minutes
** - %u : Display username
** - %d : Display the current directory
*/

char	*format_prompt(void)
{
	char	*default_format;
	int		options;

	default_format = getenv("PROMPT");
	if (!default_format)
		default_format = "%d %d %h %u %h plop $> ";
	return (parse_prompt_format(default_format));
}

int		main(int argc, char **argv)
{
	printf("%s\n", format_prompt());
	return (0);
}
