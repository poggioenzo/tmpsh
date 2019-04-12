import os
rside, wside = os.pipe()
if not os.fork():
    # Child

    os.close(rside)
    # Make stdout go to parent
    os.dup2(wside, 1)
    # Make stderr go to parent
    os.dup2(wside, 2)
    # Optionally make stdin come from nowhere
    devnull = os.open("/dev/null", os.O_RDONLY)
    os.dup2(devnull, 0)
    # Execute the desired program
    os.execve("/bin/bash",["/bin/bash","-c","echo stdout; echo stderr >&2"],os.environ)
    print("Failed to exec program!")
    sys.exit(1)

# Parent
os.close(wside)
pyrside = os.fdopen(rside)

for line in pyrside:
   print("Child (stdout or stderr) said: <%s>"%line)

# Prevent zombies!  Reap the child after exit
pid, status = os.waitpid(-1, 0)
