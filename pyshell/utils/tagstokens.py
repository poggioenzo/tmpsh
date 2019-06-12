#! /usr/bin/env python3

import pandas as pd
import utils.global_var as gv
import utils.tokenizer as tk
import utils.strcontain as sc
import utils.shiftreduce as sr


class TagsTokens():
    def __init__(self, tokens=None, tags=None):
        self.tokens = tokens if tokens else []
        self.tags = tags if tags else []
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
        self.update_length()
        return self.get_tags()

    def get_tags(self):
        for tok in self.tokens:
            if tok in gv.GRAMMAR.leaf_op:
                self.tags.append(gv.GRAMMAR.reverse[tok])
            elif sc.containspaces(tok):
                self.tags.append('SPACES')
            else:
                self.tags.append('STMT')
        self.double_quote_gesture()
        self.quote_gesture()
        return self

    def double_quote_gesture(self):
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
            print(tag)

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
        if self.stack[-1] == 'REDIRECTION':
            self.valid = False
            self.incomplete = False
            self.token_error = self.find_prev_token(len(self.tokens) - 1)
        self.clear_stack()
        return self

    def find_prev_token(self, i):
        if self.tags[i] == 'SPACES':
            i -= 1
        return self.tokens[i]

    def clear_stack(self):
        self.stack = [elt for elt in self.stack if elt != 'CMD']

    def __str__(self):
        str0 = '\n'.join(
            str(pd.DataFrame([self.tags, self.tokens])).split('\n')[1:3])
        str0 += '\nStack: {}'.format(self.stack)
        str0 += '\nValid: {} | Incomplete: {} | Token_error: "{}"'.format(
            self.valid, self.incomplete, self.token_error)
        return str0
