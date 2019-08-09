#!/usr/bin/env python3

import utils.global_var as gv

# TODO: escape $PATH\\


class Heredocs():
    def __init__(self, end_seq_word):
        self.end_seq_word = end_seq_word
        self.closed = False
        self.tokens = []
        self.tags = []

    def init_tags_tokens(self, tags, tokens):
        self.tokens = tokens
        self.tags = tags

    def __str__(self):
        str0 = f'HEREDOC: {self.end_seq_word} | closed: {self.closed}\n'
        str0 += 'DOC:\n{}\n'.format(''.join(self.tokens))
        return str0


class TagsTokensMonitor():
    """docstring for TagsTokensMonitor."""

    def __init__(self, tt):
        self.tt = tt
        self.i = -1
        self.tag = ''
        self.token = ''
        self.begin_cmd = True
        self.heredocs_keys = []
        self.opened = ['']
        self.check()

    def get_tagstokens(self):
        return self.tt

    def reset(self):
        self.begin_cmd = True
        gv.PASSED_ALIAS = []

    def next_tag_token(self):
        self.i += 1
        ret = self.i < self.tt.length
        if ret:
            self.tag = self.tt.tags[self.i]
            self.token = self.tt.tokens[self.i]
        return ret

    def check(self):
        while self.tt.valid and self.next_tag_token():
            self.op_selector()

    def op_selector(self):
        if self.tt.valid:
            if self.tag == 'STMT':
                self.check_aliases()
            elif self.tag == 'BRACEPARAM':
                self.is_braceparam()
            elif self.tag == 'DQUOTES':
                self.is_dquote()
            elif self.tag == 'QUOTE':
                self.is_quote()
            elif self.tag in gv.GRAMMAR.grammar['ABS_TERMINATOR']:
                self.is_abs_terminator()
            elif self.tag in ['CURSH', 'SUBSH']:
                self.in_command_sh()
            elif self.tag in gv.GRAMMAR.opening_tags:
                self.in_sub_process()
            elif self.tag == 'HEREDOC':
                self.is_heredocs()
            elif self.tag in gv.GRAMMAR.grammar['REDIRECTION']:
                self.in_redirection()
            elif self.opened[-1] == self.tag:
                self.opened.pop(-1)

    def check_aliases(self):
        result_alias = ''
        if self.begin_cmd and (self.token in gv.ALIAS and
                               self.token not in gv.PASSED_ALIAS):
            result_alias = gv.ALIAS[self.token]
            self.begin_cmd = result_alias[-1:].isspace()
            gv.PASSED_ALIAS.append(self.token)
            self.tt.replace_alias(result_alias, self.i)
            if self.begin_cmd:
                self.reset()

    def is_braceparam(self):
        not_end = self.next_tag_token()
        stmt_tag = self.tag
        not_end = not_end and self.next_tag_token()
        if stmt_tag != 'STMT' or self.tag != 'END_BRACE':
            if not_end:
                self.tt.valid = False
                self.tt.token_error = 'bad substitution'

    def is_heredocs(self):
        not_end = self.next_tag_token()
        key = ''
        j = 0
        if self.tag == 'SPACES':
            not_end = self.next_tag_token()
        if not_end:
            if self.tag in gv.GRAMMAR.opening_tags:
                j = self.tt.skip_openning_tags(self.i, 'NEW_LINE')
                key = ''.join(self.tt.tokens[self.i:j])
                self.i = j - 1
            else:
                key = self.token
            self.heredocs_keys.append(key)
        else:
            self.tt.valid = False
            self.tt.token_error = self.token
        self.begin_cmd = True

    def is_dquote(self):
        indquote = True
        self.opened.append('DQUOTES')
        while indquote and self.next_tag_token():
            if self.tag == 'DQUOTES' and self.opened[-1] == 'DQUOTES':
                self.opened.pop(-1)
                self.tt.tags[self.i] = 'END_DQUOTES'
                indquote = False
            elif self.tag in gv.GRAMMAR.dquotes_opening_tags:
                self.op_selector()
            else:
                self.tt.tags[self.i] = 'STMT' if self.tt.tags[self.i] != 'VAR' else 'VAR'

    def is_quote(self):
        inquote = True
        while inquote and self.next_tag_token():
            if self.tag == 'QUOTE':
                self.tt.tags[self.i] = 'END_QUOTE'
                inquote = False
                break
            else:
                self.tt.tags[self.i] = 'STMT'

    def is_abs_terminator(self):
        self.reset()

    def in_sub_process(self):
        self.reset()
        in_command = True
        self.opened.append(self.tag)
        exit_tag = gv.GRAMMAR.opening_tags[self.tag]
        while in_command and self.next_tag_token():
            if self.tag == exit_tag:
                self.opened.pop(-1)
                in_command = False
            else:
                self.op_selector()

    def in_command_sh(self):
        end = 0
        ret = 0
        if self.begin_cmd:
            self.in_sub_process()
            ret = self.next_tag_token()
            if self.tag == 'SPACES':
                ret = self.next_tag_token()
            if ret and not (self.tag in gv.GRAMMAR.grammar['ABS_TERMINATOR']
                            or self.tag in gv.GRAMMAR.grammar['REDIRECTION']
                            or self.tag in ['END_BRACE', 'END_BRACKET']):
                self.tt.valid = False
                self.tt.token_error = self.token
        else:
            end = self.tt.skip_openning_tags(self.i) - 1
            self.tt.tags[self.i] = 'STMT'
            if end < self.tt.length:
                self.tt.tags[end] = 'STMT'

    def in_redirection(self):
        not_end = self.next_tag_token()
        if self.tag == 'SPACES':
            not_end = self.next_tag_token()
        if not_end:
            self.op_selector()
            self.begin_cmd = True
        else:
            self.tt.valid = False
            self.tt.token_error = self.token
        self.begin_cmd = True
