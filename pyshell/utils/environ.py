#!/usr/bin/env python3

import utils.global_var as gv

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
    if len(variable) == 1:
        return
    search_value = variable[1:]
    if search_value == "?":
        return str(gv.LAST_STATUS)
    elif search_value == "$":
        return str(os.getpid())
    value = getenv(search_value)
    if value == None:
        value = getvar(search_value)
    return value if value != None else ""
