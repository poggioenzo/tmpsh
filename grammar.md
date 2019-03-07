
# Grammar

- `\` : ESCAPE

##  Separators_unaire
- `&`: background_jobs
- `;` : end command

## Separators_binaire
- `|` : pipe
- `&&` : and
- `||` : or

## Redirection_symbol
- `>>`: append
- `>`: trunc
- `<<`: heredoc
- `<`: read_from
- `>&n`: trunc_to (with n = `1..*`, `-`)
- `<&n`: read_from_fd (with n = `1..*`)

## Sub_process(X)
- `${X}`: expansion de variable
- `$(X)`: substitution de commande
- `(X)`: block sous-shell
- `{X}`: commandes groupées
- `>(X)`: substitution stdin
- `<(X)`: substitution by file

# rules

- prog = NAME_BINARY

- arg_op = WORD [WORD ...]

- redirection = redirection_symbol [FILENAME|FILEDESCRIPTOR]{1}
- redirection_list = redirection [redirection ...]

- command = prog{0,1}
- command = prog arg_op
- command = Sub_process(command)
- command = command separators [command]
- command = [command] redirection_list

## token atomique
- NAME_BINARY
- ESCAPE
- WORD
- Separators_unaire
- Separators_binaire
- Redirection_symbol
- FILENAME
- FILEDESCRIPTOR
- Sub_process()
