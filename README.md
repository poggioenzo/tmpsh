

# tmpsh
tmpsh is a project of creating shell. 42 school project.

### Builtins

To see any builtin's option, see the commentary above the function definition.
- `echo` : Write to stdout.
- `cd` : Change directory.
- `exit` : Quit the shell process.
- `type` : Description of command type.
- `export` : Export variables to environnement.
- `setenv` : Set or display environnement variables.
- `unsetenv` : Remove environnement variables.
- `set` : Set or display local variables.
- `jobs` : Display background jobs.
- `fg` : Set jobs in foreground.
- `bg` : Launch stopped jobs in background.
- `alias` : Set or display aliases.
- `unalias` : Unset aliases.
- `hash` : Remember or report utility locations.

### Shell Grammar

#### Operators

| Symbol | Name          |
|--------|---------------|
| ;      | semi-column   |
| \|     | pipe          |
| &&     | and           |
| \|\|   | or            |
| &      | ampersand     |
| =      | equal         |
| +=     | concatenation |
| \      | escape        |
| "      | double-quote  |
| '      | single-quote  |
| ()     | Subshell      |
| {}     | Braces        |
  
#### Redirections

__*Generic format*__ : [n]redir-opertor word

- `[n]>word` : redirect output
- `[n]<word` : redirect input
- `[n]>>word` : appending redirect output
- **Here-Document** :
```
[n]<<word
    here-document
delimiter
```
- `<<< word` : here-strings
- `[n]<&word`: duplicating an input file descriptor
- `[n]>&word`: duplicating an output file descriptor

#### Substitution

***Variables specifications***
1. Variables use `=` and `+=` operator to assign or concatenate, respectively, a variable.
2. Assignation can contain spaces, like `my_var = my_value`.
3. Multiple variable can be set at once : `var=value [var=value ...]`
4. Temporary environnement variables can be set for a command : `HOME=/ cd`
5. If a substitution is performed, split string in mutliple argument, except if the substitution is the value of an assignation.

***Available substitutions***
- `$WORD` or `${WORD}`: Replace variable.
- `$()` : Perform a command substitution.
- `<()` or `>()` : Perfom a process substitution.

***Special variables***
- `?` : Return of the last command.
- `!` : Pid of the last backgrounded command.
- `$` : Pid of the shell process.
- `~` : Home of the given user.

### Edition shortcut

- **Clipboard**
 - `Ctrl + w` : cut the previous word.
 - `Ctrl + n` : cut the next word.
 - `Ctrl + l` : cut the line.
 - `Ctrl + p` : paste.


- **Navigation**
 - `home` or `Ctrl + a` : jump at the beginning of the line.
 - `end` or `Ctrl + e` : jump at the end of the line.
 - `Alt + up` : Move one line up.
 - `Alt + down` : Move one line down
 - `Alt + left` : Move one word left.
 - `Alt + right` : Move one word right.


- **Process Management**
 - `Ctrl + c` : ?
 - `Ctrl + d` : ?
 - `Ctrl + \` : ?
 - `Ctrl + z` : Set shell in background.

The upkey and the downkey are used for the history navigation.
