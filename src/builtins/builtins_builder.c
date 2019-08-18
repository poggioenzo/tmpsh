#include "libft.h"
#include "builtins.h"

t_ht_table		*g_builtins;

void		setup_builtins(void)
{
	ht_new_table(&g_builtins, 17, 30);
	insert_value(g_builtins, "cd", built_cd, _ptr);
	insert_value(g_builtins, "exit", built_exit, _ptr);
	insert_value(g_builtins, "setenv", built_setenv, _ptr);
	insert_value(g_builtins, "env", built_env, _ptr);
	insert_value(g_builtins, "echo", built_echo, _ptr);
}
