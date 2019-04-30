#!/usr/bin/env python3

import utils.tokenizer as tk
from utils.readgrammar import ShellGrammar
import utils.strcontain as sc
import utils.shift_reduce as sr
global GRAMMAR
GRAMMAR = ShellGrammar()


# OPTIMIZE: if error stop lexing return


class Cmd(object):
    # TODO Facto: don't repeat shift_reduce of sub in upper branch:
    # use sub[i].start and sub[i].stop to replace by sub[i].stack
    def __init__(self, start, tags, ends=[]):
        self.start = start
        self.end = start
        self.ends = GRAMMAR.grammar['TERMINATOR']
        if ends != []:
            self.ends = ends
        self.sub = []
        self.get_end(tags)
        if ends != []:
            self.start -= 1
        self.tags = tags[self.start: self.end]

        self.reduce_shift()
        self.incomplete = False
        self.valid = False
        self.error_after = ''
        if self.stack == ['CMD']:
            self.valid = True
        else:
            self.is_incomplete_key()
        print(self.stack)
        print('valid:', self.valid, '| incomplete:', self.incomplete)
        if self.error_after != '':
            print('error after:', self.error_after)

    # def is_incomplete_key(self):
    #     i = 0
    #     len_stack = len(self.stack)
    #     stack = self.stack
    #     while i < len_stack:
    #         if stack[i] in GRAMMAR.opening_tags:
    #             pass
    #         elif not tk.ops_begin_with(' '.join(stack[i:]), GRAMMAR.reverse):
    #             self.error_after = GRAMMAR.grammar[stack[i]]
    #             return
    #         i += 1
    #     self.incomplete = True

    def reduce_shift(self):
        stack = []
        i = 0
        len_tags = len(self.tags)
        while (i < len_tags + 1):
            instack = sr.keyinstack(stack, GRAMMAR)
            if instack > -1:
                stack = sr.reduce_all(stack, instack, GRAMMAR)
            elif i < len_tags:
                if self.tags[i] == 'SPACES':
                    pass
                else:
                    stack.append(self.tags[i])
                i += 1
            else:
                break
        self.stack = stack

    def get_end(self, tags):
        i = self.start
        len_tags = len(tags)
        while i < len_tags:
            curr_tag = tags[i]
            if curr_tag in self.ends:
                break
            elif curr_tag in GRAMMAR.opening_tags:
                i += 1
                subcmd = Cmd(i, tags, [GRAMMAR.opening_tags[curr_tag]])
                i = subcmd.end
                self.sub.append(subcmd)
            else:
                i += 1
        i += 1
        if i > len_tags:
            i = len_tags
        self.end = i


class ListCommands(object):
    def __init__(self, term_inputs):
        self.term_inputs = term_inputs
        self.tokens = []
        tk.tokenize(term_inputs, self.tokens)
        self.get_tags()
        self.get_tree_commands()
        self.error = ''

    def get_tags(self):
        tags = []
        for tok in self.tokens:
            if tok in GRAMMAR.leaf_op:
                tags.append(GRAMMAR.reverse[tok])
            elif sc.containspaces(tok):
                tags.append('SPACES')
            else:
                tags.append('STMT')
        self.tags = tags

    def get_tree_commands(self):
        tags = self.tags
        tree_commands = []
        i = 0
        len_tags = len(tags)
        while i < len_tags:
            cmd = Cmd(i, tags)
            i = cmd.end
            tree_commands.append(cmd)
        self.tree_commands = tree_commands
