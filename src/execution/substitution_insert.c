#include "libft.h"
#include "tmpsh.h"
#include "tagstokens.h"

/*
** get_final_fields:
**
** Prepare for replace_cmdsubst1 the list of tokens and tags to insert
** inside a tagstokens.
*/

static void	get_final_fields(char *content, t_pylst **final_tokens, \
		t_pylst **statements)
{
	char		**tokens_list;
	int			nbr_tokens;
	int			index;
	char		*token;

	tokens_list = ft_strsplit(content, "\n\t ");
	ft_strdel(&content);
	index = 0;
	nbr_tokens = ft_arraylen(tokens_list);
	while (index < nbr_tokens)
	{
		token = tokens_list[index++];
		push_pylst(final_tokens, token, NO_COPY_BUT_FREE, _chare);
		push_pylst(statements, "STMT", 0, _ptr);
		if (index < nbr_tokens)
		{
			push_pylst(final_tokens, " ", 0, _ptr);
			push_pylst(statements, "SPACES", 0, _ptr);
		}
	}
	ft_memdel((void **)&tokens_list);
}

/*
** prev_is_assignation:
**
** From a given index, check if the previous command tag
** is an ASSIGNATION_EQUAL or a CONCATENATION. Skip
** SPACES token.
*/

static int	prev_is_assignation(t_tagstokens *tagstokens, int index)
{
	char	*prev_tag;

	if (index < 2)
		return (false);
	prev_tag = vindex_pylst(tagstokens->tags, index - 1);
	if (in(prev_tag, "STMT", "SUBAST", NULL))
		return (prev_is_assignation(tagstokens, index - 1));
	if (ft_strequ(prev_tag, "SPACES"))
		prev_tag = vindex_pylst(tagstokens->tags, index - 2);
	return (in(prev_tag, "ASSIGNATION_EQUAL", "CONCATENATION", NULL));
}

/*
** insert_substitution:
**
** Whenever a substitution is performed inside a tagstoken,
** split the token in one or multiple tokens fields.
**
** If the insertion is performed just after an assignation,
** insert only one STMT token.
*/

void		substitution_insert(char *content, t_tagstokens *tagstokens, \
		int index)
{
	t_pylst		*final_tokens;
	t_pylst		*statements;

	final_tokens = NULL;
	statements = NULL;
	if (!prev_is_assignation(tagstokens, index))
		get_final_fields(content, &final_tokens, &statements);
	else
	{
		push_pylst(&final_tokens, content, \
				(sizeof(char) * ft_strlen(content) + 1), _chare);
		push_pylst(&statements, "STMT", 0, _ptr);
	}
	if (final_tokens)
	{
		replace_pylst(&tagstokens->tokens, final_tokens, index, index + 1);
		replace_pylst(&tagstokens->tags, statements, index, index + 1);
	}
	else
	{
		del_portion_pylst(&tagstokens->tokens, index, index + 1);
		del_portion_pylst(&tagstokens->tags, index, index + 1);
	}
	update_length_tagstokens(tagstokens);
}
