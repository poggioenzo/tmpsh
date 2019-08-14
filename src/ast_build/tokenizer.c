#include <stdio.h>
#include "tmpsh.h"
#include "libft.h"
#include "globals.h"

void print_pylst(t_pylst *pylst)
{
  char  *value;
  t_bool first;

  first = TRUE;
  ft_printf("[");
  while (pylst_iter(pylst,(void **) &value))
  {
    if (!first)
      ft_printf(",", value);
    ft_printf("'%s'", value);
    first = FALSE;
  }
  ft_printf("]\n");
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

static void add_token(char *current, t_pylst *tokens)
{
  if (*current)
  {
    push_pylst(&tokens, current, sizeof(char) * (ft_strlen(current) + 1), _chare);
    ft_bzero(current, ft_strlen(current));
  }
}

static int span(char *command,t_pylst *tokens,char *current)
{
  int length_cmd;
  int j;
  char *to_add;

  j = 1;
  length_cmd = ft_strlen(command);
  add_token(current,tokens);
  while (j <= g_grammar->maxlen_leaf_op
        && j < length_cmd
        && ops_begin_with((to_add = ft_strndup(command, j)),\
                                                          g_grammar->leaf_op)
        && !(ft_strdel(&to_add)))
    j += 1;
  to_add = ft_strndup(command, j);
  if (in_pylst_chare(g_grammar->leaf_op, to_add))
    push_pylst(&tokens, to_add, sizeof(char) * (ft_strlen(to_add) + 1), _chare);
  else
    current[ft_strlen(current)] = *command;
  return (j);
}

static char *escape_token(char *command, t_pylst *tokens, char *current)
{
  add_token(current,tokens);
  command++;
  current[ft_strlen(current)] = g_grammar->escape[0];
  current[ft_strlen(current)] = *command;
  add_token(current, tokens);
  command++;
}

t_bool charinstr(char c, char *str)
{
  while (*str)
  {
    if (c == *str)
      return (TRUE);
    str++;
  }
  return (FALSE);
}

static int span_space(char *command, t_pylst *tokens)
{
  int i;
  char *spaces;

  i = 1;
  while(charinstr(command[i], " \t"))
    i++;
  spaces = ft_strndup(command, i);
  push_pylst(&tokens, spaces, sizeof(char) * (ft_strlen(spaces) + 1), _chare);
  ft_strdel(&spaces);
  return (i);
}


void tokenize(char *command, t_pylst *tokens)
{
  char *current;
  char *tmp;

  push_pylst(&tokens, "", 0 , _chare);
  current = ft_strnew(ft_strlen(command));
  while (*command)
  {
    if (ops_begin_with((tmp = ft_strndup(command, 1)), g_grammar->leaf_op)
        && !ft_strdel(&tmp))
      command += span(command, tokens, current);
    else if (*command == g_grammar->escape[0])
      command = escape_token(command, tokens, current);
    else if (charinstr(*command, " \t"))
      command += span_space(command, tokens);
    else
    {
      current[ft_strlen(current)] = *command;
      command++;
    }
    print_pylst(tokens);
  }
}
