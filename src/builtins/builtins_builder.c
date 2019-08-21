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
	insert_value(g_builtins, "env", built_env, _ptr);
	insert_value(g_builtins, "echo", built_echo, _ptr);
}
