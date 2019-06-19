#! /usr/bin/env python3

import pandas as pd
import utils.global_var as gv
import utils.tokenizer as tk
import utils.strcontain as sc
import utils.shiftreduce as sr


def test(func):
    def wrapper(self, i):
        if self.tags[i] not in gv.GRAMMAR.opening_tags:
            raise Exception("No {} in opening_tags.".format(self.tags[i]))
        return func(self, i)
    return wrapper


class TagsTokens():
    def __init__(self, tokens=None, tags=None):
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
        self.update_length()

    def update_length(self):
        self.length = len(self.tokens)

    def init_with_input(self, term_inputs):
        tk.tokenize(term_inputs, self.tokens)
        # self.alias_replacement()
        self.update_length()
        return self.get_tags()

    def find_prev_token(self, i, get_token=True):
        if self.tags[i] == 'SPACES':
            i -= 1
        return self.tokens[i] if get_token else self.tags[i]

    # def prev_tokens_ok(self, i):
    #     if i == 0:
    #         return True
    #     ret = self.tokens[i - 1] in gv.GRAMMAR.grammar['ABS_TERMINATOR']
    #     ret |= self.tokens[i - 1] in gv.GRAMMAR.opening_tags
    #     return ret

    # def alias_replacement(self):
    #     i = 0
    #     len_tok = len(self.tokens)
    #     tok = ''
    #     while i < len_tok:
    #         tok = self.tokens[i]
    #         if self.prev_tokens_ok(i) and tok in gv.ALIAS:
    #             pass
    #         i += 1

    def get_tags(self):
        for tok in self.tokens:
            if tok in gv.GRAMMAR.leaf_op:
                self.tags.append(gv.GRAMMAR.reverse[tok])
            elif sc.containonlyspaces(tok):
                self.tags.append('SPACES')
            else:
                self.tags.append('STMT')
        self.double_quote_gesture()
        self.quote_gesture()
        return self

    def double_quote_gesture(self):
        # TODO: inspire of split_branch(self, tt) to improve code quality
        i = 0
        stk = ['']  # stk for stack
        exit_tag = ['']
        while i < self.length:
            tag = self.tags[i]
            if exit_tag[-1] == tag:
                if stk[-1:][0] == 'DQUOTES':
                    self.tags[i] = 'STMT'
                else:
                    exit_tag.pop(-1)
                    stk.pop(-1)
            elif tag == 'DQUOTES':
                if stk[-1:][0] != 'DQUOTES':
                    stk.append(tag)
                else:
                    stk.pop(-1)
                    self.tags[i] = 'END_DQUOTES'
            elif tag not in ['STMT', 'SPACES'] and stk[-1:][0] == 'DQUOTES':
                if tag in gv.GRAMMAR.dquotes_opening_tags:
                    stk.append(tag)
                    exit_tag.append(gv.GRAMMAR.dquotes_opening_tags[tag])
                else:
                    self.tags[i] = 'STMT'
            i += 1

    def quote_gesture(self):
        i = 0
        inquote = False
        while i < self.length:
            if self.tags[i] == 'QUOTE':
                if inquote:
                    self.tags[i] = 'END_QUOTE'
                inquote = not inquote
            elif self.tags[i] not in ['STMT', 'SPACES'] and inquote:
                self.tags[i] = 'STMT'
            i += 1

    def check_syntax(self):
        def end_escape(lt):
            return len(lt) > 0 and gv.GRAMMAR.escape == lt[-1]

        self.stack = sr.tagstokens_shift_reduce(self, gv.GRAMMAR)
        if end_escape(self.tokens[-1]):
            self.incomplete = True
        if self.stack != [] and self.stack[-1] == 'REDIRECTION':
            self.valid = False
            self.incomplete = False
            self.token_error = self.find_prev_token(len(self.tokens) - 1)
        self.clear_stack()
        return self

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

    def clear_stack(self):
        self.stack = [elt for elt in self.stack if elt != 'CMD']

    def __str__(self):
        str0 = '\n'.join(
            str(pd.DataFrame([self.tags, self.tokens])).split('\n')[1:3])
        str0 += '\nStack: {}'.format(self.stack)
        str0 += '\nValid: {} | Incomplete: {} | Token_error: "{}"'.format(
            self.valid, self.incomplete, self.token_error)
        return str0

    def __getitem__(self, index):
        return TagsTokens(self.tokens[index], self.tags[index])

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
