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
