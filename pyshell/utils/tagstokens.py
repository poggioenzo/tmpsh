#! /usr/bin/env python3

import pandas as pd
import utils.global_var as gv
import utils.tokenizer as tk
import utils.strcontain as sc
import utils.shift_reduce as sr


class TagsTokens():
    def __init__(self, tokens=None, tags=None):
        self.tokens = tokens if tokens else []
        self.tags = tags if tags else []
        self.stack = []
        self.token_error = ''
        self.valid = True
        self.incomplete = False

    def init_with_input(self, term_inputs):
        tk.tokenize(term_inputs, self.tokens)
        return self.get_tags()

    def get_tags(self):
        for tok in self.tokens:
            if tok in gv.GRAMMAR.leaf_op:
                self.tags.append(gv.GRAMMAR.reverse[tok])
            elif sc.containspaces(tok):
                self.tags.append('SPACES')
            else:
                self.tags.append('STMT')
        self.double_quote_gseture()
        self.quote_gseture()
        return self

    def double_quote_gseture(self):
        len_tags = len(self.tags)
        i = 0
        stk = ['']  # stk for stack
        exit_tag = ''
        while i < len_tags:
            tag = self.tags[i]
            if exit_tag == tag:
                if stk[-1:][0] == 'DQUOTES':
                    self.tags[i] = 'STMT'
                else:
                    exit_tag = ''
                    stk.pop(-1)
            elif tag == 'DQUOTES':
                _ = stk.append(tag) if stk[-1:][0] != tag else stk.pop(-1)
                # Ouais on peut clairement developper cette ternaire mais c'est
                # un kiffe de faire un switch sur une ligne
            elif tag not in ['STMT', 'SPACES'] and stk[-1:][0] == 'DQUOTES':
                if tag in gv.GRAMMAR.dquotes_opening_tags:
                    stk.append(tag)
                    exit_tag = gv.GRAMMAR.dquotes_opening_tags[tag]
                else:
                    self.tags[i] = 'STMT'
            i += 1

    def quote_gseture(self):
        len_tags = len(self.tags)
        i = 0
        inquote = False
        while i < len_tags:
            if self.tags[i] == 'QUOTE':
                inquote = not inquote
            elif self.tags[i] not in ['STMT', 'SPACES'] and inquote:
                self.tags[i] = 'STMT'
            i += 1

    def check_syntax(self):
        def end_escape(last_tokens):
            return gv.GRAMMAR.escape == last_tokens[-1]
        self.stack = sr.tagstokens_shift_reduce(self, gv.GRAMMAR)
        if end_escape(self.tokens[-1]):
            self.incomplete = True
        return self

    def __str__(self):
        str0 = '\n'.join(
            str(pd.DataFrame([self.tags, self.tokens])).split('\n')[1:3])
        str0 += '\nStack: {}'.format(self.stack)
        str0 += '\nValid: {} | Incomplete: {} | Token_error: "{}"'.format(
            self.valid, self.incomplete, self.token_error)
        return str0
