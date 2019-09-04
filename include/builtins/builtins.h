/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   determine_bytes.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/27 15:04:52 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/27 15:04:55 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */


#ifndef BUILTINS_H
# define BUILTINS_H

int			built_cd(char **args, char **environ);
int			built_exit(char **args, char **environ);
int			built_setenv(char **args, char **environ);
int			built_unsetenv(char **args, char **environ);
int			built_set(char **args, char **environ);
int			built_unset(char **args, char **environ);
int			built_env(char **args, char **environ);
int			built_echo(char **args, char **environ);
int			built_hash(char **argv, char **environ);
int			built_fg(char **argv, char **environ);
int			built_bg(char **argv, char **environ);
int			built_jobs(char **argv, char **environ);
int			built_alias(char **argv, char **environ);
int			built_unalias(char **argv, char **environ);
int			built_export(char **argv, char **environ);
int			built_type(char **argv, char **environ);

void		setup_builtins(void);

#endif
