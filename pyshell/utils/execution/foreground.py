import os
import utils.global_var as gv
import termios

"""
Functions to manipulate the controlling terminal directly.
Always open /dev/tty to perform manipulation on the controlling terminal
"""

def set_foreground(pgid):
    """
    Use to be called by a the a shell to give
    the foreground to any pgid, including himself.
    """
    with open("/dev/tty") as control_term:
        os.tcsetpgrp(control_term.fileno(), pgid)

def restore_tcattr():
    """
    Restore the termios configuration, usually called
    when the shell retrieve foreground.
    """
    with open("/dev/tty") as control_term:
        termios.tcsetattr(control_term.fileno(), termios.TCSADRAIN, \
            gv.TCSETTINGS)

def get_tpgid():
    """
    Return the current foreground process group.
    """
    with open("/dev/tty") as control_term:
        return os.tcgetpgrp(control_term.fileno())
