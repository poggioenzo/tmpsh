#!/usr/bin/env python3

import utils.global_var as gv
from utils.tagstokens import TagsTokens
from utils.abstractcommandbranch import AbstractCommandBranch as ACB


class AbstractSyntaxTree():
    """docstring for AbstractSyntaxTree."""

    def __init__(self, tagstokens):
        self.list_branch = []
        self.split_branch(tagstokens)

    def split_branch(self, tt):
        i = 0
        len_tags = len(tt.tags)
        while i < len_tags:
            tag = tt.tags[i]
            i += 1
