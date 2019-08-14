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

int ops_begin_with(char *pattern, t_pylst *leaf_op)
{
  int i;
  char  *value;

  i = ft_strlen(pattern);
  while (pylst_iter(leaf_op,(void **) &value))
    if (ft_strncmp(pattern, value, i))
      return (TRUE);
  return (FALSE);
}

// char *add_token(char *current, t_pylst *tokens)
// {
//   if (current)
//   {
//     push_pylst(&tokens, current, ft_strlen(current), _chare);
//     ft_bzero(current, ft_strlen(current));
//   }
//   return current;
// }
//
// int span(char *command,int length_cmd,t_pylst *tokens,char *current)
// {
//   int j;
//   char *to_add;
//
//   j = 1;
//   current = add_token(current,tokens);
//   while (j <= g_grammar->maxlen_leaf_op
//         && j < length_cmd
//         && ops_begin_with((to_add = ft_strndup(command, j)), g_grammar->leaf_op)
//         && !(ft_strdel(&to_add)))
//     j += 1;
//
//
// }
//




void tokenize(char *command, t_pylst *tokens)
{
  int i;
  int length_cmd;
  char *current;

  i = 0;
  length_cmd = ft_strlen(command);
  current = ft_strnew(length_cmd);
  while (i< length_cmd)
  {

    ft_printf("%d\n",ops_begin_with(ft_strndup(command + i, 1), g_grammar->leaf_op));
    // if (ops_begin_with(&command[i], g_grammar->leaf_op))
    // {
    //   // current = add_token(current,tokens);
    //   // i += span(command, i, tokens, current);
    //
    // }

  }
  ft_strdel(&current);

}
