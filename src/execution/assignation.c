#include "libft.h"
#include "tmpsh.h"
#include "variables.h"

/*
** fill_assignation:
**
** @assignations: Current list of assignation set.
** @key: new variable name
** @method: assignation methon, if it's a CONCATENATION or ASSIGNATION_EQUAL
** @value: Value of the new variable.
**
** Whenever a new assignation is found, group the key/methon/value in a pylst,
** and add it to the current list of assignation.
** Like creating a tuple for a single assignation, like (key, method, value)
*/

static void		fill_assignation(t_pylst **assignations, char *key, \
		char *method, char *value)
{
	t_pylst		*operation;

	operation = NULL;
	push_pylst(&operation, key, 0, _chare);
	push_pylst(&operation, method, 0, _chare);
	push_pylst(&operation, value, 0, _chare);
	push_pylst(assignations, operation, NO_COPY_BUT_FREE, _pylst);
}

/*
** delete_variables:
**
** @tagstok: tagstokens where the assignation tag/tokens have to be removed.
** @assignations: List of all branch assignations.
**
** Remove in the tags and tokens list of the given tagstokens each element
** related to the assignation.
** Assuming that all assignation are at the begining of the branch.
*/

static void		delete_variables(t_tagstokens *tagstok, t_pylst *assignations)
{
	int		nbr_assignations;

	nbr_assignations = len_pylst(assignations);
	if (nbr_assignations > 0)
	{
		del_portion_pylst(&tagstok->tags, 0, nbr_assignations * 3);
		del_portion_pylst(&tagstok->tokens, 0, nbr_assignations * 3);
		//update_length(tagstok);
	}
}

/*
** retrieve_assignation:
**
** @branch: branch where the assignation have to be parsed.
**
** Inside a branch, retrieve each token which are related to variables
** assignation, finding for each operation a key, a method and a value.
** Store each of this assignation inside a list.
**
** return : - pylst of tuple (aka pylst) containing each existing assignations
**			- NULL if no assignation where found.
*/

t_pylst			*retrieve_assignation(t_acb *branch)
{
	t_pylst			*assignation_list;
	char			*last_stmt;
	int				index;
	char			*tag;

	index = 0;
	assignation_list = NULL;
	last_stmt = NULL;
	while (index < branch->tagstokens->length)
	{
		tag = vindex_pylst(branch->tagstokens->tags, index);
		if (!last_stmt && ft_strequ(tag, "STMT"))
			last_stmt = vindex_pylst(branch->tagstokens->tokens, index);
		else if (ft_strequ(tag, "CONCATENATION") || \
				ft_strequ(tag, "ASSIGNATION_EQUAL"))
		{
			index += 1;
			fill_assignation(&assignation_list, last_stmt, tag,\
				vindex_pylst(branch->tagstokens->tokens, index));
			last_stmt = NULL;
		}
		index++;
	}
	delete_variables(branch->tagstokens, assignation_list);
	return (assignation_list);
}

/*
** variables_config:
**
** @assignations: List tuple who contain all assignations
** @only_env: Specify if variable are only set to the environnement.
**
** Facility to set up a list of assignations, storing each given value.
*/

void			variables_config(t_pylst *assignations, t_bool only_env)
{
	t_pylst		*operation;
	char		*mode;
	char		*key;
	char		*value;

	operation = NULL;
	while (iter_pylst(assignations, (void **)&operation))
	{
		key = vindex_pylst(operation, 0);
		mode = vindex_pylst(operation, 1);
		value = vindex_pylst(operation, 2);
		update_var(key, value, mode, only_env);
	}
	free_pylst(&assignations, 0);
}
