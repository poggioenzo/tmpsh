#include <sys/stat.h>

int			file_size(char *filename)
{
	struct stat		inode;

	if (stat(filename, &inode) == -1)
		return (-1);
	return (inode.st_size);
}
