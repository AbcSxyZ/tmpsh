wishlist:
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
- $$ fait 2 statement.
- `echo 2>&1-- content` le STMT du fd est `1--` 
