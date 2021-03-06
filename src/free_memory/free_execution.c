/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   determine_bytes.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/27 15:04:52 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/17 13:58:17 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "tmpsh.h"
#include "libft.h"

void		free_job_type(void *job_ptr)
{
	t_job	**destroy_job;

	destroy_job = (t_job **)job_ptr;
	free_pylst(&(*destroy_job)->branches, 0);
	ft_strdel(&(*destroy_job)->command);
	ft_memdel(&job_ptr);
}

void		free_hash_exec_type(void *hash_exec)
{
	t_hash_exec		**removed_cache;

	removed_cache = (t_hash_exec **)hash_exec;
	ft_strdel(&(*removed_cache)->exec_file);
	ft_memdel((void **)hash_exec);
}

void		free_static_type(void *static_ptr)
{
	UNUSED(static_ptr);
	return ;
}
