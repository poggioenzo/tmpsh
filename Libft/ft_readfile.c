/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_readfile.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/27 16:11:46 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/14 10:05:32 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include <sys/stat.h>
#include <fcntl.h>

static int			file_size(char *filename)
{
	struct stat		inode;

	if (stat(filename, &inode) == -1)
		return (-1);
	return (inode.st_size);
}

char	*readfile(char *filename)
{
	int		len;
	char	*content;
	int		fd;
	int		ret;

	len = file_size(filename);
	fd = open(filename, O_RDONLY);
	if (fd == -1 || len == -1)
		return (NULL);
	if (!(content = MALLOC(sizeof(char) * (len + 1))))
		return (NULL);
	ret = read(fd, content, len);
	content[ret] = '\0';
	close(fd);
	return (content);
}

char	*fd_readfile(int fd)
{
	char	*content;
	int		readed;
	char	buffer[BUFF_SIZE + 1];
	char	*buffer_pointer;

	content = NULL;
	buffer_pointer = buffer;
	while ((readed = read(fd, buffer, BUFF_SIZE)))
	{
		buffer[readed] = '\0';
		if (content)
		{
			if (!(content = ft_fstrjoin(&content, &buffer_pointer + 0, 1, 0)))
				return (NULL);
		}
		else
		{
			if (!(content = ft_strdup(buffer)))
				return (NULL);
		}
	}
	return (content);
}
