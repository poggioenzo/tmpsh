#!/usr/bin/env python3

import utils.tokenizer as tk


def revkeyinstack(stack, grammar):
    len_stack = len(stack) - 1
    while len_stack > -1:
        key = ' '.join(stack[len_stack:])
        if tk.ops_begin_with(key, grammar.reverse):
            return True
        del key
        len_stack -= 1
    return False


def keyinstack(stack, grammar):
    len_stack = len(stack)
    i = 0
    while i < len_stack:
        key = ' '.join(stack[i:])
        if key in grammar.reverse:
            return i
        del key
        i += 1
    return -1


def reduce(stack, instack, grammar):
    ret = (stack[:instack] + [grammar.reverse[' '.join(stack[instack:])]])
    return ret


def reduce_all(stack, instack, grammar):
    while instack > -1:
        stack = reduce(stack, instack, grammar)
        instack = keyinstack(stack, grammar)
    return stack


def shift_reduce(tags, grammar):
    stack = []
    i = 0
    len_tags = len(tags)
    while i < len_tags:
        instack = keyinstack(stack, grammar)
        if instack > -1:
            stack = reduce_all(stack, instack, grammar)
        else:
            if tags[i] == 'SPACES':
                pass
            else:
                stack.append(tags[i])
            i += 1
    instack = keyinstack(stack, grammar)
    if instack > -1:
        stack = reduce_all(stack, instack, grammar)
    return stack


def tagstokens_shift_reduce(tagstokens, grammar):
    stack = []
    i = 0
    len_tags = len(tagstokens.tags)
    while i <= len_tags:
        instack = keyinstack(stack, grammar)
        if instack > -1:
            stack = reduce_all(stack, instack, grammar)
        else:
            if i < len_tags and tagstokens.tags[i] == 'SPACES':
                pass
            elif stack == [] or revkeyinstack(stack, grammar):
                if i < len_tags:
                    stack.append(tagstokens.tags[i])
            else:
                tagstokens.valid = False
                tagstokens.token_error = tagstokens.find_prev_token(i - 1)
                break
            i += 1
    if tagstokens.valid and len(stack) > 0 and stack != ['CMD']:
        tagstokens.incomplete = True
    return stack
