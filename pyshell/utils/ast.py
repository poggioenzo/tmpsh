#!/usr/bin/env python3

import utils.global_var as gv
from utils.tagstokens import TagsTokens as TT


def split_shift(string):
    return '\n'.join(['\t{}'.format(x) for x in string.split('\n')])[:-1]


def wait(waiting, tag=''):
    if tag != '':
        return len(waiting) > 0 and waiting[-1] == tag
    return waiting == []


class AST():  # AbstractSyntaxTree
    """docstring for AbstractSyntaxTree."""

    def __init__(self, tagstokens):
        self.list_branch = []
        self.split_branch(tagstokens)
        self.type = 'ROOT'

    def set_type(self, ast_type):
        self.type = ast_type

    def split_branch(self, tt):
        i = 0
        begin = 0
        and_or_begin = ''
        wtg = []  # for waiting
        tag = ''
        while i < tt.length:
            tag = tt.tags[i]
            if wait(wtg, tag):
                wtg.pop(-1)
            elif tag in gv.GRAMMAR.opening_tags:
                wtg.append(gv.GRAMMAR.opening_tags[tag])
            elif (wait(wtg) and tag in gv.GRAMMAR.grammar['ABS_TERMINATOR']):
                self.list_branch.append(ACB(TT(tt.tokens[begin:i],
                                               tt.tags[begin:i]),
                                            and_or_begin,
                                            tag))
                begin = i + 1
                and_or_begin = ''
            if tag in ['CMDAND', 'CMDOR'] and wtg == []:
                and_or_begin = tag
            i += 1
        self.list_branch.append(ACB(TT(tt.tokens[begin:i], tt.tags[begin:i]),
                                    and_or_begin,
                                    tag))

    def __str__(self):
        return '{:_^12}:\n'.format(self.type) + split_shift('\n'.join(
            [str(branch) for branch in self.list_branch]))


class ACB():  # AbstractCommandBranch
    """docstring for AbstractSyntaxTree."""

    def __init__(self, tt, begin_andor, tag_end):
        self.tagstokens = tt
        self.begin_andor = begin_andor
        self.tag_end = tag_end
        self.subast = []  # list of AST
        self.subcmd_type = []
        self.check_subcmd()
        self.set_subast_type()

    def set_subast_type(self):
        for type_command, sub_ast in zip(self.subcmd_type, self.subast):
            sub_ast.set_type(type_command)

    def check_subcmd(self):
        i = 0
        begin = 0
        wtg = []  # for waiting
        tag = ''
        while i < self.tagstokens.length:
            tag = self.tagstokens.tags[i]
            if tag in gv.GRAMMAR.opening_tags:
                wtg.append(gv.GRAMMAR.opening_tags[tag])
                if len(wtg) == 1:
                    begin = i + 1
                    self.subcmd_type.append(tag)
            elif wait(wtg, tag):
                if len(wtg) == 1:
                    self.subast.append(AST(TT(self.tagstokens.tokens[begin:i],
                                              self.tagstokens.tags[begin:i])))
                wtg.pop(-1)
            i += 1

    def __str__(self):
        cmd = '{:_^10}'.format(self.begin_andor)
        cmd += '{}'.format(''.join(self.tagstokens.tokens))
        cmd += '{:_^15}\n'.format(self.tag_end)
        if self.subast != []:
            cmd += split_shift('\n'.join([str(cmd) for cmd in self.subast]))
        return cmd
