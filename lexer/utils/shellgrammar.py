#!/usr/bin/env python3
import utils.strcontain as sc
from utils.grammar import Grammar


class ShellGrammar(Grammar):
    """docstring for ."""

    def __init__(self, path='grammar.txt'):
        super().__init__(path)
        self.spaces = [' ', '\t']
        self.escape = ''
        self.get_escape()
        self.add_symbol('\n', 'NEW_LINE')
        self.get_leaf_op()
        if 'ESCAPE' in self.grammar:
            self.leaf_op.remove(self.grammar['ESCAPE'][0])
        self.maxlen_leaf_op = self.get_maxlen(self.leaf_op)
        self.get_opening_tags()

    def get_escape(self):
        if 'ESCAPE' in self.grammar:
            self.escape = self.grammar['ESCAPE'][0]

    def get_list_op(self, func):
        return [key for key in self.reverse if not func(key)]

    def get_leaf_op(self):
        self.leaf_op = self.get_list_op(sc.containalphanum)

    def get_maxlen(self, iter):
        return max([len(k) for k in iter])

    # def get_first(self, iter):
    #     return [k[0] for k in iter]

    def get_opening_tags(self):
        self.opening_tags = {}
        if 'SUB_PROCESS' in self.grammar and 'QUOTES' in self.grammar:
            opening_tags = self.grammar['SUB_PROCESS']
            opening_tags.extend(self.grammar['QUOTES'])
            for tag in opening_tags:
                tag_split = tag.split()
                tag_op = tag_split[0]
                tag_end = tag_split[-1]
                self.opening_tags[tag_op] = tag_end
