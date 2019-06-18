#!/usr/bin/env python3

import utils.global_var as gv
from utils.tagstokens import TagsTokens as TT


def split_shift(string):
    return '\n'.join(['\t{}'.format(x) for x in string.split('\n')])[:-1]


class AST():  # AbstractSyntaxTree
    """docstring for AbstractSyntaxTree."""

    def __init__(self, tagstokens):
        self.list_branch = []
        self.type = 'ROOT'
        self.split_branch(tagstokens)

    def set_type(self, ast_type):
        self.type = ast_type

    def split_branch(self, tt):
        i = 0
        begin = 0
        and_or_begin = ''
        tag = ''
        while i < tt.length:
            tag = tt.tags[i]
            if tag in gv.GRAMMAR.opening_tags:
                i = tt.skip_openning_tags(i) - 1
            elif tag in gv.GRAMMAR.grammar['ABS_TERMINATOR']:
                self.list_branch.append(ACB(tt[begin:i], and_or_begin, tag))
                begin = i + 1
                and_or_begin = ''
            if tag in ['CMDAND', 'CMDOR']:
                and_or_begin = tag
            i += 1
        self.list_branch.append(ACB(tt[begin:i], and_or_begin, tag))

    def __str__(self):
        return '{:_^12}:\n'.format(self.type) + split_shift('\n'.join(
            [str(branch) for branch in self.list_branch]))


class ACB():  # AbstractCommandBranch
    """docstring for AbstractSyntaxTree."""

    def __init__(self, tt, begin_andor, tag_end):
        self.tagstokens = tt
        self.begin_andor = begin_andor
        self.tag_end = tag_end if tag_end in [
            'BACKGROUND_JOBS', 'PIPE'] else ''
        self.subast = []  # list of AST
        self.subcmd_type = []
        self.redirectionfd = []
        self.check_subast()
        self.set_subast_type()

    def set_subast_type(self):
        for type_command, sub_ast in zip(self.subcmd_type, self.subast):
            sub_ast.set_type(type_command)

    def check_subast(self):
        i = 0
        begin = 0
        tag = ''
        while i < self.tagstokens.length:
            tag = self.tagstokens.tags[i]
            if tag in gv.GRAMMAR.opening_tags:
                begin = i + 1
                self.subcmd_type.append(tag)
                i = self.tagstokens.skip_openning_tags(i) - 1
                self.subast.append(AST(self.tagstokens[begin:i]))
                self.tagstokens[begin - 1:i + 1] = [
                    ['SUBAST'], ['↓subast{}↓'.format(len(self.subast) - 1)]]
                i = begin
            i += 1

    def check_redirection(self):
        lentags = self.tagstokens.length - 1
        tag = ''
        while lentags >= 0:
            tag = self.tagstokens.tags[lentags]
            if tag in gv.GRAMMAR.grammar['REDIRECTION']:
                lol = 0
            lentags -= 1

    def __str__(self):
        cmd = '{:_^10}'.format(self.begin_andor)
        cmd += '{}'.format(''.join(self.tagstokens.tokens))
        cmd += '{:_^17}\n'.format(self.tag_end)
        if self.subast != []:
            cmd += split_shift('\n'.join([str(cmd) for cmd in self.subast]))
        return cmd


class RedirectionFD():
    """docstring forRedirec."""

    def __init__(self, tagstokens, redirection_type):
        self.tagstokens = tagstokens
        self.type = redirection_type
