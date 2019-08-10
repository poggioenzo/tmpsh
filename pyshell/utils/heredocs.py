#!/usr/bin/env python3

# import utils.global_var as gv

import utils.tagstokens as tt
import utils.tagstokensmonitor as ttm
# Should be this next import statement but create circular import error.
# from utils.tagstokens import TagsTokens


class Heredocs():
    def __init__(self, key, len_key):
        self.key = key
        self.len_key = len_key
        self.closed = False
        self.tagstokens = tt.TagsTokens()

    def add_tags_tokens(self, tag, token):
        self.tagstokens.append(tag, token)

    # def retags(self):
    #     i = 0
    #     stack = ['']
    #     tok = ''
    #     tag = ''
    #     in_cmdsubt = False
    #     while i < self.tagstokens.length:
    #         tok = self.tagstokens.tokens[i]
    #         tag = self.tagstokens.tags[i]
    #         if in_cmdsubt:
    #             if
    #             pass
    #             if stack == ['']:
    #                 in_cmdsubt = False
    #         elif tag == 'CMDSUBST1':
    #             in_cmdsubt = True
    #         else:
    #             pass

    def close(self):
        self.tagstokens = self.tagstokens.copytt(0, -self.len_key)

        ttm.TagsTokensMonitor(self.tagstokens)
        self.closed = True

    def __str__(self):
        str0 = f'HEREDOC: {self.key} | closed: {self.closed}\n'
        str0 += 'DOC:\n{}\n'.format(str(self.tagstokens))
        return str0
