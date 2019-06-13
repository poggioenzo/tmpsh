
class FDManager():
    """docstring for FDManager."""

    def __init__(self):
        self.fd_append = []  # >>
        self.fd_trunc = []  # >
        self.fd_heredoc = []  # <<
        self.fd_read_from = []  # <
        self.fd_trunc_to_fd = []  # >&
        self.fd_read_from_fd = []  # <&

    def get_redirection_list_from_tag(self, tag):
        redirection_lists = {'APPEND': self.fd_append,
                             'TRUNC': self.fd_trunc,
                             'HEREDOC': self.fd_heredoc,
                             'READ_FROM': self.fd_read_from,
                             'TRUNC_TO_FD': self.fd_trunc_to_fd,
                             'READ_FROM_FD': self.fd_read_from_fd}
        return redirection_lists[tag] if tag in redirection_lists else None
