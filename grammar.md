# Grammar

- `\` : escape


## Separators
- `|` : pipe
- `;` : end command
- `&&` : and
- `||` : or
- `&`: background_jobs


## redirection_symbol
- `>>`: append
- `>`: trunc
- `<<`: heredoc
- `<`: read_from
- `>&n`: trunc_to (with n = `1..*`, `-`)
- `<&n`: read_from_fd (with n = `1..*`)


# rules

- prog = NAME_BINARY
- prog = ALIAS

- arg_op = WORD [WORD ...]

redirection_list = redirection_symbol[redirection_symbol ...]

- command = prog
- command = prog arg_op
- command = command separators command
- command = command redirection_list FILENAME
- command = command redirection_list FILEDESCRIPTOR
- command = command
