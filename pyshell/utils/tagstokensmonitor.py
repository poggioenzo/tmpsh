#!/usr/bin/env python3

import utils.global_var as gv

# TODO: alias gesture
# TODO: escape $PATH\\


class TagsTokensMonitor():
    """docstring for TagsTokensMonitor."""

    def __init__(self, tt):
        self.tt = tt
        self.i = -1
        self.tag = ''
        self.token = ''
        self.begin_cmd = True
        self.after_red = False
        self.opened = ['']
        self.passed_alias = []
        self.check()

    def get_tagstokens(self):
        return self.tt

    def reset(self):
        self.begin_cmd = True
        self.passed_alias = []

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
        # print(self.tag, self.begin_cmd)
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
            elif self.tag in gv.GRAMMAR.grammar['REDIRECTION']:
                self.in_redirection()
            elif self.opened[-1] == self.tag:
                self.opened.pop(-1)

    def check_aliases(self):
        print(self.begin_cmd, self.token)
        alias = ''

        if self.begin_cmd and self.token in gv.ALIAS:
            alias = gv.ALIAS[self.token]

        self.begin_cmd = False

    def is_braceparam(self):
        not_end = self.next_tag_token()
        stmt_tag = self.tag
        not_end = not_end and self.next_tag_token()
        if stmt_tag != 'STMT' or self.tag != 'END_BRACE':
            if not_end:
                self.tt.valid = False
                self.tt.token_error = 'bad substitution'

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
                self.tt.tags[self.i] = 'STMT'

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
                            or self.tag in gv.GRAMMAR.grammar['REDIRECTION']):
                self.tt.valid = False
                self.tt.token_error = self.token
            else:
                self.op_selector()
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
