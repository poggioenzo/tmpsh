/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   determine_bytes.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/27 15:04:52 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/30 15:36:02 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FILE_RIGHTS_H
# define FILE_RIGHTS_H

char	*check_rights(char *filename, int opts, t_bool free, \
		t_bool print_error);

# define R			0b00001
# define W			0b00010
# define X			0b00100
# define F			0b01000
# define VERBOSE	0b10000

#endif
