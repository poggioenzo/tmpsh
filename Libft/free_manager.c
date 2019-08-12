#include "libft.h"

/*
** setup_pyfreefct:
**
** Prepare our global array of t_free_fct with each freeing
** function according to each data type.
*/

void		setup_freefct(void)
{
	g_free_fct[_ptr] = no_free;
	g_free_fct[_chare] = free_chare;
	g_free_fct[_charee] = free_charee;
	g_free_fct[_inte] = free_inte;
	g_free_fct[_pylst] = free_pylst_type;
	g_free_fct[_hash_table] = free_hash_table_type;
}
