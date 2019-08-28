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
	push_pylst(&pylst, &value, 0, _ptr);
	ASSERT_INTCMP(x_test, *(int *)pylst->value, value);

	// Add one more element to have 2 node
	int		value2 = -150;
	push_pylst(&pylst, &value2, 0, _ptr);
	ASSERT_INTCMP(x_test, *(int *)pylst->value, value);
	ASSERT_INTCMP(x_test, *(int *)pylst->next->value, value2);

	// Test with 3 nodes
	int		value3 = 0;
	push_pylst(&pylst, &value3, 0, _ptr);
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
	push_pylst(&pylst, &value, 0, _ptr);
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
	push_pylst(&pylst, &value, 0, _ptr);
	ASSERT_INTCMP(x_test, len_pylst(pylst), 1);
	push_pylst(&pylst, &value, 0, _ptr);
	ASSERT_INTCMP(x_test, len_pylst(pylst), 2);
	push_pylst(&pylst, &value, 0, _ptr);
	ASSERT_INTCMP(x_test, len_pylst(pylst), 3);
	push_pylst(&pylst, &value, 0, _ptr);
	ASSERT_INTCMP(x_test, len_pylst(pylst), 4);
	push_pylst(&pylst, &value, 0, _ptr);
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

#define PYLST(nb_args, strings...) create_ref_pylist(nb_args, strings)

static void		show_lst(t_pylst *pylst, char *message)
{
	ft_printf("%s : [", message);
	while (pylst)
	{
		ft_printf("\"%s\"", (char*)pylst->value);
		pylst = pylst->next;
		if (pylst)
			ft_printf(", ");
	}
	ft_printf("]\n");
}

void	slice_pylst_test(void)
{
	int		x_test = 0;
	t_pylst *pylst = NULL;

	// Simple slicing with a single element : "my_str"
	push_pylst(&pylst, "my_str", 0, _chare);
	ASSERT_PYLSTCMP(x_test, slice_pylst(pylst, 0, 1), PYLST(1, "my_str"));

	// Add a second string "join", and test multiple slicing
	// ["my_str", "join"]
	push_pylst(&pylst, "join", 0, _chare);
	ASSERT_PYLSTCMP(x_test, slice_pylst(pylst, 0, 1), PYLST(1, "my_str"));
	ASSERT_PYLSTCMP(x_test, slice_pylst(pylst, 0, 2), PYLST(2, "my_str", "join"));
	ASSERT_PYLSTCMP(x_test, slice_pylst(pylst, 0, -1), PYLST(1, "my_str"));
	ASSERT_PTRCMP(x_test, slice_pylst(pylst, 0, -2), NULL);
	ASSERT_PYLSTCMP(x_test, slice_pylst(pylst, 1, 2), PYLST(1, "join"));
	ASSERT_PYLSTCMP(x_test, slice_pylst(pylst, -2, 2), PYLST(2, "my_str", "join"));

	// 3th string in the list, "blop", test indexes in all ways
	// ["my_str", "join", "blop"]
	push_pylst(&pylst, "blop", 0, _chare);
	// Testing normal incrementation
	ASSERT_PYLSTCMP(x_test, slice_pylst(pylst, 0, 1), PYLST(1, "my_str"));
	ASSERT_PYLSTCMP(x_test, slice_pylst(pylst, 0, 2), PYLST(2, "my_str", "join"));
	ASSERT_PYLSTCMP(x_test, slice_pylst(pylst, 0, 3), \
			PYLST(3, "my_str", "join", "blop"));
	// Testing by starting going to negative value
	ASSERT_PYLSTCMP(x_test, slice_pylst(pylst, 0, -1), PYLST(2, "my_str", "join"));
	ASSERT_PYLSTCMP(x_test, slice_pylst(pylst, 0, -2), PYLST(1, "my_str"));
	ASSERT_PTRCMP(x_test, slice_pylst(pylst, 0, -3), NULL);
	// Testing by starting from the first index
	ASSERT_PYLSTCMP(x_test, slice_pylst(pylst, 1, 2), PYLST(1, "join"));
	ASSERT_PYLSTCMP(x_test, slice_pylst(pylst, 1, 3), PYLST(2, "join", "blop"));
	// Testing by starting with the second index
	ASSERT_PYLSTCMP(x_test, slice_pylst(pylst, 2, 3), PYLST(1, "blop"));
}

void	del_portion_pylst_test(void)
{
	int		x_test = 0;
	t_pylst	*lst_to_test = NULL;

	// Simple test on a single node
	lst_to_test = PYLST(1, "my_str");
	// Single test with same index, must delete nothing
	del_portion_pylst(&lst_to_test, 0, 0);
	ASSERT_PYLSTCMP(x_test, lst_to_test, PYLST(1, "my_str"));
	// Delete the portion
	del_portion_pylst(&lst_to_test, 0, 1);
	ASSERT_PTRCMP(x_test, lst_to_test, NULL);

	/* Tests with 2 nodes */

	// Destroy from the start
	lst_to_test = PYLST(2, "my_str", "join");
	del_portion_pylst(&lst_to_test, 0, 1);
	ASSERT_PYLSTCMP(x_test, lst_to_test, PYLST(1, "join"));
	// Destroy from the end
	lst_to_test = PYLST(2, "my_str", "join");
	del_portion_pylst(&lst_to_test, 1, 2);
	ASSERT_PYLSTCMP(x_test, lst_to_test, PYLST(1, "my_str"));

	/* Tests with 3 nodes */

	// Destroy from the start
	lst_to_test = PYLST(3, "my_str", "join", "more");
	del_portion_pylst(&lst_to_test, 0, 1);
	ASSERT_PYLSTCMP(x_test, lst_to_test, PYLST(2, "join", "more"));
	del_portion_pylst(&lst_to_test, 0, 1);
	ASSERT_PYLSTCMP(x_test, lst_to_test, PYLST(1, "more"));
	// Destroy 2 element from the start
	lst_to_test = PYLST(3, "my_str", "join", "more");
	del_portion_pylst(&lst_to_test, 0, 2);
	ASSERT_PYLSTCMP(x_test, lst_to_test, PYLST(1, "more"));

	// Destroy from the end
	lst_to_test = PYLST(3, "my_str", "join", "more");
	del_portion_pylst(&lst_to_test, 2, 3);
	ASSERT_PYLSTCMP(x_test, lst_to_test, PYLST(2, "my_str", "join"));
	del_portion_pylst(&lst_to_test, 1, 2);
	ASSERT_PYLSTCMP(x_test, lst_to_test, PYLST(1, "my_str"));
	// Destroy 2 element from the end
	lst_to_test = PYLST(3, "my_str", "join", "more");
	del_portion_pylst(&lst_to_test, 1, 3);
	ASSERT_PYLSTCMP(x_test, lst_to_test, PYLST(1, "my_str"));

	// Delete the middle node
	lst_to_test = PYLST(3, "my_str", "join", "more");
	del_portion_pylst(&lst_to_test, 1, 2);
	ASSERT_PYLSTCMP(x_test, lst_to_test, PYLST(2, "my_str", "more"));

	/* Tests with 4 nodes */
	lst_to_test = PYLST(4, "my_str", "join", "more", "4");
	// Delete 2 nodes in the middle
	del_portion_pylst(&lst_to_test, 1, 3);
	ASSERT_PYLSTCMP(x_test, lst_to_test, PYLST(2, "my_str", "4"));
}

void	del_negativ_portion_test(void)
{
	int		x_test = 0;
	t_pylst	*lst_to_test = NULL;

	/* Tests with 1 element*/
	// Simply delete the node
	lst_to_test = PYLST(1, "my_str");
	del_portion_pylst(&lst_to_test, 0, -1);
	ASSERT_PYLSTCMP(x_test, lst_to_test, PYLST(1, "my_str"));

	/* Tests with 2 elements */
	// Delete last node
	lst_to_test = PYLST(2, "my_str", "to_test");
	del_portion_pylst(&lst_to_test, -2, -1);
	ASSERT_PYLSTCMP(x_test, lst_to_test, PYLST(1, "to_test"));
	// Delete first node
	lst_to_test = PYLST(2, "my_str", "to_test");
	del_portion_pylst(&lst_to_test, 0, -1);
	ASSERT_PYLSTCMP(x_test, lst_to_test, PYLST(1, "to_test"));

	/* Tests with 3 elements */

	// Delete last node
	lst_to_test = PYLST(3, "my_str", "to_test", "extra");
	del_portion_pylst(&lst_to_test, -2, -1);
	ASSERT_PYLSTCMP(x_test, lst_to_test, PYLST(2, "my_str", "extra"));
	// Delete 2 last node
	lst_to_test = PYLST(3, "my_str", "to_test", "extra");
	del_portion_pylst(&lst_to_test, 1, -1);
	ASSERT_PYLSTCMP(x_test, lst_to_test, PYLST(2, "my_str", "extra"));

	// Delete middle node
	lst_to_test = PYLST(3, "my_str", "to_test", "extra");
	del_portion_pylst(&lst_to_test, -2, -1);
	ASSERT_PYLSTCMP(x_test, lst_to_test, PYLST(2, "my_str", "extra"));

}

void	del_after_pylst_test(void)
{
	int		x_test = 0;
	t_pylst		*lst_to_test = NULL;

	// Delete a single element
	lst_to_test = PYLST(1, "a string");
	del_after_pylst(&lst_to_test, 0);
	ASSERT_PTRCMP(x_test, lst_to_test, NULL);

	/* Tests with 2 elements */

	// Delete from the start
	lst_to_test = PYLST(2, "a string", "to_test");
	del_after_pylst(&lst_to_test, 0);
	ASSERT_PTRCMP(x_test, lst_to_test, NULL);
	// Delete the second element only
	lst_to_test = PYLST(2, "a string", "to_test");
	del_after_pylst(&lst_to_test, 1);
	ASSERT_PYLSTCMP(x_test, lst_to_test, PYLST(1, "a string"));

	/* Tests with 3 elements */

	// Delete from the second node
	lst_to_test = PYLST(3, "a string", "to_test", "more");
	del_after_pylst(&lst_to_test, 1);
	ASSERT_PYLSTCMP(x_test, lst_to_test, PYLST(1, "a string"));
	// Delete from the last node
	lst_to_test = PYLST(3, "a string", "to_test", "more");
	del_after_pylst(&lst_to_test, 2);
	ASSERT_PYLSTCMP(x_test, lst_to_test, PYLST(2, "a string", "to_test"));

	// NEGATIV VALUE
	// Tests with -1
	lst_to_test = PYLST(3, "a string", "to_test", "more");
	del_after_pylst(&lst_to_test, -1);
	ASSERT_PYLSTCMP(x_test, lst_to_test, PYLST(2, "a string", "to_test"));
	// Tests with -2
	lst_to_test = PYLST(3, "a string", "to_test", "more");
	del_after_pylst(&lst_to_test, -2);
	ASSERT_PYLSTCMP(x_test, lst_to_test, PYLST(1, "a string"));
}

void	replace_pylst_test(void)
{
	int		x_test = 0;
	t_pylst		*lst_to_test = NULL;

	// Replace a single node with a single element
	push_pylst(&lst_to_test, "a string", 0, _chare);
	replace_pylst(&lst_to_test, PYLST(1, "WARZA"), 0, 1);
	ASSERT_PYLSTCMP(x_test, lst_to_test, PYLST(1, "WARZA"));

	// Replace a single node with mutliple elements
	replace_pylst(&lst_to_test, PYLST(2, "my_str", "join"), 0, 1);
	ASSERT_PYLSTCMP(x_test, lst_to_test, PYLST(2, "my_str", "join"));

	/* Tests with 2 elements */

	// Replace the first element : 
	// from ["my_str", "join"] to ["big", "join"]
	replace_pylst(&lst_to_test, PYLST(1, "big"), 0, 1);
	ASSERT_PYLSTCMP(x_test, lst_to_test, PYLST(2, "big", "join"));
	// Replace the last element
	// from ["big", "join"] to ["big", "lol"]
	replace_pylst(&lst_to_test, PYLST(1, "lol"), 1, 2);
	ASSERT_PYLSTCMP(x_test, lst_to_test, PYLST(2, "big", "lol"));

	// Replace the entire list with a single element
	// from ["big", "link"] to ["small"]
	replace_pylst(&lst_to_test, PYLST(1, "small"), 0, 2);
	ASSERT_PYLSTCMP(x_test, lst_to_test, PYLST(1, "small"));

	// Replacement with multiple elements
	// Replace from start, from ["start", "string"] to ["some", "content", "string"]
	lst_to_test = PYLST(2, "start", "string");
	replace_pylst(&lst_to_test, PYLST(2, "some", "content"), 0, 1);
	ASSERT_PYLSTCMP(x_test, lst_to_test, PYLST(3, "some", "content", "string"));
	// Replace from end, from ["start", "string"] to ["start", "some", "content"]
	lst_to_test = PYLST(2, "start", "string");
	replace_pylst(&lst_to_test, PYLST(2, "some", "content"), 1, 2);
	ASSERT_PYLSTCMP(x_test, lst_to_test, PYLST(3, "start", "some", "content"));
	// Replace the entire list, ["start", "string"] to ["some", "content"].
	lst_to_test = PYLST(2, "start", "string");
	replace_pylst(&lst_to_test, PYLST(2, "some", "content"), 0, 2);
	ASSERT_PYLSTCMP(x_test, lst_to_test, PYLST(2, "some", "content"));

	/* Tests with 3 elements */

	// Simple replacement, element by element
	// replace index 0, from ["a", "long", "test"] to ["some", "long", "test"]
	lst_to_test = PYLST(3, "a", "long", "test");
	replace_pylst(&lst_to_test, PYLST(1, "some"), 0, 1);
	ASSERT_PYLSTCMP(x_test, lst_to_test, PYLST(3, "some", "long", "test"));
	// replace index 1, from ["a", "long", "test"] to ["a", "some", "test"]
	lst_to_test = PYLST(3, "a", "long", "test");
	replace_pylst(&lst_to_test, PYLST(1, "some"), 1, 2);
	ASSERT_PYLSTCMP(x_test, lst_to_test, PYLST(3, "a", "some", "test"));
	// replace index 2, from ["a", "long", "test"] to ["a", "long", "some"]
	lst_to_test = PYLST(3, "a", "long", "test");
	replace_pylst(&lst_to_test, PYLST(1, "some"), 2, 3);
	ASSERT_PYLSTCMP(x_test, lst_to_test, PYLST(3, "a", "long", "some"));

	// Replace multiple index at once
	// From start, from ["a", "long", "some"] to ["a", "string"]
	replace_pylst(&lst_to_test, PYLST(1, "string"), 1, 3);
	ASSERT_PYLSTCMP(x_test, lst_to_test, PYLST(2, "a", "string"));
	// From end, from ["a" "long", "some"] to ["string", "some"]
	lst_to_test = PYLST(3, "a", "long", "some");
	replace_pylst(&lst_to_test, PYLST(1, "string"), 0, 2);
	ASSERT_PYLSTCMP(x_test, lst_to_test, PYLST(2, "string", "some"));
}

void	replace_negativ_pylst_test(void)
{
	int		x_test = 0;
	t_pylst	*lst_to_test = NULL;

	// Replace [0:-1] with a single element
	lst_to_test = PYLST(1, "CONTENT");
	replace_pylst(&lst_to_test, PYLST(1, "TEST"), 0, -1);
	ASSERT_PYLSTCMP(x_test, lst_to_test, PYLST(2, "TEST", "CONTENT"));

	// Replace [0:-1] starting with 2 elements,
	// from ["TEST", "CONTENT"] to ["string", "CONTENT"]
	replace_pylst(&lst_to_test, PYLST(1, "string"), 0, -1);
	ASSERT_PYLSTCMP(x_test, lst_to_test, PYLST(2, "string", "CONTENT"));

	// Replace middle with 3 element, [-2:-1]
	// From ["TEST", "string", "CONTENT"] to ["TEST", "middle", "CONTENT"]
	lst_to_test = PYLST(3, "TEST", "string", "CONTENT");
	replace_pylst(&lst_to_test, PYLST(1, "middle"), -2, -1);
	ASSERT_PYLSTCMP(x_test, lst_to_test, PYLST(3, "TEST", "middle", "CONTENT"));
}

void	update_pylst_test(void)
{
	int		x_test = 0;
	t_pylst	*lst_to_test;
	int		first_allocsize;
	int		second_allocsize;
	char	*first_var;
	char	*second_var;

	//Simple test change the first node
	first_var = "New";
	push_pylst(&lst_to_test, "VALUE", 0, _ptr);
	first_allocsize = sizeof(char) * (ft_strlen(first_var) + 1);
	update_pylst(lst_to_test, 0, first_var, first_allocsize, _chare);
	ASSERT_PYLSTCMP(x_test, lst_to_test, PYLST(1, first_var));

	//Verify if attributes have been set properly
	ASSERT_INTCMP(x_test, lst_to_test->ctype, _chare);
	ASSERT_INTCMP(x_test, lst_to_test->size, first_allocsize);

	//Add a new element, and change each index one by one.
	first_var = "Rock";
	first_allocsize = sizeof(char) * (ft_strlen(first_var) + 1);
	push_pylst(&lst_to_test, "Random", 0, _ptr);
	update_pylst(lst_to_test, 0, first_var, first_allocsize, _chare);
	ASSERT_PYLSTCMP(x_test, lst_to_test, PYLST(2, first_var, "Random")); 

	//Change the second element
	second_var = "N'roll";
	second_allocsize = sizeof(char) * (ft_strlen(second_var) + 1);
	update_pylst(lst_to_test, 1, second_var, second_allocsize, _chare);
	ASSERT_PYLSTCMP(x_test, lst_to_test, PYLST(2, first_var, second_var)); 

	//Test for each new element if attributes are set properly
	//Check for index 0
	ASSERT_INTCMP(x_test, lst_to_test->ctype, _chare);
	ASSERT_INTCMP(x_test, lst_to_test->size, first_allocsize);

	//Check for index 1
	ASSERT_INTCMP(x_test, lst_to_test->next->ctype, _chare);
	ASSERT_INTCMP(x_test, lst_to_test->next->size, second_allocsize);

	//Create a bigger pylst and change some random index
	//(each extreme and some in the middle)
	lst_to_test = PYLST(6, "0", "1", "2", "3", "4", "5");

	//Replace each extreme
	//the 0th index first.
	update_pylst(lst_to_test, 0, "Test0", 0, _ptr);
	ASSERT_PYLSTCMP(x_test, lst_to_test, \
			PYLST(6, "Test0", "1", "2", "3", "4", "5")); 

	//last index (aka 5)
	update_pylst(lst_to_test, 5, "Test5", 0, _chare);
	ASSERT_PYLSTCMP(x_test, lst_to_test, \
			PYLST(6, "Test0", "1", "2", "3", "4", "Test5")); 

	//Replace index 2 and 4, to test middle of the pylst
	//Index 2
	update_pylst(lst_to_test, 2, "Test2", 0, _chare);
	ASSERT_PYLSTCMP(x_test, lst_to_test, \
			PYLST(6, "Test0", "1", "Test2", "3", "4", "Test5")); 

	//Index 4
	update_pylst(lst_to_test, 4, "Test4", 0, _chare);
	ASSERT_PYLSTCMP(x_test, lst_to_test, \
			PYLST(6, "Test0", "1", "Test2", "3", "Test4", "Test5")); 
}
