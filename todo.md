## Tout le monde

wishlist:
- ~~slice_pylist(int, int)~~
- ~~join_pylist(pylist pl, char* join )~~
- ~~delete_after_pylist( pylist pl, int after_not_include)~~
	```
	>>> a = [1,2,3,4,5,6,7,8,9]
	>>> del a[6:]
	>>> a
	[1, 2, 3, 4, 5, 6]
	```
- ~~delete_until_pylist(pylist pl, int until_include)~~ ==> delete_portion(pylst pl, 0, int until)
	```
	>>> a = [1,2,3,4,5,6,7,8,9]
	>>> del a[:6]
	>>> a
	[7, 8, 9]
	```
- ~~delete_portion_pylist(pylist pl, int until_include, int after_not_include)~~
	```
	>>> a = [1,2,3,4,5,6,7,8,9]
	>>> del a[4:6]
	>>> a
	[1, 2, 3, 4, 7, 8, 9]
	```
- ~~replace_portion_pylist(pylist pl, pylist replace, int until_include, int after_not_include)~~
```
>>> a = [1,2,3,4,5,6,7,8,9]
>>> a[4:6] = [700, 800, 900]
>>> a
[1, 2, 3, 4, 700, 800, 900, 7, 8, 9]
```
- (hashmap) reverse_hashmap(hashmap hm)
- ~~assertListEqual_pylist(pylist t)~~ create this kind of assertion, see ASSERT_PYLSTCMP
- ~~int	duplicate_pylist(pylist source, pylist dest)~~

## Enzo

- Tokenisation alias replacement

## Simon

### Builtins
- ~~cd~~
- ~~echo~~
- ~~unsetenv~~ / ~~setenv~~ / export /~~env~~
- ~~exit~~
- type
- alias


- Ctrl - L

- slice_pylist(int, int)
- join_pylist(pylist pl, char* join )
- delete_after_pylist( pylist pl, int after_not_include)
- (hashmap) reverse_hashmap(hashmap hm)
- assertListEqual_pylist(pylist t)
    - comparaison char * à char *

-Checker les builtins.  
echo/cd/setenv/unsetenv/env/exit/type/export/set/unset . 
jobs/fg/bg
-  variable env for builtins
Lexing:  
- `echo 2>&1-- content` le STMT du fd est `1--` 
