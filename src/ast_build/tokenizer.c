#include <stdio.h>
#include "tmpsh.h"
#include "libft.h"
#include "globals.h"

void qwerty(void)
{
  printf("YOLO\n");
}

void print_pylst(t_pylst *pylst)
{
  char  *value;

  while (pylst_iter(pylst, &value))
    ft_printf("%s\n", value);
}

int ops_begin_with(char *pattern, t_pylst *leaf_op)
{
  int i;
  char  *value;

  i = ft_strlen(pattern);
  while (pylst_iter(leaf_op, &value))
    if (ft_strncmp(pattern, value, i))
      return (TRUE);
  return (FALSE);
}

char *add_token(char *current, t_pylst *tokens)
{
  if (current)
  {
    push_pylst(&tokens, current, ft_strlen(current), _chare);
    ft_bzero(current);
  }
  return current;
}







void tokenize(char *command, t_pylst *tokens)
{
  int i;
  int length_cmd;
  char *current;


  i = 0;
  length_cmd = ft_strlen(command);
  current = ft_memalloc(length_cmd)
  while (i< length_cmd)
  {
    if (ops_begin_with(command[i], g_grammar->leaf_op))
    {
      current = add_token(current,tokens);
      i += span(, tokens, )

    }
  }
  ft_strdel(&current);

}
