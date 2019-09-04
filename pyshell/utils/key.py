#!/usr/bin/env python3

# import utils.global_var as gv


def get_key(key, tag, tok, minus):
    if minus:
        if key == '' and tag == 'SPACES':
            return ''
    return key + tok


def modifify_gold_key(gold_key):
    if gold_key[0] in '"\'' and gold_key[-1] in '"\'':
        return gold_key[1:-1]
    return gold_key


def quoted_gold_key(gold_key):
    return gold_key[0] in '"\'' and gold_key[-1] in '"\''


def dquoted_gold_key(gold_key):
    return gold_key[0] in '"' and gold_key[-1] in '"'
