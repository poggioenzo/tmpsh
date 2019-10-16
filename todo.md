# Enzo
## Alias
- Problème alias qui finisse avec un espace.
```
~/git/tmpsh $> la dit
ls: echo: No such file or directory
```

## heredoc order && heredoc minus && heredoc stripped
```
cat <<- EOF1
	content1
	EOF1
EOF1

cat << EOF2
	content2
	EOF2
EOF2

ls

```

## redfd -> 2>&1>truc
pass


# Simon
## Pipe redirigé
`echo lol | > a` ne crée pas de fichier `a` mais en vrai osef.

## env
```
➜  tmpsh git:(master) ✗ env -i ./tmpsh
tmpsh: No such file or directory : .tmpshrc
/Users/epoggio/git/tmpsh $> ls
21sh			aliasfile		ctest			include			src
LICENSE			auteur			dependencies		key_manager_tmpsh.svg	test_mateo_morgane
Libft			bracket_parser.svg	detected_error.txt	lib			tmpsh
Makefile		build			enzo_part.errors	prettify.txt		tmpsh.dSYM
README.md		checked_translation.txt	execution_test		pyshell			todo.md
Useful_links.md		concept_example		grammar.txt		sources.d		unittest
/Users/epoggio/git/tmpsh $> echo $PATH
/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin
/Users/epoggio/git/tmpsh $>
```

## sigint
```
/Users/epoggio/git/tmpsh $> kill -2 $$
[1]    15882 segmentation fault  env -i ./tmpsh
```

## bloqué signaux paste


## SEGFAULT ULTIME
Le crash du long paste
