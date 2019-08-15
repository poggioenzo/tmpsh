#include <stdio.h>
#include "tmpsh.h"
#include "libft.h"
#include "globals.h"
#include "tokenizer_utils.h"

static void add_token(char *current, t_pylst **tokens)
{
  if (*current)
  {
    push_pylst(tokens, current, sizeof(char) * (ft_strlen(current) + 1), _chare);
    ft_bzero(current, ft_strlen(current));
  }
}

static int span(char *command,t_pylst **tokens,char *current)
{
  int length_cmd;
  int j;
  int i;
  char *to_add;

  j = 1;
  i = 1;
  length_cmd = ft_strlen(command);
  add_token(current,tokens);
  while (j <= g_grammar->maxlen_leaf_op
        && j < length_cmd
        && ops_begin_with((to_add = ft_strndup(command, j)),\
                                                          g_grammar->leaf_op)
        && !(ft_strdel(&to_add)))
    j += 1;
  to_add = ft_strndup(command, --j);
  if (in_pylst_chare(to_add, g_grammar->leaf_op))
  {
    push_pylst(tokens, to_add, sizeof(char) * (ft_strlen(to_add) + 1), _chare);
    i = j;
  }
  else
    current[ft_strlen(current)] = *command;
  ft_strdel(&to_add);
  return (i);
}

static char *escape_token(char *command, t_pylst **tokens, char *current)
{
  add_token(current,tokens);
  command++;
  current[ft_strlen(current)] = g_grammar->escape[0];
  current[ft_strlen(current)] = *command;
  add_token(current, tokens);
  command++;
  return (command);
}

static int span_space(char *command, t_pylst **tokens, char *current)
{
  int i;
  char *spaces;

  i = 1;
  add_token(current, tokens);
  while(ft_incharset(command[i], " \t"))
    i++;
  spaces = ft_strndup(command, i);
  push_pylst(tokens, spaces, sizeof(char) * (ft_strlen(spaces) + 1), _chare);
  ft_strdel(&spaces);
  return (i);
}


void tokenize(char *command, t_pylst **tokens)
{
  char *current;
  char *tmp;

  current = ft_strnew(ft_strlen(command));
  while (*command)
  {
    if (ops_begin_with((tmp = ft_strndup(command, 1)), g_grammar->leaf_op)
        && !ft_strdel(&tmp))
      command += span(command, tokens, current);
    else if (*command == g_grammar->escape[0])
      command = escape_token(command, tokens, current);
    else if (ft_incharset(*command, " \t"))
      command += span_space(command, tokens, current);
    else
    {
      current[ft_strlen(current)] = *command;
      command++;
    }
  }
  print_pylst_chare(*tokens);
}
