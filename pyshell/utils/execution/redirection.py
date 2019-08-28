import os
import utils.execution.fd_management as fd

#To do: - Avoir running command if fd is wrong

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

def join_cmd(list_branch):
    final_cmd = ""
    for branch in list_branch:
        index = 0
        tagstoken = branch.tagstokens
        while index < tagstoken.length:
            if tagstoken.tags[index] in ["STMT", "SPACES"]:
                final_cmd += tagstoken.tokens[index]
            index += 1
        final_cmd += "\n"
    return final_cmd

def prepare_heredoc(redirection):
    here_pipe = fd.setup_pipe_fd()
    redirection.source = 0
    redirection.dest = here_pipe[0]
    if redirection.type == "TRIPLEHEREDOC":
        print(redirection.tagstokens)
        content = redirection.tagstokens.tokens[0] + "\n"
    else:
        content = join_cmd(redirection.heredoc_ast.list_branch)
    os.write(here_pipe[1], content.encode())
    os.close(here_pipe[1])

def heredoc_apply(redirections_list, func):
    for redirection in redirections_list:
        if redirection.type == "HEREDOC":
            for redir_branch in redirection.heredoc_ast.list_branch:
                func(redir_branch)

def setup_redirection(branch):
    fd_list = branch.redirectionfd
    index = 0
    nbr_redirection = len(fd_list)
    while index < nbr_redirection:
        redirection = fd_list[index]
        if redirection.type in ["HEREDOC", "TRIPLEHEREDOC", "HEREDOCMINUS"]:
            prepare_heredoc(redirection)
        else:
            open_redirection_file(redirection)
        if redirection.error == False:
            if redirection.dest is not None:
                os.dup2(redirection.dest, redirection.source)
                os.close(redirection.dest)
            if redirection.close:
                os.close(redirection.source)
        index += 1
    pass
