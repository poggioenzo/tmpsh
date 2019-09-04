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

#ifndef CD_CANON_H
# define CD_CANON_H

void		retrieve_prev(char *absfile, char *curr_file, char **prev_file);
void		remove_double_slash(char *path);
void		remove_dot(char *absolute, char *position);
void		reset_previous_dir(char *abspath, char **curr_file);
int			next_fileis(char *relpath, char *expected_name);

void		canonicalize(char *path);

#endif
