/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   environ_setter.h                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/07 10:31:55 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/07 10:46:47 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef ENVIRON_SETTER_H
# define ENVIRON_SETTER_H

void	ft_setenv(char *variable, char *value);
void	ft_unsetenv(char *variable);
char	*ft_getenv(char *variable);

#endif
