#include "libft.h"
#include "test_runner.h"

/*
** simple_pylst:
**
** Test really basic test on the pylst.
*/

void	simple_chare_pylst(void)
{
	int		x_test = 0;
	t_pylst	*pylst = NULL;

	// Check if a single node with a char * is created correctly
	char	*str = "test";
	push_pylst(&pylst, str, sizeof(char) * ft_strlen(str) + 1, _chare);
	ASSERT_STRCMP(x_test, (char *)pylst->value, str);

	// Check if we can add a node to our pylst
	char	*str2 = "abc";
	push_pylst(&pylst, str2, sizeof(char) * ft_strlen(str2) + 1, _chare);
	ASSERT_STRCMP(x_test, (char *)pylst->value, str);
	ASSERT_STRCMP(x_test, (char *)pylst->next->value, str2);

	// Append a third node
	char	*str3 = "it's the final string for this test";
	push_pylst(&pylst, str3, sizeof(char) * ft_strlen(str3) + 1, _chare);
	ASSERT_STRCMP(x_test, (char *)pylst->value, str);
	ASSERT_STRCMP(x_test, (char *)pylst->next->value, str2);
	ASSERT_STRCMP(x_test, (char *)pylst->next->next->value, str3);
}

void	simple_int_pylst(void)
{
	int		x_test = 0;
	t_pylst	*pylst = NULL;

	// Push a single element
	int		value = 150;
	push_pylst(&pylst, &value, 0, _int);
	ASSERT_INTCMP(x_test, *(int *)pylst->value, value);

	// Add one more element to have 2 node
	int		value2 = -150;
	push_pylst(&pylst, &value2, 0, _int);
	ASSERT_INTCMP(x_test, *(int *)pylst->value, value);
	ASSERT_INTCMP(x_test, *(int *)pylst->next->value, value2);

	// Test with 3 nodes
	int		value3 = 0;
	push_pylst(&pylst, &value3, 0, _int);
	ASSERT_INTCMP(x_test, *(int *)pylst->value, value);
	ASSERT_INTCMP(x_test, *(int *)pylst->next->value, value2);
	ASSERT_INTCMP(x_test, *(int *)pylst->next->next->value, value3);
}

void	multitype_pylst(void)
{
	int		x_test = 0;
	t_pylst	*pylst = NULL;

	// Test if we can have multiple element in a list
	int		value = 101;
	char	*str = "a string";
	push_pylst(&pylst, &value, 0, _int);
	push_pylst(&pylst, str, sizeof(char) * (ft_strlen(str) + 1), _chare);
	ASSERT_INTCMP(x_test, *(int *)pylst->value, value);
	ASSERT_STRCMP(x_test, (char *)pylst->next->value, str);

	// Test if we can add a t_pylst in an other t_pylst
	t_pylst *pylst2 = NULL;
	push_pylst(&pylst2, pylst, NO_COPY_BUT_FREE, _pylst);
	ASSERT_PTRCMP(x_test, (t_pylst *)pylst2->value, pylst);

	// Check if the content of the first pylist is still valid
	t_pylst	*first_pylst_ptr = (t_pylst *)pylst2->value;
	ASSERT_INTCMP(x_test, *(int *)first_pylst_ptr->value, value);
	ASSERT_STRCMP(x_test, (char *)first_pylst_ptr->next->value, str);
}

void	len_pylst_test(void)
{
	int		x_test = 0;
	t_pylst	*pylst = NULL;

	// Simplie test with few elements
	int		value = -1500;
	ASSERT_INTCMP(x_test, len_pylst(pylst), 0);
	push_pylst(&pylst, &value, 0, _int);
	ASSERT_INTCMP(x_test, len_pylst(pylst), 1);
	push_pylst(&pylst, &value, 0, _int);
	ASSERT_INTCMP(x_test, len_pylst(pylst), 2);
	push_pylst(&pylst, &value, 0, _int);
	ASSERT_INTCMP(x_test, len_pylst(pylst), 3);
	push_pylst(&pylst, &value, 0, _int);
	ASSERT_INTCMP(x_test, len_pylst(pylst), 4);
	push_pylst(&pylst, &value, 0, _int);
	ASSERT_INTCMP(x_test, len_pylst(pylst), 5);
}


void	index_pylst_test(void)
{
	int x_test = 0;
	t_pylst	*pylst = NULL;

	char *value = "mytest";
	// Test with a single element with positive and negativ index
	push_pylst(&pylst, &value, 0, _chare);
	ASSERT_PTRCMP(x_test, index_pylst(pylst, 0), pylst);
	ASSERT_PTRCMP(x_test, index_pylst(pylst, -1), pylst);

	// Test for 2 element, each index, positive and negativ.
	push_pylst(&pylst, &value, 0, _chare);
	ASSERT_PTRCMP(x_test, index_pylst(pylst, 0), pylst);
	ASSERT_PTRCMP(x_test, index_pylst(pylst, 1), pylst->next);
	ASSERT_PTRCMP(x_test, index_pylst(pylst, -1), pylst->next);
	ASSERT_PTRCMP(x_test, index_pylst(pylst, -2), pylst);

	// Test for 3, still using the same method
	push_pylst(&pylst, &value, 0, _chare);
	ASSERT_PTRCMP(x_test, index_pylst(pylst, 0), pylst);
	ASSERT_PTRCMP(x_test, index_pylst(pylst, 1), pylst->next);
	ASSERT_PTRCMP(x_test, index_pylst(pylst, 2), pylst->next->next);
	ASSERT_PTRCMP(x_test, index_pylst(pylst, -1), pylst->next->next);
	ASSERT_PTRCMP(x_test, index_pylst(pylst, -2), pylst->next);
	ASSERT_PTRCMP(x_test, index_pylst(pylst, -3), pylst);

	// Test with 4.
	push_pylst(&pylst, &value, 0, _chare);
	ASSERT_PTRCMP(x_test, index_pylst(pylst, 0), pylst);
	ASSERT_PTRCMP(x_test, index_pylst(pylst, 1), pylst->next);
	ASSERT_PTRCMP(x_test, index_pylst(pylst, 2), pylst->next->next);
	ASSERT_PTRCMP(x_test, index_pylst(pylst, 3), pylst->next->next->next);
	ASSERT_PTRCMP(x_test, index_pylst(pylst, -1), pylst->next->next->next);
	ASSERT_PTRCMP(x_test, index_pylst(pylst, -2), pylst->next->next);
	ASSERT_PTRCMP(x_test, index_pylst(pylst, -3), pylst->next);
	ASSERT_PTRCMP(x_test, index_pylst(pylst, -4), pylst);
}

void	join_pylst_test(void)
{
	int		x_test = 0;
	t_pylst	*pylst = NULL;

	// Single node with "my_str"
	push_pylst(&pylst, "my_str", 0, _chare);
	ASSERT_STRCMP(x_test, join_pylst(pylst, "|"), "my_str");

	// 2 nodes : "my_str", "join".
	// Test multiple separator
	push_pylst(&pylst, "join", 0, _chare);
	ASSERT_STRCMP(x_test, join_pylst(pylst, "|"), "my_str|join");
	ASSERT_STRCMP(x_test, join_pylst(pylst, "fd"), "my_strfdjoin");

	// 3 nodes : "my_str", "join", "move".
	push_pylst(&pylst, "move", 0, _chare);
	ASSERT_STRCMP(x_test, join_pylst(pylst, "|"), "my_str|join|move");
	ASSERT_STRCMP(x_test, join_pylst(pylst, "fd"), "my_strfdjoinfdmove");

	// 4 nodes : "my_str", "join", "move", "last".
	push_pylst(&pylst, "last", 0, _chare);
	ASSERT_STRCMP(x_test, join_pylst(pylst, "|"), "my_str|join|move|last");
	ASSERT_STRCMP(x_test, join_pylst(pylst, "fd"), "my_strfdjoinfdmovefdlast");

	// 5 nodes, with empty string : "my_str", "join", "move", "last", "".
	// Test multiple separator
	push_pylst(&pylst, "", 0, _chare);
	ASSERT_STRCMP(x_test, join_pylst(pylst, "|"), "my_str|join|move|last|");
	ASSERT_STRCMP(x_test, join_pylst(pylst, "fd"), "my_strfdjoinfdmovefdlastfd");
}

#define ARRAY(nb_args, strings...) create_ref_pylist(nb_args, strings)



static void		show_lst(t_pylst *pylst)
{
	while (pylst)
	{
		ft_printf("%s-->", (char*)pylst->value);
		pylst = pylst->next;
	}
	ft_printf("NULL\n");
}

void	slice_pylst_test(void)
{
	int		x_test = 0;
	t_pylst *pylst = NULL;
	t_pylst	*reference;

	// Simple slicing with a single element : "my_str"
	push_pylst(&pylst, "my_str", 0, _chare);
	reference = ARRAY(1, "my_str");
	ASSERT_PYLSTCMP(x_test, slice_pylst(pylst, 0, 1), reference);

	// Add a second string "join", and test multiple slicing
	// ["my_str", "join"]
	push_pylst(&pylst, "join", 0, _chare);
	reference = ARRAY(1, "my_str");
	ASSERT_PYLSTCMP(x_test, slice_pylst(pylst, 0, 1), reference);
	reference = ARRAY(2, "my_str", "join");
	ASSERT_PYLSTCMP(x_test, slice_pylst(pylst, 0, 2), reference);
	reference = ARRAY(1, "my_str");
	ASSERT_PYLSTCMP(x_test, slice_pylst(pylst, 0, -1), reference);
	ASSERT_PTRCMP(x_test, slice_pylst(pylst, 0, -2), NULL);
	reference = ARRAY(1, "join");
	ASSERT_PYLSTCMP(x_test, slice_pylst(pylst, 1, 2), reference);
	reference = ARRAY(2, "my_str", "join");
	ASSERT_PYLSTCMP(x_test, slice_pylst(pylst, -2, 2), reference);

	// 3th string in the list, "blop", test indexes in all ways
	// ["my_str", "join", "blop"]
	push_pylst(&pylst, "blop", 0, _chare);
	// Testing normal incrementation
	reference = ARRAY(1, "my_str");
	ASSERT_PYLSTCMP(x_test, slice_pylst(pylst, 0, 1), reference);
	reference = ARRAY(2, "my_str", "join");
	ASSERT_PYLSTCMP(x_test, slice_pylst(pylst, 0, 2), reference);
	reference = ARRAY(3, "my_str", "join", "blop");
	ASSERT_PYLSTCMP(x_test, slice_pylst(pylst, 0, 3), \
			reference);
	// Testing by starting going to negative value
	reference = ARRAY(2, "my_str", "join");
	ASSERT_PYLSTCMP(x_test, slice_pylst(pylst, 0, -1), reference);
	reference = ARRAY(1, "my_str");
	ASSERT_PYLSTCMP(x_test, slice_pylst(pylst, 0, -2), reference);
	ASSERT_PTRCMP(x_test, slice_pylst(pylst, 0, -3), NULL);



	
}
