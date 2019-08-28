#ifndef CD_FINDER_H
# define CD_FINDER_H

char		*get_oldpwd(void);
int			allowed_access(char *filename, int print_error);
char		*find_newdir(char *argument, int p_opt);

#endif
