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


def keyinstack(stack, grammar, next_tag=''):
    len_stack = len(stack)
    key = ''
    extend_key = ''
    i = 0
    while i < len_stack and extend_key not in grammar.reverse:
        key = ' '.join(stack[i:])
        extend_key = key + ' ' + next_tag
        if key in grammar.reverse:
            if extend_key in grammar.reverse:
                break
            return i
        i += 1
    return -1


def reduce(stack, instack, grammar):
    ret = (stack[:instack] + [grammar.reverse[' '.join(stack[instack:])]])
    return ret


def reduce_all(stack, instack, grammar, next_tag):
    while instack > -1:
        stack = reduce(stack, instack, grammar)
        instack = keyinstack(stack, grammar, next_tag)
    return stack


def check_forbidden(tags, grammar):
    i = 0
    len_tags = len(tags)
    instack = []
    key = ''
    spaces = 0
    while i < len_tags:
        key = ' '.join(instack)
        if key in grammar.reverse and grammar.reverse[key] == 'FORBIDDEN':
            if tags[i - len(instack)] == 'SPACES':
                tags[i - len(instack) - 1] = 'FORBIDDEN'
            else:
                tags[i - len(instack)] = 'FORBIDDEN'
            spaces = 0
            instack = []
            break
        elif tags[i] == 'SPACES':
            spaces += 1
        elif instack == [] or tk.ops_begin_with(
                key, grammar.grammar['FORBIDDEN']):
            instack.append(tags[i])
        else:
            instack = []
        i += 1
    key = ' '.join(instack)
    if key in grammar.reverse and grammar.reverse[key] == 'FORBIDDEN':
        tags[i + spaces - len(instack)] = 'FORBIDDEN'
    return tags


def shift_reduce(tags, grammar):
    stack = []
    i = 0
    instack = 0
    len_tags = len(tags)
    next_tag = ''

    tags = check_forbidden(tags, grammar)
    while i < len_tags:
        next_tag = tags[i]
        instack = keyinstack(stack, grammar, next_tag)
        if instack > -1:
            stack = reduce_all(stack, instack, grammar, next_tag)
        else:
            if next_tag == 'SPACES':
                pass
            else:
                stack.append(next_tag)
            i += 1
    instack = keyinstack(stack, grammar, next_tag)
    if instack > -1:
        stack = reduce_all(stack, instack, grammar, next_tag)
    return stack


def tagstokens_shift_reduce(tagstokens, grammar):
    stack = []
    i = 0
    instack = 0
    len_tags = len(tagstokens.tags)
    next_tag = ''

    tagstokens.tags = check_forbidden(tagstokens.tags, grammar)
    while i <= len_tags:
        instack = keyinstack(stack, grammar, next_tag)
        stack = check_forbidden(stack, grammar)
        if "FORBIDDEN" in stack:
            tagstokens.valid = False
            tagstokens.token_error = tagstokens.find_prev_token(i - 1)
            break
        if instack > -1:
            stack = reduce_all(stack, instack, grammar, next_tag)
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
    stack = check_forbidden(stack, grammar)
    # if "FORBIDDEN" in stack:
    #     tagstokens.valid = False
    #     tagstokens.token_error = 'bad syntax'
    stack = ['CMD' if elt == 'COMMAND_SH' else elt for elt in stack]
    if tagstokens.valid and len(stack) > 0 and not all(
            [elt == 'CMD'for elt in stack]):
        tagstokens.incomplete = True
    return stack
