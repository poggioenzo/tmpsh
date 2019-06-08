#! /usr/bin/env python3

import utils.global_var as gv
import utils.tokenizer as tk
import utils.strcontain as sc


class TagsTokens():
    def __init__(self, tags=None, tokens=None):
        self.tokens = tags if tags else []
        self.tags = tokens if tokens else []

    def init_with_input(self, term_inputs):
        tk.tokenize(term_inputs, self.tokens)
        for tok in self.tokens:
            if tok in gv.GRAMMAR.leaf_op:
                self.tags.append(gv.GRAMMAR.reverse[tok])
            elif sc.containspaces(tok):
                self.tags.append('SPACES')
            else:
                self.tags.append('STMT')
        return self

    def __str__(self):
        import pandas as pd
        dataframe = pd.DataFrame([self.tags, self.tokens])
        return str(dataframe)
