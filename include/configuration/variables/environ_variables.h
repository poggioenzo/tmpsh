/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   environ_variables.h                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/08 13:23:43 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/08 13:23:55 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef ENVIRON_VARIABLES_H
# define ENVIRON_VARIABLES_H

void	ft_setenv(char *variable, char *value);
void	ft_unsetenv(char *variable);
char	*ft_getenv(char *variable);

#endif
