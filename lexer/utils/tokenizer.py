#!/usr/bin/env python3

def span_sub(command, grammar, tokens, top=1):
    i = 0
    j = 1
    maxlen = max([len(k) for k in grammar.opening_op])
    length_cmd = len(command)
    while j <= maxlen and i == 0:
        if command[:j] in grammar.opening_op:
            key = command[:j]
            i += j
            while i < length_cmd:
                if command[i] == grammar.grammar['ESCAPE'][0]:
                    i += 1
                elif command[i] in grammar.begin_opening_op:
                    i += span_sub(command[i:], grammar, tokens, 0)
                elif command[i] == grammar.opening_op[key][0]:
                    break
                i += 1
        j += 1
    if i != 0 and top:
        tokens.append(command[:i + 1])
    return i

def span_op(command, grammar, tokens):
    j = 1
    maxlen = max([len(k) for k in grammar.no_scope_op])
    while j <= maxlen:
        if command[:j] in grammar.no_scope_op:
            j += 1
        else:
            break
    j -= 1
    tokens.append(command[:j])
    return j

def tokenize(command, grammar, tokens):
    length_cmd = len(command)
    current = ""
    i = 0
    while i < length_cmd:
        if command[i] in grammar.begin_opening_op:
            i += span_sub(command[i:], grammar, tokens) + 1
        elif command[i] in grammar.begin_no_scope:
            i += span_op(command[i:], grammar, tokens)
        elif command[i] == grammar.grammar['ESCAPE'][0]:
            i += 1
            tokens.append(command[i])
        elif command[i] in ' \r\t':
            if current != "":
                tokens.append(current)
                current = ""
        else:
            current += command[i]
        i += 1
    if current != "":
        tokens.append(current)
