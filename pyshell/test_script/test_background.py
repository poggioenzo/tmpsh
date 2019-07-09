import os, time, signal

pid = os.fork()
if pid == 0:
    os.setpgid(0, 0)
    os.execve("/usr/bin/top", ["top"], os.environ)
else:
    print("start sleep")
    time.sleep(3)
    os.tcsetpgrp(0, pid)
    os.kill(pid, signal.SIGCONT)
    status = os.waitpid(pid, 0)
    print(status)
