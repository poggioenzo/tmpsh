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

#include "libft.h"
#include "builtins.h"

t_ht_table		*g_builtins;

/*
** setup_builtins:
**
** Allocate builtin hash table.
** Using the hash_table with the builtin name as
** key, and a value of type : int (*builtin)(char **, char **)
** Store each available pointer function.
*/

void		setup_builtins(void)
{
	ht_new_table(&g_builtins, 17, 30);
	insert_value(g_builtins, "cd", built_cd, _static);
	insert_value(g_builtins, "exit", built_exit, _static);
	insert_value(g_builtins, "setenv", built_setenv, _static);
	insert_value(g_builtins, "unsetenv", built_unsetenv, _static);
	insert_value(g_builtins, "unset", built_unset, _static);
	insert_value(g_builtins, "set", built_set, _static);
	insert_value(g_builtins, "export", built_export, _static);
	insert_value(g_builtins, "echo", built_echo, _static);
	insert_value(g_builtins, "alias", built_alias, _static);
	insert_value(g_builtins, "unalias", built_unalias, _static);
	insert_value(g_builtins, "bg", built_bg, _static);
	insert_value(g_builtins, "fg", built_fg, _static);
	insert_value(g_builtins, "jobs", built_jobs, _static);
	insert_value(g_builtins, "type", built_type, _static);
	insert_value(g_builtins, "hash", built_hash, _static);
	insert_value(g_builtins, "pwd", built_pwd, _static);
}
