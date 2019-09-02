#include "tmpsh.h"

void		store_word(t_char *word, t_char **save_tmp, int *in_word)
{
	*in_word = true;
	*save_tmp = word;
}
