#!/usr/bin/env python3

"""
Module for class AbstractSyntaxTree (AST) and AbstractCommandBranch (ACB).

These classes are done to represente the syntax shell in a tree.
"""

import utils.global_var as gv


def split_shift(string):
    """Split on \n add \t at the beginnin of each lines join on \n."""
    return '\n'.join(['\t{}'.format(x) for x in string.split('\n')])[:-1]


class AST():
    """
    Class to create AST (AbstractSyntaxTree) object.

    Param:
        tagstokens: TagsTokens object.
    Attributes:
        list_branch: list containing AbstractCommandBranch objects.
        type: a string which indicate the type of AbstractSyntaxTree.
        link_fd: ???
    """

    def __init__(self, tagstokens):
        """Constructor for AST object."""
        self.list_branch = []
        self.type = 'ROOT'
        self.link_fd = None
        self.pid = None
        self.command = None
        self.complete = False
        self.split_branch(tagstokens)

    @property
    def type(self):
        """Getter for attribute type."""
        return self._type

    @type.setter
    def type(self, ast_type):
        """Setter for attribute type."""
        self._type = ast_type

    def split_branch(self, tagstokens):
        """
        Fill list_branch of ACB separate using tagstokens (TagsTokens).

        Each command branch is separate on ABS_TERMINATOR (; || && & ...).
        """
        i = 0
        begin = 0
        and_or_begin = ''
        tag = ''
        while i < tagstokens.length:
            tag = tagstokens.tags[i]
            if tag in gv.GRAMMAR.opening_tags:
                i = tagstokens.skip_openning_tags(i) - 1
            elif tag in gv.GRAMMAR.grammar['ABS_TERMINATOR']:
                self.list_branch.append(
                    ACB(tagstokens.copytt(begin, i), and_or_begin, tag))
                begin = i + 1
                and_or_begin = ''
            if tag in ['CMDAND', 'CMDOR']:
                and_or_begin = tag
            i += 1
        if begin != i:
            self.list_branch.append(
                ACB(tagstokens.copytt(begin, i), and_or_begin, tag))

    def __str__(self):
        """Print the type of AST then each branchs of the AST shifted."""
        return '{:_^12}:\n'.format(self.type) + split_shift('\n'.join(
            [str(branch) for branch in self.list_branch]))

    def get_command(self):
        """
        Format the command of the entire ast.
        Call the get_command of each branch and concatenate the content
        of all branches.
        """
        index = 0
        command = ""
        while index < len(self.list_branch):
            self.list_branch[index].get_command()
            command += self.list_branch[index].command
            index += 1
        self.command = command
        pass


class ACB():
    """
    Class to create ACB (AbstractCommandBranch) object.

    Param:
        tagstokens: TagsTokens object.
        begin_andor: string which contain the CMDAND, CMDOR or nothing.
        tag_end: string which contain the last tag of the command in the AST.
    Attributes:
        All params are attributes.
        subast:
        subcmd_type:

    """

    def __init__(self, tagstokens, begin_andor, tag_end):
        """Constructor for ACB object."""
        self.tagstokens = tagstokens
        self.begin_andor = begin_andor
        self.tag_end = tag_end if tag_end in \
            gv.GRAMMAR.grammar['ABS_TERMINATOR'] else ''
        self.subast = []  # list of AST
        self.subcmd_type = []
        self.redirectionfd = []
        self.command = None
        self.stdin = None
        self.stdout = None
        self.background = False
        self.status = None
        self.pid = None
        self.pgid = 0
        self.complete = False
        self.check_subast()
        self.set_subast_type()
        self.check_redirection()

    @property
    def has_subast(self):
        return len(self.subast) > 0

    def set_subast_type(self):
        for type_command, sub_ast in zip(self.subcmd_type, self.subast):
            sub_ast.type = type_command

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
                self.subast.append(AST(self.tagstokens.copytt(begin, i)))
                self.tagstokens[begin - 1:i + 1] = [
                    ['SUBAST'], ['{}'.format(len(self.subast) - 1)]]
                i = begin - 1
            i += 1

    def check_redirection(self):
        lentags = self.tagstokens.length - 1
        previous = 0
        tag = ''
        source = None
        while lentags >= 0:
            tag = self.tagstokens.tags[lentags]
            if tag in gv.GRAMMAR.grammar['REDIRECTION']:
                if lentags > 0 and \
                        self.tagstokens.find_prev_token(
                            lentags - 1).isdigit() and tag != 'HEREDOC':
                    source = self.tagstokens.find_prev_token(lentags - 1)
                self.redirectionfd.append(
                    RedirectionFD(self.tagstokens.copytt(previous),
                                  tag, source))
                del self.tagstokens[previous]
                del self.tagstokens[lentags]
                if source:
                    del self.tagstokens[self.tagstokens.find_prev_ind_token(
                        lentags - 1)]
                    self.tagstokens.update_length()
                    lentags = self.tagstokens.length - 1
                    source = None
            elif tag != 'SPACES':
                previous = lentags
            lentags -= 1
        self.tagstokens.strip()
        self.tagstokens.update_length()
        self.redirectionfd = list(reversed(self.redirectionfd))

    def __str__(self):
        cmd = '{:_^10}'.format(self.begin_andor)
        cmd += '{}'.format(''.join(self.tagstokens.tokens))
        cmd += '{:_^17}'.format(self.tag_end)
        if self.redirectionfd != []:
            cmd += ' fd-> ' + ' '.join([str(fd) for fd in self.redirectionfd])
        cmd += '\n'
        if self.subast != []:
            cmd += split_shift('\n'.join([str(cmd) for cmd in self.subast]))
        return cmd

    def get_command(self):
        """
        From each tags/tokens, re-create the command given by the user.
        Go through each token and concate it the the right way, depending
        if it a simple token or an other subast.
        """
        final_str = ""
        index = 0
        while index < self.tagstokens.length:
            if self.tagstokens.tags[index] == "SPACES":
                final_str += " "
            elif self.tagstokens.tags[index] == "STMT":
                final_str += self.tagstokens.tokens[index]
            elif self.tagstokens.tags[index] == "SUBAST":
                ast_index = self.tagstokens.tokens[index].split(' ')[-1]
                subast = self.subast[int(ast_index)]
                subast.get_command()
                prefix = gv.GRAMMAR.grammar[subast.type][0]
                if subast.type in ["BRACEPARAM", "CURSH"]:
                    suffix = gv.GRAMMAR.grammar["END_BRACE"][0]
                else:
                    suffix = gv.GRAMMAR.grammar["END_BRACKET"][0]
                final_str += prefix + subast.command + suffix
            index += 1
        end = gv.GRAMMAR.grammar[self.tag_end][0] if self.tag_end != '' else ''
        self.command = final_str + end


class RedirectionFD():
    """docstring forRedirec."""

    def __init__(self, tagstokens, redirection_type, source=None):
        self.tagstokens = tagstokens
        self.type = redirection_type
        self.heredoc_ast = None
        if source is None:
            source = 0 if self.type in ["READ_FROM_FD", "READ_FROM"] else 1

        self.source = int(source)
        self.dest = self.tagstokens.tokens[-1]
        self.close = False
        self.error = False
        if self.type in ["READ_FROM_FD", "TRUNC_TO_FD"]:
            last_stmt = tagstokens.tokens[-1]
            if last_stmt[-1] == '-':
                self.close = True
        if self.type in ["HEREDOC", "HEREDOCMINUS"]:
            self.get_heredoc_ast()

    def get_heredoc_ast(self):
        if gv.HEREDOCS != []:
            tagstokens = gv.HEREDOCS[-1].tagstokens
            del gv.HEREDOCS[-1]
            self.heredoc_ast = AST(tagstokens)

    def __str__(self):
        str0 = '{}: {} source:{}'.format(self.type,
                                         ''.join(self.tagstokens.tokens),
                                         self.source)
        if self.heredoc_ast:
            str0 += '\n' + split_shift(str(self.heredoc_ast))
        return str0
