#!/usr/bin/env python3

import utils.global_var as gv
import utils.key as k

# import utils.tagstokens as tt
# Should be this next import statement but create circular import error.
# from utils.tagstokens import TagsTokens


def replace_first_tab(tok):
    i = 0
    len_tok = len(tok)
    while i < len_tok and ord(tok[i]) == 9:
        i += 1
    return tok[:i]


class Heredocs():
    def __init__(self, key, len_key, minus):
        import utils.tagstokens as tt
        self.key = key
        self.quoted = k.quoted_gold_key(key)
        self.len_key = len_key
        self.minus = minus
        self.closed = False
        self.tagstokens = tt.TagsTokens()
        self.stack = []
        self.in_cmdsubst = False

    def add_tags_tokens(self, tag, token):
        if self.quoted:
            tag = 'STMT'
        elif not self.in_cmdsubst:
            if tag in gv.GRAMMAR.dquotes_opening_tags:
                self.in_cmdsubst = True
                self.stack.append(gv.GRAMMAR.dquotes_opening_tags[tag])
            else:
                tag = tag if tag in ['VAR', 'STMT',
                                     'SPACES', 'NEW_LINE'] else 'STMT'
        else:
            if tag == self.stack[-1]:
                self.stack.pop(-1)
                if self.stack == []:
                    self.in_cmdsubst = False
            elif tag == 'QUOTE' and self.stack[-1] != 'DQUOTES':
                self.stack.append(tag)
            elif tag == 'DQUOTES' and self.stack[-1] != 'QUOTE':
                self.stack.append(tag)
            elif tag in gv.GRAMMAR.opening_tags and self.stack[-1] != 'QUOTE':
                if self.stack[-1] == 'DQUOTES' and \
                        tag in gv.GRAMMAR.dquotes_opening_tags:
                    self.stack.append(gv.GRAMMAR.dquotes_opening_tags[tag])
                else:
                    self.stack.append(gv.GRAMMAR.opening_tags[tag])
        self.tagstokens.append(tag, token)

    def striplines(self):
        i = 0
        new_line = True
        tag = ''
        tok = ''
        while i < self.tagstokens.length:
            tok, tag = self.tagstokens[i]
            if tag == 'NEW_LINE':
                new_line = True
            elif tag == 'SPACES' and new_line:
                self.tagstokens.tokens[i] = replace_first_tab(tok)
            else:
                new_line = False
            i += 1

    def close(self):
        self.tagstokens = self.tagstokens.copytt(0, -self.len_key)
        if self.minus:
            self.striplines()
        self.tagstokens.check_syntax(True)
        self.closed = True
        # self.tagstokens.incomplete = False

    def __str__(self):
        str0 = '\nHEREDOC: {} | closed: {} | Minus: {}\n'.format(
            self.key, self.closed, self.minus)
        str0 += 'DOC:\n{}\n'.format(str(self.tagstokens))
        return str0
