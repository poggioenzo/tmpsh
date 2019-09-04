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
	insert_value(g_builtins, "cd", built_cd, _ptr);
	insert_value(g_builtins, "exit", built_exit, _ptr);
	insert_value(g_builtins, "setenv", built_setenv, _ptr);
	insert_value(g_builtins, "unsetenv", built_unsetenv, _ptr);
	insert_value(g_builtins, "unset", built_unset, _ptr);
	insert_value(g_builtins, "set", built_set, _ptr);
	insert_value(g_builtins, "export", built_export, _ptr);
	insert_value(g_builtins, "env", built_env, _ptr);
	insert_value(g_builtins, "echo", built_echo, _ptr);
	insert_value(g_builtins, "alias", built_alias, _ptr);
	insert_value(g_builtins, "unalias", built_unalias, _ptr);
	insert_value(g_builtins, "bg", built_bg, _ptr);
	insert_value(g_builtins, "fg", built_fg, _ptr);
	insert_value(g_builtins, "jobs", built_jobs, _ptr);
	insert_value(g_builtins, "type", built_type, _ptr);
	insert_value(g_builtins, "hash", built_hash, _ptr);
}
