import os

def open_redirection_file(redirection):
    fd = None
    if redirection.type in ["TRUNC", "APPEND", "READ_FROM"]:
        flags = 0
        if os.path.exists(redirection.dest) == False:
            flags |= os.O_CREAT
        if redirection.type == "TRUNC":
            flags |= os.O_WRONLY
        elif redirection.type == "APPEND":
            flags |= os.O_WRONLY | os.O_APPEND
        elif redirection.type == "READ_FROM":
            flags |= os.O_RDONLY
        try:
            fd = os.open(redirection.dest, flags, 0o666)
            redirection.dest = fd
        except PermissionError:
            print("tmpsh: permission denied: {}".format(redirection.dest), file=sys.stderr)
            redirection.error = True
    else:
        redirection.dest = int(redirection.dest) if redirection.dest.isdigit() else None

def setup_redirection(branch):
    fd_list = branch.redirectionfd
    index = 0
    nbr_redirection = len(fd_list)
    while index < nbr_redirection:
        redirection = fd_list[index]
        open_redirection_file(redirection)
        if redirection.error == False:
            if redirection.dest is not None:
                os.dup2(redirection.dest, redirection.source)
            if redirection.close:
                os.close(redirection.source)
        index += 1
    pass
