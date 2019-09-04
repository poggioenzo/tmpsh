#include "tagstokens.h"

void routine_tagstokens(t_tagstokens **self, char *shell_content)
{
	free_pylst(&g_actual_alias, 42);
	free_pylst(&g_passed_alias, 42);
    free_pylst(&g_heredocs, 42);
	g_aliasindepth = 0;
	input_init_tagstokens(self, shell_content);
}
