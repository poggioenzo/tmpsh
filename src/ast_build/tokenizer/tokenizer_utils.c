#include "tmpsh.h"
#include "libft.h"

int ops_begin_with(char *pattern, t_pylst *leaf_op)
{
  int     i;
  char    *leaf;
  t_bool  ret;

  ret = FALSE;
  i = ft_strlen(pattern);
  while (pylst_iter(leaf_op,(void **) &leaf))
    if (ft_strnequ(pattern, leaf, i))
    {
      ret = TRUE;
      leaf_op->iter_item = NULL;
      break ;
    }
  return (ret);
}
