#!/usr/bin/env python3

from global_var import ENVIRON, LOCAL_VAR

def getenv(variable):
    """os.getenv equivalent for our local environnement"""
    return ENVIRON.get(variable, None)

def setenv(variable, value):
    """os.setenv like function"""
    ENVIRON[variable] = value

def getvar(variable):
    """Equivalent to getenv but for local variable"""
    return LOCAL_VAR.get(variable, None)

def setvar(variable, value):
    """Set up value to a variable in the local environnement"""
    env_var = getenv(variable)
    LOCAL_VAR[variable] = value

def update_var(variable, value, type_update):
    """
    Change a variable value. Manage internally if it is a environnement or a local
    variable
    """
    environ_var = getenv(variable)
    if environ_var != None:
        if type_update == "INCREMENT":
            value = environ_var + value
        setenv(variable, value)
    else:
        if type_update == "INCREMENT":
            old_var = getvar(variable)
            value = old_var + value if old_var != None else value
        setvar(variable, value)
