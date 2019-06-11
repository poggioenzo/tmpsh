#!/usr/bin/env python3

import utils.global_var as gv
from utils.tagstokens import TagsTokens as TT


def split_shift(tabit):
    return ''.join(['\t{}'.format(x) for x in tabit])[: -1]


def wait(waiting):
    return len(waiting) > 0 and waiting[-1] == ''


class AST():  # AbstractSyntaxTree
    """docstring for AbstractSyntaxTree."""

    def __init__(self, tagstokens):
        self.list_branch = []
        self.split_branch(tagstokens)

    def split_branch(self, tt):
        i = 0
        begin = 0
        and_or_begin = ''
        wtg = []  # for waiting
        tag = ''
        while i <= tt.length:
            if i < tt.length:
                tag = tt.tags[i]
            if wait(wtg):
                wtg.pop(-1)
            elif tag in gv.GRAMMAR.opening_tags:
                wtg.append(gv.GRAMMAR.opening_tags[tag])
            if (wait(wtg) and tag in gv.GRAMMAR.grammar['ABS_TERMINATOR'])\
                    or i == tt.length - 1:
                self.list_branch.append(ACB(TT(tt.tokens[begin:i + 1],
                                               tt.tags[begin:i + 1]),
                                            and_or_begin,
                                            tag == 'PIPE'))
                begin = i + 1
                and_or_begin = ''
            if tag in ['CMDAND', 'CMDOR']:
                and_or_begin = tag
            i += 1

    def __str__(self):
        return '\n'.join([str(branch) for branch in self.list_branch])


class ACB():  # AbstractCommandBranch
    """docstring for AbstractSyntaxTree."""

    def __init__(self, tt, begin_andor, pipe_end):
        self.tagstokens = tt
        self.begin_andor = begin_andor
        self.pipe_end = pipe_end
        self.type = 'NORMAL'
        if len(tt.tags) > 0 and tt.tags[0] in gv.GRAMMAR.opening_tags:
            self.type = tt.tags[0]
        self.subcmd = []  # list of AST
        self.check_subcmd()

    def check_subcmd(self):
        i = 0
        begin = 0
        wtg = []  # for waiting
        tag = ''
        while i <= self.tagstokens.length:
            if i < self.tagstokens.length:
                tag = self.tagstokens.tags[i]
            if len(wtg) > 0 and tag == wtg[-1]:
                wtg.pop(-1)
            if tag in gv.GRAMMAR.opening_tags:
                wtg.append(gv.GRAMMAR.opening_tags[tag])
                begin = i
            elif len(wtg) > 0 and tag == wtg[-1]:
                self.subcmd.append(AST(TT(self.tagstokens.tokens[begin:i],
                                          self.tagstokens.tags[begin:i])))
            i += 1

    def __str__(self):
        cmd = '{:_<10}:'.format(self.type)
        cmd += '{:_<4}'.format(self.begin_andor)
        cmd += '{}'.format(''.join(self.tagstokens.tokens))
        if self.pipe_end:
            cmd += 'PIPE'
        if self.subcmd != []:
            cmd += '\n'.join([str(cmd) for cmd in self.subcmd])
        return cmd
