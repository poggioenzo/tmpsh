## Tout le monde

wishlist:
- slice_pylist(int, int)
- join_pylist(pylist pl, char* join )
- delete_after_pylist( pylist pl, int after_not_include)
	```
	>>> a = [1,2,3,4,5,6,7,8,9]
	>>> del a[6:]
	>>> a
	[1, 2, 3, 4, 5, 6]
	```
- delete_until_pylist(pylist pl, int until_include)
	```
	>>> a = [1,2,3,4,5,6,7,8,9]
	>>> del a[:6]
	>>> a
	[7, 8, 9]
	```
- delete_portion_pylist(pylist pl, int until_include, int after_not_include)
	```
	>>> a = [1,2,3,4,5,6,7,8,9]
	>>> del a[4:6]
	>>> a
	[1, 2, 3, 4, 7, 8, 9]
	```
- replace_portion_pylist(pylist pl, pylist replace, int until_include, int after_not_include)
```
>>> a = [1,2,3,4,5,6,7,8,9]
>>> a[4:6] = [700, 800, 900]
>>> a
[1, 2, 3, 4, 700, 800, 900, 7, 8, 9]
```
- (hashmap) reverse_hashmap(hashmap hm)
- assertListEqual_pylist(pylist t)
	- comparaison char * à char *


## Enzo

- Tokenisation alias replacement

## Simon

### Builtins
- cd
- echo
- unsetenv / setenv / export /env
- export
- exit
- type
- alias
- whence


- Ctrl - L
