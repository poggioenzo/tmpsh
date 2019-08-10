#!/usr/bin/env python3

import utils.global_var as gv
import os

def getenv(variable):
    """os.getenv equivalent for our local environnement"""
    return gv.ENVIRON.get(variable, None)

def setenv(variable, value):
    """os.setenv like function"""
    gv.ENVIRON[variable] = value

def getvar(variable):
    """Equivalent to getenv but for local variable"""
    return gv.LOCAL_VAR.get(variable, None)

def setvar(variable, value):
    """Set up value to a variable in the local environnement"""
    gv.LOCAL_VAR[variable] = value

def update_var(variable, value, type_update, only_env=False):
    """
    Change a variable value. Manage internally if it is a environnement or a local
    variable
    """
    environ_var = getenv(variable)
    if environ_var != None or only_env:
        if type_update == "CONCATENATION":
            value = environ_var + value
        setenv(variable, value)
    else:
        if type_update == "CONCATENATION":
            old_var = getvar(variable)
            value = old_var + value if old_var != None else value
        setvar(variable, value)

def retrieve_variable(variable):
    """
    Return from the string in form $VARIABLE
    the content of the variable.
    """
    if variable == "?":
        return str(gv.LAST_STATUS)
    elif variable == "$":
        return str(os.getpid())
    value = getenv(variable)
    if value == None:
        value = getvar(variable)
    return value if value != None else ""

def retrieve_assignation(branch):
    """
    Find the list of assignation containing in the tagstokens.
    Return a list of tuples as [(key, mode, value), (...)]
    """
    assignation_list = []
    last_stmt = None
    index = 0
    tagstok = branch.tagstokens
    index_to_del = 0
    while index < tagstok.length:
        if last_stmt == None and tagstok.tags[index] == "STMT":
            last_stmt = tagstok.tokens[index]
        elif tagstok.tags[index] in ["CONCATENATION", "ASSIGNATION_EQUAL"]:
            index_to_del = index + 1
            assignation_list.append((last_stmt, tagstok.tags[index], tagstok.tokens[index_to_del]))
            index = index_to_del
            last_stmt = None
        index += 1
    if len(assignation_list) > 0:
        del tagstok.tags[:index_to_del + 1]
        del tagstok.tokens[:index_to_del + 1]
        tagstok.update_length()
    return assignation_list

def variables_config(variables, only_env=False):
    """
    Facility to set the variables list [(key, mode, value), (...)] according
    to his key=value. The mode specify if it is
    a CONCATENATION or an ASSIGNATION_EQUAL.
    Set up the variable only to the environnement if specified.
    """
    nbr_var = len(variables)
    index = 0
    while index < nbr_var:
        variable_data = variables[index]
        mode = variable_data[1]
        key = variable_data[0]
        value = variable_data[2]
        update_var(key, value, mode, only_env)
        index += 1

def replace_variable(branch):
    """
    Replace each variable within a single branch.
    Make a recursive calling if there is any dquotes element inside
    the branch.
    """
    index = 0
    index_subast = 0
    while index < branch.tagstokens.length:
        tag = branch.tagstokens.tags[index]
        token = branch.tagstokens.tokens[index]
        if tag == "VAR":
            variable = retrieve_variable(token[1:])
            branch.tagstokens.tokens[index] = variable
            branch.tagstokens.tags[index] = "STMT"
        elif tag == "SUBAST":
            if branch.subast[index_subast].type == "DQUOTES":
                replace_variable(branch.subast[index_subast].list_branch[0])
            index_subast += 1
        index += 1
