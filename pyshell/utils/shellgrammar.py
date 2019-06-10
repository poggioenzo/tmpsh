#!/usr/bin/env python3
import utils.strcontain as sc
from utils.grammar import Grammar


def get_maxlen(iterator):
    return max([len(k) for k in iterator])


class ShellGrammar(Grammar):
    """docstring for ."""

    def __init__(self, path='grammar/grammar.txt'):
        super().__init__(path)
        self.spaces = [' ', '\t']
        self.escape = ''
        self.opening_tags = {}
        self.dquotes_opening_tags = {}
        self.get_escape()
        self.add_symbol('\n', 'NEW_LINE')
        self.get_leaf_op()
        if 'ESCAPE' in self.grammar:
            self.leaf_op.remove(self.grammar['ESCAPE'][0])
        self.maxlen_leaf_op = get_maxlen(self.leaf_op)
        self.get_opening_tags()
        self.get_abstract_terminator()

    def get_abstract_terminator(self):
        if 'TERMINATOR' in self.grammar:
            self.grammar['ABSTRACT_TERMINATOR'] = \
                self.grammar['TERMINATOR'] + ['BACKGROUND_JOBS']

    def get_escape(self):
        if 'ESCAPE' in self.grammar:
            self.escape = self.grammar['ESCAPE'][0]

    def get_list_op(self, func):
        return [key for key in self.reverse if not func(key)]

    def get_leaf_op(self):
        self.leaf_op = self.get_list_op(sc.containalphanum)

    def get_opening_tags(self):
        if 'SUB_PROCESS' in self.grammar:
            opening_tags = self.grammar['SUB_PROCESS']
            if 'QUOTES' in self.grammar:
                opening_tags.extend(self.grammar['QUOTES'])
            for tag in opening_tags:
                tag_split = tag.split()
                tag_op = tag_split[0]
                tag_end = tag_split[-1]
                self.opening_tags[tag_op] = tag_end
            if 'QUOTES' in self.grammar:
                self.get_dquotes_opening_tags()

    def get_dquotes_opening_tags(self):
        if 'BRACEPARAM' in self.opening_tags:
            self.dquotes_opening_tags['BRACEPARAM'] = \
                self.opening_tags['BRACEPARAM']
        if 'CMDSUBST1' in self.opening_tags:
            self.dquotes_opening_tags['CMDSUBST1'] = \
                self.opening_tags['CMDSUBST1']
