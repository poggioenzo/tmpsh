#!/usr/bin/env python3


# TODO: quotes gesture
# TODO: sub arboresence in list
# TODO: alias gesture
# TODO: error : return tokens
# TODO: branch on open CMDOR CMDAND end TERMINATOR


import utils.global_var as gv
import utils.shift_reduce as sr
from utils.tagstokens import TagsTokens


class Cmd():
    def __init__(self, tags, ends=None):
        # self.start = start
        # self.end = start
        self.tagstokens = TagsTokens()
        self.incomplete = False
        self.valid = True
        self.sub = []
        self.stack = []
        self.error_near = -1

        if ends != []:
            self.get_end(tags, ends)
            self.start -= 1
        else:
            self.get_end(tags, gv.GRAMMAR.grammar['TERMINATOR'])
        self.tags = tags[self.start: self.end]
        self.is_valid_complete()

    def is_valid_complete(self):
        for subcmd in self.sub:
            if not subcmd.valid:
                self.valid = False
                self.error_near = subcmd.error_near
            if subcmd.incomplete:
                self.incomplete = True
        if self.valid:
            self.shift_reduce()

    def shift_reduce(self):
        stack = []
        i = 0
        len_tags = len(self.tags)
        while i <= len_tags:
            instack = sr.keyinstack(stack, gv.GRAMMAR)
            if instack > -1:
                stack = sr.reduce_all(stack, instack, gv.GRAMMAR)
            else:
                if i < len_tags and self.tags[i] == 'SPACES':
                    pass
                elif stack == [] or sr.revkeyinstack(stack, gv.GRAMMAR):
                    if i < len_tags:
                        stack.append(self.tags[i])
                else:
                    self.valid = False
                    self.error_near = i - 1
                    break
                i += 1
        if self.valid and stack != ['CMD']:
            self.incomplete = True
        self.stack = stack

    def get_end(self, tags, ends):
        i = self.start
        len_tags = len(tags)
        while i < len_tags:
            curr_tag = tags[i]
            if curr_tag in ends:
                break
            elif curr_tag in gv.GRAMMAR.opening_tags:
                i += 1
                subcmd = Cmd(i, tags, [gv.GRAMMAR.opening_tags[curr_tag]])
                i = subcmd.end
                self.sub.append(subcmd)
            else:
                i += 1
        i += 1
        if i > len_tags:
            i = len_tags
        self.end = i


class ListCommands():
    def __init__(self, tagstokens):
        self.list_commands = []
        self.to_complete = []
        self.error = ''
        self.valid = True
        self.incomplete = False
        if self.incomplete:
            # self.incomplete = True
            self.to_complete.append('>')

    def get_to_complete(self):
        pass

    def get_error(self):
        pass
