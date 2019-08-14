#include <stdio.h>
#include "tmpsh.h"
#include "libft.h"
#include "globals.h"

void print_pylst(t_pylst *pylst)
{
  char  *value;

  while (pylst_iter(pylst,(void **) &value))
    ft_printf("%s\n", value);
}

int in_pylst_chare(t_pylst *pylst, char *str)
{
  char  *value;

  while (pylst_iter(pylst,(void **) &value))
  {
    if (value && !ft_strcmp(str, value))
      return (TRUE);
  }
  return (FALSE);
}

int ops_begin_with(char *pattern, t_pylst *leaf_op)
{
  int i;
  char  *leaf;


  i = ft_strlen(pattern);
  while (pylst_iter(leaf_op,(void **) &leaf))
    if (!ft_strncmp(pattern, leaf, i))
      return (TRUE);
  return (FALSE);
}

void *add_token(char *current, t_pylst *tokens)
{
  if (*current)
  {
    push_pylst(&tokens, current, ft_strlen(current) + 1, _chare);
    ft_bzero(current, ft_strlen(current));
  }
}

int span(char *command,t_pylst *tokens,char *current)
{
  int length_cmd;
  int j;
  char *to_add;

  j = 1;
  length_cmd = ft_strlen(command);
  current = add_token(current,tokens);
  ft_printf("length_cmd %d\n", length_cmd);
  while (j <= g_grammar->maxlen_leaf_op
        && j < length_cmd
        && ops_begin_with((to_add = ft_strndup(command, j)), g_grammar->leaf_op)
        && !(ft_strdel(&to_add)))
  {
    j += 1;
  }
  to_add = ft_strndup(command, j);
  ft_printf("|%s|\n", to_add);
  if (in_pylst_chare(g_grammar->leaf_op, to_add))
  {
    ft_printf( "YOLO\n" );
    push_pylst(&tokens, to_add, ft_strlen(to_add) + 1, _chare);
    ft_printf( "YOLO\n");
  }
  else
    current = ft_strncat(current, command, 1);
  ft_printf("j %d\n", j);
  return (j);


}


void tokenize(char *command, t_pylst *tokens)
{
  char *current;
  char *tmp;


  current = ft_strnew(ft_strlen(command));
  tokens = NULL;
  while (*command)
  {
    ft_printf("-> %c <- \n", *command);
    if (ops_begin_with((tmp = ft_strndup(command, 1)), g_grammar->leaf_op)
        && !ft_strdel(&tmp))
    {
      ft_printf("SPAN\n");
      command += span(command, tokens, current);
    }
    else
      command++;
  }
  print_pylst(tokens);
  ft_strdel(&current);

}
