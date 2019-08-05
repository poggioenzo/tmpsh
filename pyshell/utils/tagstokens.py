#! /usr/bin/env python3

import pandas as pd
import utils.global_var as gv
import utils.tokenizer as tk
import utils.strcontain as sc
import utils.shiftreduce as sr
from utils.tagstokensmonitor import TagsTokensMonitor as TTM

# TODO: HEREDOC gesture post NEW_LINE


def test(func):
    def wrapper(self, i):
        if self.tags[i] not in gv.GRAMMAR.opening_tags:
            raise Exception("No {} in opening_tags.".format(self.tags[i]))
        return func(self, i)
    return wrapper


def end_escape(lt):
    return len(lt) > 0 and gv.GRAMMAR.escape == lt[-1]


class Heredocs():
    def __init__(self, end_seq_word):
        self.end_seq_word = end_seq_word
        self.closed = False


class TagsTokens():
    def __init__(self, tokens=None, tags=None):
        self.heredocs = []  # list of Heredocs
        self.tokens = tokens if tokens else []
        self.tags = tags if tags else []
        if isinstance(self.tokens, str):
            self.tokens = [self.tokens]
        if isinstance(self.tags, str):
            self.tags = [self.tags]
        self.stack = []
        self.token_error = ''
        self.valid = True
        self.incomplete = False
        self.length = 0
        self.strip()
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

    def get_tags(self, i=0):
        self.tags = self.tags[:i]
        tok = ''
        while i < self.length:
            tok = self.tokens[i]
            if tok in gv.GRAMMAR.leaf_op:
                self.tags.append(gv.GRAMMAR.reverse[tok])
            elif sc.containonlyspaces(tok):
                self.tags.append('SPACES')
            else:
                self.tags.append('STMT')
            i += 1
        self.strip()  # to remove and change test
        self.update_length()
        return self

    def check_syntax(self):
        TTM(self)
        if self.valid:
            self.stack = sr.tagstokens_shift_reduce(self, gv.GRAMMAR)
            if self.length > 0 and end_escape(self.tokens[-1]):
                self.incomplete = True
        self.clear_stack()
        return self

    def clear_stack(self):
        self.stack = [elt for elt in self.stack if elt != 'CMD']

    @test
    def skip_openning_tags(self, i):
        stack = [gv.GRAMMAR.opening_tags[self.tags[i]]]
        i += 1
        while i < self.length:
            tag = self.tags[i]
            if stack == []:
                break
            elif tag in gv.GRAMMAR.opening_tags:
                stack.append(gv.GRAMMAR.opening_tags[tag])
            elif tag == stack[-1]:
                stack.pop(-1)
            i += 1
        return i

    def find_prev_ind_token(self, i):
        if self.tags[i] == 'SPACES' and i - 1 >= 0:
            i -= 1
        return i

    def find_prev_token(self, i, get_token=True):
        if self.tags[i] == 'SPACES' and i - 1 >= 0:
            i -= 1
        return self.tokens[i] if get_token else self.tags[i]

    def find_next_token(self, i, get_token=True):
        if self.tags[i] == 'SPACES' and i + 1 < self.length:
            i += 1
        return self.tokens[i] if get_token else self.tags[i]

    def replace_alias(self, alias_inputs, i):
        tt_alias = TagsTokens().init_with_input(alias_inputs).check_syntax()
        self.tokens = self.tokens[:i] + tt_alias.tokens + self.tokens[i + 1:]
        self.tags = self.tags[:i] + tt_alias.tags + self.tags[i + 1:]
        self.valid = tt_alias.valid
        self.update_length()

    def __str__(self):
        str0 = '\n'.join(
            str(pd.DataFrame([self.tags, self.tokens])).split('\n')[1:3])
        str0 += '\nStack: {}'.format(self.stack)
        str0 += '\nValid: {} | Incomplete: {} | Token_error: "{}"'.format(
            self.valid, self.incomplete, self.token_error)
        return str0

    def copytt(self, begin, end=None):
        if end is None:
            end = begin + 1
        tokens, tags = self[begin:end]
        return TagsTokens(tokens, tags)

    def __getitem__(self, index):
        return (self.tokens[index], self.tags[index])

    def __setitem__(self, index, value):
        if not (type(value) == tuple or type(value) == list):
            raise Exception("Setitem value should be a tuple or list."
                            "\n(tag, token) or [[tags],[tokens]]")
        self.tags[index], self.tokens[index] = value
        self.update_length()

    def __delitem__(self, key):
        if not (0 <= key < self.length):
            raise Exception("IndexError: list index out of range")
        del self.tags[key]
        del self.tokens[key]
        self.update_length()

    def __add__(self, other):
        return TagsTokens(self.tokens + other.tokens,
                          self.tags + other.tags).check_syntax()
