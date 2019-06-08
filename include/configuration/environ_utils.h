#ifndef ENVIRON_UTILS_H
# define ENVIRON_UTILS_H

void	duplicate_environ(char **environ);
void	ft_setenv(char *variable, char *value);
void	ft_unsetenv(char *variable);
char	*ft_getenv(char *variable);

#endif
