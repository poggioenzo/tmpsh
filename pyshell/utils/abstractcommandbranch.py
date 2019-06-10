#!/usr/bin/env python3

import utils.global_var as gv
from utils.tagstokens import TagsTokens
from utils.abstractsyntaxtree import AbstractSyntaxTree as AST


class AbstractCommandBranch():
    """docstring for AbstractSyntaxTree."""

    def __init__(self, tagstokens):
        self.tagstokens = tagstokens
