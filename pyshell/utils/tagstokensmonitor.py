#!/usr/bin/env python3

import utils.global_var as gv


# def update_i(func):
#     def method(self):
#


class TagsTokensMonitor():
    """docstring for TagsTokensMonitor."""

    def __init__(self, tt):
        self.tt = tt
        self.i = -1
        self.tag = ''
        self.token = ''
        self.begin_cmd = True
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
        if self.i < self.tt.length:
            self.tag = self.tt.tags[self.i]
            self.token = self.tt.tokens[self.i]

    def check(self):
        while self.i < self.tt.length and self.tt.valid:
            self.next_tag_token()
            self.op_selector()

    def op_selector(self):
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
        else:
            self.i += 1
        self.begin_cmd = False

    def check_aliases(self):
        self.i += 1

    def is_braceparam(self):
        self.next_tag_token()
        stmt_tag = self.tag
        self.next_tag_token()
        if stmt_tag != 'STMT' or self.tag != 'END_BRACE':
            self.tt.valid = False
            self.tt.token_error = 'bad substitution'

    def is_dquote(self):
        end = self.tt.skip_openning_tags(self.i) + 1
        self.i += 1
        while self.i < end:
            self.next_tag_token()
            self.i += 1

    def is_quote(self):
        i = self.i
        inquote = False
        while i < self.tt.length:
            if self.tt.tags[i] == 'QUOTE':
                if inquote:
                    self.tt.tags[i] = 'END_QUOTE'
                inquote = not inquote
            elif self.tt.tags[i] != 'STMT' and inquote:
                self.tt.tags[i] = 'STMT'
            i += 1
        self.i = i

    def is_abs_terminator(self):
        self.reset()
        self.i += 1

    def in_sub_process(self):
        self.reset()
        self.i += 1

    def in_command_sh(self):
        self.i += 1

    def in_redirection(self):
        self.i += 1

    # def prev_tokens_ok(self, i):
    #     if i == -1 or (i == 0 and self.tags[0] == 'SPACES'):
    #         return True
    #     ret = self.find_prev_token(i, False)\
    #         in gv.GRAMMAR.grammar['ABS_TERMINATOR']
    #     ret |= self.find_prev_token(i, False)\
    #         in gv.GRAMMAR.opening_tags
    #     return ret

    # def alias_gesture(self):
    #     i = 0
    #     tok = ''
    #     local = []
    #     passed_alias = []
    #
    #     while i < self.length:
    #         tok = self.tokens[i]
    #         print(passed_alias)
    #         if self.tags[i] in gv.GRAMMAR.grammar['ABS_TERMINATOR']\
    #                 or self.tags[i] in gv.GRAMMAR.opening_tags:
    #             passed_alias = []
    #         elif self.prev_tokens_ok(i - 1) and tok in gv.ALIAS and\
    #                 tok not in passed_alias:
    #             passed_alias.append(tok)
    #             tk.tokenize(gv.ALIAS[tok], local)
    #             self.tokens[i:i + 1] = local
    #             self.get_tags()
    #             local = []
    #             i -= 1
    #         i += 1
