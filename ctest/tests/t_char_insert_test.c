#include "test_runner.h"
#include "t_char_insert.h"
#include "t_char_allocation.h"

/*
** insert_char_test-> insert_char
**
** Check 4 situation:
** 1) When a pointer is asked from NULL (first insertion)
** 2) Adding a new char when we have only single node (second insertion)
** 3) Adding a new char when we have mutlpile node (third insertion)
** 4) Check if the size update for mutliple element (4th insert)
** 5) Add element from the second one to see if increment is done properly (5th insert)
*/

void	insert_char_test(void)
{
	int		x_test = 0;

	//Insert a char from a NULL pointer
	t_char *char_lst = NULL;
	t_char *reference_chars = NULL;
	int lock = TRUE;

	//Insert a single t_char from a null node
	insert_char(&char_lst, 'a', lock); 
	reference_chars = create_ref_list("a");
	ASSERT_TCHARCMP(x_test, char_lst, reference_chars);

	//Insert a second char
	insert_char(&char_lst, 'b', lock);
	reference_chars = create_ref_list("ab");
	ASSERT_TCHARCMP(x_test, char_lst, reference_chars);

	//Insert a third and a fourth t_char from the beginning
	//of the t_char lst. Check after each insertion
	//Three t_char:
	insert_char(&char_lst, 'c', lock);
	reference_chars = create_ref_list("acb");
	ASSERT_TCHARCMP(x_test, char_lst, reference_chars);
	
	//Four t_char:
	insert_char(&char_lst, 's', lock);
	reference_chars = create_ref_list("ascb");
	ASSERT_TCHARCMP(x_test, char_lst, reference_chars);

	//Move on in our list, add a new char from the secod position and
	//see if our list is correct
	insert_char(&char_lst->next, 'W', lock);
	reference_chars = create_ref_list("asWcb");
	ASSERT_TCHARCMP(x_test, char_lst, reference_chars);
}

void	insert_string_test(void)
{
	int		x_test = 0;

	//Utils for the whole test
	int lock = TRUE;
	t_char	*reference_chars = NULL;

	//Insert an empty string from a NULL pointer, should stay NULL
	t_char *char_lst = NULL;
	insert_string(&char_lst, "", lock);
	ASSERT_PTRCMP(x_test, char_lst, NULL);

	//Insert a string from a NULL pointer
	insert_string(&char_lst, "abc", lock);
	reference_chars = create_ref_list("abc");
	ASSERT_TCHARCMP(x_test, char_lst, reference_chars);

	//Insert a new string from the last t_char ('c') of the string
	insert_string(&char_lst->next->next, "def", lock);
	reference_chars = create_ref_list("abcdef");
	ASSERT_TCHARCMP(x_test, char_lst, reference_chars);

	//Insert string from the second t_char ('b')
	insert_string(&char_lst->next, "123", lock);
	reference_chars = create_ref_list("ab123cdef");
	ASSERT_TCHARCMP(x_test, char_lst, reference_chars);
	
}










