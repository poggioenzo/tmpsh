#include "tmpsh.h"
#include "libft.h"
#include "environ_utils.h"
#include "local_variables.h"

void	setup_variables_elements(char **environ)
{
	duplicate_environ(environ);
	setup_var_table();
}

void	update_var(char *variable, char *value, char *type, t_bool only_env)
{
	char	*saved_var;
	char	*new_var;

	saved_var = ft_getenv(variable);
	if (saved_var || only_env == true)
	{
		if (!saved_var)
			saved_var = "";
		value = ft_strequ(type, "CONCATENATION") ? \
				ft_strjoin(saved_var, value): ft_strdup(value);
		ft_setenv(variable, value);
		ft_strdel(&value);
	}
	else
	{
		saved_var = ft_getvar(variable);
		if (ft_strequ(type, "CONCATENATION"))
			value = ft_strjoin(saved_var ?: "", value);
		else
			value = ft_strdup(value);
		insert_value(g_variables, variable, value, _ptr);
	}
}

char	*retrieve_variable(char *variable)
{
	char	*variable_str;
	char	*tmp_var;

	variable_str = NULL;
	if (ft_strequ(variable, "?"))
		variable_str = ft_itoa(g_last_status);
	else if (ft_strequ(variable, "$"))
		variable_str = ft_itoa(getpid());
	else
	{
		tmp_var = ft_getenv(variable);
		if (!tmp_var)
			tmp_var = ft_getvar(variable);
		variable_str = ft_strdup(tmp_var?: "");
	}
	return (variable_str);
}

static int		is_stmt(t_tagstokens *tagstok, int index)
{
	char		*tag;

	tag = index_pylst(tagstok->tags, index);
	return (ft_strequ(tag, "STMT"));
}

void	fill_assignation(t_pylst **assignations, char *key, \
		char *method, char *value)
{
	t_pylst		*operation;

	operation = NULL;
	key = ft_strdup(key);
	value = ft_strdup(value);
	push_pylst(&operation, key, NO_COPY_BUT_FREE, _chare);
	push_pylst(&operation, method, 0, _chare);
	push_pylst(&operation, value, NO_COPY_BUT_FREE, _chare);
	push_pylst(assignations, operation, NO_COPY_BUT_FREE, _pylst);
}

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

t_pylst		*retrieve_assignation(t_acb *branch)
{
	t_pylst		*assignation_list;
	char		*last_stmt;
	int			index;
	t_tagstokens	*tagstok;
	char		*tag;

	index = 0;
	assignation_list = NULL;
	tagstok = branch->tagstokens;
	last_stmt = NULL;
	while (index < tagstok->length)
	{
		tag = index_pylst(tagstok->tags, index);
		if (!last_stmt && ft_strequ(tag, "STMT"))
			last_stmt = index_pylst(tagstok->tokens, index);
		else if (ft_strequ(tag, "CONCATENATION") || ft_strequ(tag, "ASSIGNATION_EQUAL"))
		{
			index += 1;
			fill_assignation(&assignation_list, last_stmt, tag,\
					index_pylst(tagstok->tokens, index));
			last_stmt = NULL;
		}
		index++;
	}
	delete_variables(tagstok, assignation_list);
	return (assignation_list);
}

void	variables_config(t_pylst *variables, t_bool only_env)
{
	t_pylst		*operation;
	char		*mode;
	char		*key;
	char		*value;

	operation = NULL;
	while (pylst_iter(variables, &operation))
	{
		key = index_pylst(operation, 0);
		mode = index_pylst(operation, 1);
		value = index_pylst(operation, 2);
		update_var(key, value, mode, only_env);
	}
}


void	tagstoken_variable_swap(t_tagstokens *tagstok, int index)
{
	char	*variable;
	char	*token;
	t_pylst	*tmp_node;

	token = index_pylst(tagstokens->tokens, index);
	variable = retrieve_variable(token + 1);
	pylst_replace(tagstok->tokens, index, variable, NO_COPY_BUT_FREE, _chare);
	pylst_replace(tagstok->tags, index, tag, 0, _ptr);

}


void	replace_variable(t_acb *branch)
{
	int		index;
	int		index_subast;
	char	*tag;
	t_ast	*subast;

	index = 0;
	index_subast = 0;
	while (index < branch->tagstokens->length)
	{
		tag = index_pylst(branch->tagstokens->tags, index);
		if (ft_strequ(tag, "VAR"))
			tagstoken_variable_swap(branch->tagstokens, index);
		else if (ft_strequ(tag, "SUBAST"))
		{
			subast = index_pylst(branch->subast);
			if (ft_strequ(subast->type, "DQUOTES"))
				replace_variable(subast->list_branch);
			index_subast++;
		}
		index++;
	}
}





