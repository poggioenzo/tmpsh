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
	ft_memdel(&hash_exec);
}
