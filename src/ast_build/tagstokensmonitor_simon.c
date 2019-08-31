
t_bool		check_aliases(t_tags_tokens_monitor *self)
{
	char	*result_alias;
	t_bool	assignation;

	result_alias = "";
	assignation = self->i + 1 < self->tt->length && \
				  in(find_next_token(self->tt, self->i + 1, false), \
						  "ASSIGNATION_EQUAL", "CONCATENATION", NULL);
	if (!assignation && self->begin_cmd && \
			(search_value(g_alias, self->token) && \
			 !search_value(g_passed_alias, self->token)))
	{
		result_alias = search_value(g_alias, self->token);
		self->begin_cmd = ft_isspace(result_alias[ft_strlen(result_alias) - 1]);
		push_pylst(g_passed_alias, self.token, 0, _ptr); // Check memory.
		replace_alias(self->tt, result_alias, self->i);
		if (self->begin_cmd)
		{
			reset(self); //Check reset name.
			return (true);
		}
	}
	else if (assignation)
	{
		if (!self->begin_cmd)
			update_pylst(self->tt->tags, self->i + 1, "STMT", 0, _ptr);
		else
			return (true);
	}
	return (self->i - 1 > 0 && 
			in(find_prev_token(self->tt, self->i - 1, false), \
				"ASSIGNATION_EQUAL", "CONCATENATION", NULL));
}

void	is_braceparam(t_tags_tokens_monitor *self)
{
	t_bool	not_end;
	char	*stmt_tag;

	not_end = next_ttm(self, false);
	stmt_tag = self->tag;
	not_end = not_end && next_tag_token(self, false);
	if (!ft_strequ(stmt_tag, "STMT") || !ft_strequ(self->tag, "END_BRACE"))
	{
		if (not_end)
		{
			self->tt->valid = false;
			self->tt->token_error = "bad substitution";
		}
	}
}

void	is_dquote(t_tags_tokens_monitor *self)
{
	t_bool	indquote;
	char	*update_str;

	indquote = true;
	push_pylst(self->opened, "DQUOTES", 0, _ptr);
	while (indquote && next_ttm(self, false))
	{
		if (ft_strequ(self->tag, "DQUOTES") && \
				ft_strequ(vindex_pylst(self->opened, -1), "DQUOTES"))
		{
			pop_pylst(self->opened);
			update_pylst(self->tt->tags, self->i, "END_DQUOTES", 0, _ptr);
			indquote = false;
		}
		else if (search_value(g_grammar->dquotes_opening_tags, self->tag))
			op_selector(self);
		else
		{
			if (!ft_strequ(vindex_pylst(self->tt->tags, self->i), "VAR"))
				update_str = "STMT";
			else
				update_str = "VAR";
			update_pylst(self->tt->tags, self->i, update_str, 0, _ptr);
		}
	}
}


void	is_quote(t_tags_tokens_monitor *self)
{
	t_bool		inquote;

	inquote = true;
	while (inquote && next_tag_token(self, false))
	{
		if (ft_strequ(self->tag, "QUOTE"))
		{
			update_pylst(self->tt->tags, self->i, "END_QUOTE", 0, _ptr);
			inquote = false;
		}
		else
			update_pylst(self->tt->tags, self->i, "STMT", 0, _ptr);
	}
}

void	is_abs_terminator(t_tags_tokens_monitor *self)
{
	reset(self);//Function name
}

void	in_sub_process(t_tags_tokens_monitor *self)
{
	t_bool	in_command;
	char	*exit_tag;

	reset(self);//Should be an other function name
	in_command = true;
	push_pylst(&self->opened, self->tag, 0, _ptr); //Check allocation, set _ptr by default.
	exit_tag = search_value(g_grammar->opening_tags, self->tag);
	while (in_command && next_tag_token(self, false))
	{
		if (ft_strequ(self->tag, exit_tag))
		{
			pop_pylst(&self->opened, -1);
			in_command = false;
		}
		else
			op_selector(self);
	}
}

int		search_end(char *tag)
{
	t_pylst		*tmp_operand;

	if (in_grammar(tag, "ABS_TERMINATOR"))
		return (1);
	if (in_grammar(tag, "REDIRECTION"))
		return (1);
	return (in(tag, "END_BRACE", "END_BRACKET", NULL));
}

void	in_command_sh(t_tags_tokens_monitor *self)
{
	int		end;
	int		ret;

	if (self->begin_cmd)
	{
		in_sub_process(self);
		ret = next_ttm(self, false);
		if (ft_strequ(self->tag, "SPACES"))
			ret = next_ttm(self, false);
		end = search_end(self->tag);
		if (ret && !end)
		{
			self->tt->valid = false;
			self->tt->token_error = self->token;
		}
		else if (ret && end)
			reset(self); // SHould be an other function name
	}
	else
	{
		end = skip_openning_tags(self, self->i, NULL) - 1;
		update_pylst(self->tt-tags, self->i, "STMT", 0, _ptr);
		if (end < self->tt->length)
			update_pylst(self->tt->tags, end, "STMT", 0, _ptr);
	}
}

void	in_redirection(t_tags_tokens_monitor *self)
{
	t_bool		not_end;

	not_end = next_ttm(self, false);
	if (ft_strequ(self->tag, "SPACES"))
		not_end = next_ttm(self, false);
	if (not_end)
	{
		op_selector(self);
		self->begin_cmd = true;
	}
	else
	{
		self->tt->valid = false;
		self->tt->token_error = self->token;
	}
	self->begin_cmd = true;
}
