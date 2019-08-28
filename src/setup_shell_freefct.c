
#include "libft.h"
#include "ast.h"
#include "acb.h"
#include "redirectionfd.h"
#include "tagstokens.h"

void setup_shell_freefct(void)
{
    setup_freefct();
    g_free_fct[_ast] = free_ast_type;
    g_free_fct[_acb] = free_acb_type;
    g_free_fct[_redfd] = free_redfd_type;
}
