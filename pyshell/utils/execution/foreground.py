import os
import utils.global_var as gv
import termios

def set_foreground(pgid):
    """
    Use to be called by a the a shell to give
    the foreground to any pgid, including himself.
    """
    with open("/dev/tty") as control_term:
        os.tcsetpgrp(control_term.fileno(), pgid)

def restore_tcattr():
    with open("/dev/tty") as control_term:
        termios.tcsetattr(control_term.fileno(), termios.TCSADRAIN, \
            gv.TCSETTINGS)

