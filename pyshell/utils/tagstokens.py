#! /usr/bin/env python3

import pandas as pd
import utils.global_var as gv
import utils.tokenizer as tk
import utils.strcontain as sc
import utils.shiftreduce as sr


def end_escape(lt):
    return len(lt) > 0 and gv.GRAMMAR.escape == lt[-1]


class TagsTokens():
    def __init__(self, tokens=None, tags=None):
        self.tokens = tokens if tokens else []
        self.tags = tags if tags else []
        if isinstance(self.tokens, str):
            self.tokens = [self.tokens]
        if isinstance(self.tags, str):
            self.tags = [self.tags]
        self.stack = []
        self.not_heredoc = True
        self.token_error = ''
        self.valid = True
        self.incomplete = False
        self.length = 0
        self.update_length()

    def strip(self):
        if len(self.tags) > 0 and self.tags[0] == 'SPACES':
            self.tokens, self.tags = self[1:]
        if len(self.tags) > 0 and self.tags[-1] == 'SPACES':
            self.tokens, self.tags = self[:-1]
        if len(self.tags) == 1 and self.tags[0] == 'SPACES':
            self.tokens, self.tags = [], []

    def update_length(self):
        self.length = len(self.tokens)

    def init_with_input(self, term_inputs):
        tk.tokenize(term_inputs, self.tokens)
        self.update_length()
        self.get_tags()
        return self

    def get_tags(self):
        i = 0
        tok = ''
        while i < self.length:
            tok = self.tokens[i]
            if tok in gv.GRAMMAR.leaf_op:
                self.tags.append(gv.GRAMMAR.reverse[tok])
            elif sc.containonlyspaces(tok):
                self.tags.append('SPACES')
            elif tok[0] == '$' and len(tok) > 1:
                self.tags.append('VAR')
            else:
                self.tags.append('STMT')
            i += 1
        self.strip()  # to remove and change test
        self.update_length()
        return self

    def check_syntax(self):
        import utils.tagstokensmonitor as ttm
        ttm.TagsTokensMonitor(self)
        if self.valid:
            self.stack = sr.tagstokens_shift_reduce(self, gv.GRAMMAR)
            if self.length > 0 and end_escape(self.tokens[-1]):
                self.incomplete = True
        if gv.HEREDOCS != [] and self.not_heredoc:
            self.incomplete |= not all([elt.closed and
                                        not elt.tagstokens.incomplete
                                        for elt in gv.HEREDOCS])
            self.valid &= all([elt.tagstokens.valid for elt in gv.HEREDOCS])
        self.clear_stack()
        return self

    def clear_stack(self):
        self.stack = [elt for elt in self.stack if elt != 'CMD']

    def skip_openning_tags(self, i, until=''):
        stack = [gv.GRAMMAR.opening_tags[self.tags[i]]]
        i += 1
        while i < self.length:
            tag = self.tags[i]
            if stack == [] or tag == until:
                break
            elif tag in gv.GRAMMAR.opening_tags:
                stack.append(gv.GRAMMAR.opening_tags[tag])
            elif tag == stack[-1]:
                stack.pop(-1)
            i += 1
        return i

    def replace_alias(self, alias_key, i):
        alias_result = gv.ALIAS[alias_key]
        ret = alias_result[-1:].isspace()
        if alias_key in gv.ACTUAL_ALIAS:
            ret = False
            alias_result = alias_key
        gv.ACTUAL_ALIAS.append(alias_key)
        tt_alias = TagsTokens().init_with_input(alias_result).check_syntax()
        gv.ALIASINDEPTH = tt_alias.length + i + 1
        self.tokens = self.tokens[:i] + tt_alias.tokens + self.tokens[i + 1:]
        self.tags = self.tags[:i] + tt_alias.tags + self.tags[i + 1:]
        self.valid = tt_alias.valid
        self.update_length()
        return ret

    def find_prev_ind_token(self, i):
        if self.tags[i] == 'SPACES' and i - 1 >= 0:
            i -= 1
        return i

    def find_prev_token(self, i, get_token=True):
        if self.tags[i] == 'SPACES' and i - 1 >= 0:
            i -= 1
        return self.tokens[i] if get_token else self.tags[i]

    def find_next_ind_token(self, i):
        if i + 1 < self.length and self.tags[i] == 'SPACES':
            i += 1
        return i

    def find_next_token(self, i, get_token=True):
        if i + 1 < self.length and self.tags[i] == 'SPACES':
            i += 1
        return self.tokens[i] if get_token else self.tags[i]

    def append(self, tag, token):
        self.tags.append(tag)
        self.tokens.append(token)
        self.update_length()

    def copytt(self, begin, end=None):
        if end is None:
            end = begin + 1
        tokens, tags = self[begin:end]
        return TagsTokens(tokens, tags)

    def __str__(self):
        str0 = '\n'.join(
            str(pd.DataFrame([self.tags, self.tokens])).split('\n')[1:3])
        str0 += '\nStack: {}'.format(self.stack)
        str0 += '\nValid: {} | Incomplete: {} | Token_error: "{}" | Length: {}'.format(
            self.valid, self.incomplete, self.token_error, self.length)
        if gv.HEREDOCS != [] and gv.DONTPRINT:
            gv.DONTPRINT = False
            str0 += '\n' + '\n'.join([str(elt) for elt in gv.HEREDOCS])
        return str0

    def __getitem__(self, index):
        return (self.tokens[index], self.tags[index])

    def __setitem__(self, index, value):
        if not (type(value) == tuple or type(value) == list):
            raise Exception("Setitem value should be a tuple or list."
                            "\n(tag, token) or [[tags],[tokens]]")
        self.tags[index], self.tokens[index] = value
        self.update_length()

    def __delitem__(self, key):
        if key is int:
            if not (0 <= key < self.length):
                raise Exception("IndexError: list index out of range")
        if key is slice:
            if not (0 <= key.start and key.stop < self.length):
                raise Exception("SliceError: slice out of range")
        del self.tags[key]
        del self.tokens[key]
        self.update_length()

    # def __add__(self, other):
    #     return TagsTokens(self.tokens + other.tokens,
    #                       self.tags + other.tags).check_syntax()
