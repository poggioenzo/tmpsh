import utils.global_var as gv
import utils.tokenizer as tk
import utils.strcontain as sc


class TagsTokens():
    def __init__(self, term_inputs, ):
        self.term_inputs = term_inputs
        self.tokens = []
        tk.tokenize(term_inputs, self.tokens)
        self.tags = []
        self.get_tags()

    def get_tags(self):
        for tok in self.tokens:
            if tok in gv.GRAMMAR.leaf_op:
                self.tags.append(gv.GRAMMAR.reverse[tok])
            elif sc.containspaces(tok):
                self.tags.append('SPACES')
            else:
                self.tags.append('STMT')

    def __str__(self):
        import pandas as pd
        dataframe = pd.DataFrame([self.tags, self.tokens])
        return str(dataframe)
