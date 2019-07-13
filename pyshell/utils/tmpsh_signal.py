#!/usr/bin/env python3

import signal

def init_signals():
    signal.signal(signal.SIGTSTP, signal.SIG_IGN)
    signal.signal(signal.SIGTTIN, signal.SIG_IGN)
    signal.signal(signal.SIGTTOU, signal.SIG_IGN)

def reset_signals():
    signal.signal(signal.SIGTSTP, signal.SIG_DFL)
    signal.signal(signal.SIGTTIN, signal.SIG_DFL)
    signal.signal(signal.SIGTTOU, signal.SIG_DFL)

