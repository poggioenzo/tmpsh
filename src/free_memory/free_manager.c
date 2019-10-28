/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   determine_bytes.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/27 15:04:52 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/28 10:21:28 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include "freeing.h"
#include "acb.h"
#include "ast.h"
#include "redirectionfd.h"
#include "heredocs.h"

/*
** setup_freefct:
**
** Prepare our global array of t_free_fct with each freeing
** function according to each data type.
*/

void		setup_freefct(void)
{
	g_free_fct[_ptr] = free_ptr;
	g_free_fct[_chare] = free_chare;
	g_free_fct[_charee] = free_charee;
	g_free_fct[_pylst] = free_pylst_type;
	g_free_fct[_hash_table] = free_hash_table_type;
	g_free_fct[_job] = free_job_type;
	g_free_fct[_hash_exec] = free_hash_exec_type;
	g_free_fct[_acb] = free_acb_type;
	g_free_fct[_ast] = free_ast_type;
	g_free_fct[_redfd] = free_redfd_type;
	g_free_fct[_static] = free_static_type;
	g_free_fct[_heredocs] = free_heredocs_type;
}
