wishlist:
	- slice_pylist(int, int)
	- join_pylist(pylist pl, char* join )
	- delete_after_pylist( pylist pl, int after_not_include)
	- (hashmap) reverse_hashmap(hashmap hm)
	- assertListEqual_pylist(pylist t)
		- comparaison char * à char *
		
- `(echo ok)> test` me retourne 0 en source. Ca semble etre avec le combo SUBSH/CURSH + redirections normal qui retourne 0
- `echo ok > $(echo mdr) > $(echo test)` semble avoir un probleme a la creation du `RedirectionFD`, j'ai un `IndexError` quand j'ai 2 CMDSUBST pour former les redirections
