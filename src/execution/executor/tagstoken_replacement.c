#include "tmpsh.h"
#include "libft.h"

/*
** replace_redirection:
**
** If the replacement is not done in the branch tagstokens,
** search if the replacement can be done inside a redirection element.
*/

static void		replace_redirection(t_acb *branch, int change_index, char *content)
{
	char				*tag;
	char				*token;
	t_redirection_fd	*redirection;

	while (iter_pylst(branch->redirectionfd, (void **)&redirection))
	{
		tag = redirection->tagstokens->tags->value;
		token = redirection->tagstokens->tokens->value;
		if (ft_strequ(tag, "SUBAST") && ft_atoi(token) == change_index)
		{
			ft_memdel(&redirection->dest);
			redirection->dest = content;
		}
	}
}

/*
** get_final_fields:
**
** Prepare for replace_cmdsubst1 the list of tokens and tags to insert
** inside a tagstokens.
*/

static void		get_final_fields(char *content, t_pylst **final_tokens, \
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
** replace_cmdsubst1:
**
** Insert CMDSUBST1 elements inside a tagstokens.
** Split element by IFS caracters.
** Replace each IFS caracters by one of them, and split all.
** Insert tokens list to be mutliple STMT separated by
** spaces.
*/

void	replace_cmdsubst1(char *content, t_tagstokens *tagstokens, int index)
{
	t_pylst		*final_tokens;
	t_pylst		*statements;

	final_tokens = NULL;
	statements = NULL;
	get_final_fields(content, &final_tokens, &statements);
	replace_pylst(&tagstokens->tokens, final_tokens, index, index + 1);
	replace_pylst(&tagstokens->tags, statements, index, index + 1);
	//update_length(tagstokens);
}

/*
** replace_subast:
**
** Replace in a branch the content given by a subast with
** a CMDSUBT[123], QUOTE or DQUOTES.
** Try to replace this content in the tagstokens list of the branch,
** or replace in the filedescriptor list if it's not found.
*/

void			replace_subast(t_acb *branch, int change_index, char *content, \
		char *type_ast)
{
	int		index;
	char	*tag;
	char	*token;
	t_tagstokens	*tagstok;

	index = 0;
	tagstok = branch->tagstokens;
	while (index < tagstok->length)
	{
		tag = vindex_pylst(tagstok->tags, index);
		token = vindex_pylst(tagstok->tokens, index);
		if (ft_strequ(tag, "SUBAST") && ft_atoi(token) == change_index)
		{
			if (ft_strequ("CMDSUBST1", type_ast))
				replace_cmdsubst1(content, branch->tagstokens, index);
			else
			{
				update_pylst(tagstok->tokens, index, content, \
						NO_COPY_BUT_FREE, _chare);
				update_pylst(tagstok->tags, index, "STMT", 0, _chare);
			}
			return ;
		}
		index++;
	}
	replace_redirection(branch, change_index, content);
}
