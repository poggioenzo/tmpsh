# Grammar

- `\` : ESCAPE

## Assignation
- `=`: assignation
- `+=`: concatenation

##  Separators_unaire
- `&`: background_jobs
- `;` : end command

## Separators_binaire
- `|` : pipe
- `&&` : and
- `||` : or

## Redirection_symbol_filename
- `>>`: append
- `>`: trunc
- `<<`: heredoc
- `<`: read_from

## Redirection_symbol_fd
- `>&n`: trunc_to (with n = `1..*`, )
- `>&-`: trunc_to_null 
- `<&n`: read_from_fd (with n = `1..*`)

## Sub_process(...)
- `${...}`: expansion de variable
- `$(...)`: substitution de commande
- `(...)`: block sous-shell
- `{...}`: commandes groupées
- `>(...)`: substitution stdin
- `<(...)`: substitution by file

# Rules

- arg_op = WORD [WORD ...]

- redirection = [FILEDESCRIPTOR] Redirection_symbol_filename FILENAME
- redirection = [FILEDESCRIPTOR] Redirection_symbol_fd FILEDESCRIPTOR
- redirection_list = redirection [redirection ...]


- command = command Separators_unaire [command]
- command = command Separators_binaire command
- command = WORD Assignation WORD __sans espace__
- command = [command] Sub_process(command)
- command = [command] [arg_op] redirection_list [arg_op]
- command = redirection_list [command] [arg_op]
- command = NAME_BINARY arg_op
- command = NAME_BINARY{0,1}

# Token atomique
- NAME_BINARY
- ESCAPE
- WORD
- Separators_unaire
- Separators_binaire
- Redirection_symbol
- FILENAME
- FILEDESCRIPTOR
- Sub_process(...)
