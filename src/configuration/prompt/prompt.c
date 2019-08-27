/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   prompt.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/10 13:30:03 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/14 16:19:12 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include "prompt.h"

/*
** insert_field:
**
** Whenever a flag is found, insert his value in the string.
*/

static void	insert_field(char **prompt, int index, char *(*data_func)(void))
{
	char	*new_prompt;
	char	*added_elem;
	char	*second_prompt_part;

	if (!(new_prompt = ft_strsub(*prompt, 0, index)))
		exit(-1);
	added_elem = data_func();
	if (!(new_prompt = ft_fstrjoin(&new_prompt, &added_elem, 1, 1)))
		exit(-1);
	second_prompt_part = (*prompt) + index + 2;
	if (!(new_prompt = ft_fstrjoin(&new_prompt, &second_prompt_part, 1, 0)))
		exit(-1);
	ft_strdel(prompt);
	*prompt = new_prompt;
}

/*
** parse_prompt_format:
**
** Go through a string which indicate the desired format for the prompt.
** Check if a flag %h, %u and %d is present, and replace it by the correponding
** value.
*/

static char	*parse_prompt_format(char *format)
{
	char	*final_prompt;
	int		index;

	if (!(final_prompt = ft_strdup(format)))
		exit(-1);
	index = 0;
	while (final_prompt[index])
	{
		if (final_prompt[index] == '%' && final_prompt[index + 1] == 'h')
			insert_field(&final_prompt, index, add_date);
		else if (final_prompt[index] == '%' && final_prompt[index + 1] == 'u')
			insert_field(&final_prompt, index, add_user);
		else if (final_prompt[index] == '%' && final_prompt[index + 1] == 'd')
			insert_field(&final_prompt, index, add_cwd);
		index++;
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

char		*format_prompt(void)
{
	char	*default_format;

	default_format = getenv("PROMPT42");
	if (!default_format)
		default_format = "%d $> ";
	return (parse_prompt_format(default_format));
}
