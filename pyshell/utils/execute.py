#!/usr/bin/env python3

class Executor:
    """From an AST, run each command"""
    def __init__(self, ast):
        self.ast = ast
        print(ast)
