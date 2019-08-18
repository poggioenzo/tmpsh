
#ifndef BUILTINS_H
# define BUILTINS_H

int			built_cd(char **args, char **environ);
int			built_exit(char **args, char **environ);
int			built_setenv(char **args, char **environ);
int			built_env(char **args, char **environ);
int			built_echo(char **args, char **environ);

void		setup_builtins(void);

#endif
