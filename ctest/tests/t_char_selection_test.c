#include "test_runner.h"
#include "char_selection.h"
#include "t_char_allocation.h"

#define TRUE	1
#define FALSE	0

/*
** ! ALL SELECTION FUNCTIONS WITH A t_char LIST
** SHOULD ALWAYS BEEN USED WITH A t_char->lock PART SET TO TRUE !
*/

/*
** get_last_char_test -> get_last_char
**
** Test the if we retrieve always the last unlocked
** t_char in a list.
** Will perfrom each test from the first element of the list,
** which is always a locked part.
*/

void	get_last_char_test(void)
{
	int		x_test = 0;

	//Create the pointer to use as last t_char for the whole test.
	//Result variable
	t_char	*last_char = NULL;

	//Create a simple locked char
	t_char	*char_lst = NULL;
	char letter = 'a'; int lock = TRUE;
	push_end_char(&char_lst, letter, lock);

	//Should return NULL because we have no unlocked char
	get_last_char(char_lst, &last_char); 
	ASSERT_PTRCMP(x_test, last_char, NULL);

	//Aternate creating a locked t_char and performing
	//a test for 3 times, should always return NULL

	//Test 0
	push_end_char(&char_lst, letter, lock);
	get_last_char(char_lst, &last_char); 
	ASSERT_PTRCMP(x_test, last_char, NULL);
	//Test 1
	push_end_char(&char_lst, letter, lock);
	get_last_char(char_lst, &last_char); 
	ASSERT_PTRCMP(x_test, last_char, NULL);
	//Test 2
	push_end_char(&char_lst, letter, lock);
	get_last_char(char_lst, &last_char); 
	ASSERT_PTRCMP(x_test, last_char, NULL);

	
	//Get the last locked t_char manually (4 t_char in the list)
	t_char *last_lock_ref = char_lst->next->next->next;

	//Add now an unlocked t_char and retrieve it manually.
	lock = FALSE;
	push_end_char(&char_lst, letter, lock);
	t_char *last_unlocked_ref = last_lock_ref->next;

	// Test the if the function return our char
	get_last_char(char_lst, &last_char); 
	ASSERT_PTRCMP(x_test, last_char, last_unlocked_ref);

	//Alternatively add a new t_char and check if have the
	//right t_char

	//Test 0
	push_end_char(&char_lst, letter, lock);
	get_last_char(char_lst, &last_char); 
	last_unlocked_ref = last_unlocked_ref->next;
	ASSERT_PTRCMP(x_test, last_char, last_unlocked_ref);
	//Test 1
	push_end_char(&char_lst, letter, lock);
	get_last_char(char_lst, &last_char); 
	last_unlocked_ref = last_unlocked_ref->next;
	ASSERT_PTRCMP(x_test, last_char, last_unlocked_ref);
	//Test 2
	push_end_char(&char_lst, letter, lock);
	get_last_char(char_lst, &last_char); 
	last_unlocked_ref = last_unlocked_ref->next;
	ASSERT_PTRCMP(x_test, last_char, last_unlocked_ref);
}

/*
** get_unlocked_char_test -> get_unlocked_char.
*/

void	get_unlocked_char_test(void)
{
	int		x_test = 0;

	//Create a simple locked char
	t_char	*char_lst = NULL;
	char letter = 'a'; int lock = TRUE;
	push_end_char(&char_lst, letter, lock);

	//Should return NULL because we have no unlocked char
	ASSERT_PTRCMP(x_test, get_unlocked_char(char_lst), NULL);

	//Alternatively adding a locked char and test if we always get NULL
	push_end_char(&char_lst, letter, lock);
	ASSERT_PTRCMP(x_test, get_unlocked_char(char_lst), NULL);
	push_end_char(&char_lst, letter, lock);
	ASSERT_PTRCMP(x_test, get_unlocked_char(char_lst), NULL);
	push_end_char(&char_lst, letter, lock);
	ASSERT_PTRCMP(x_test, get_unlocked_char(char_lst), NULL);

	//Start storing a single locked char and get it as reference.
	lock = FALSE;
	push_end_char(&char_lst, letter, lock);
	t_char	*unlocked_ref = NULL;
	get_last_char(char_lst, &unlocked_ref);

	//Test if the function give us the freshly created node
	ASSERT_PTRCMP(x_test, get_unlocked_char(char_lst), unlocked_ref);

	//Add mutliple unlocked char and test each time if we always have the
	//same result. Test 3 extensions.

	//Test 0
	push_end_char(&char_lst, letter, lock);
	ASSERT_PTRCMP(x_test, get_unlocked_char(char_lst), unlocked_ref);
	//Test 1
	push_end_char(&char_lst, letter, lock);
	ASSERT_PTRCMP(x_test, get_unlocked_char(char_lst), unlocked_ref);
	//Test 2
	push_end_char(&char_lst, letter, lock);
	ASSERT_PTRCMP(x_test, get_unlocked_char(char_lst), unlocked_ref);
}

/*
** get_last_lock_test -> get_last_lock
*/
void	get_last_lock_test(void)
{
	int		x_test = 0;

	//Create a list with a single locked elem
	t_char	*char_lst = NULL;
	char letter = 'a'; int lock = TRUE;
	push_end_char(&char_lst, letter, lock);

	//Test if we get himself and not NULL.
	t_char *lock_result = NULL;
	get_last_lock(char_lst, &lock_result);
	ASSERT_PTRCMP(x_test, lock_result, char_lst);

	//Insert an unlocked char
	lock = FALSE;
	push_end_char(&char_lst, letter, lock);

	//Test if we still get the first t_char element of the list
	get_last_lock(char_lst, &lock_result);
	ASSERT_PTRCMP(x_test, lock_result, char_lst);

	//Destroy the unlocked char to add only locked t_char at the end
	free_t_char(&char_lst->next);

	//Add a second locked char
	lock = TRUE;
	push_end_char(&char_lst, letter, lock);

	//Get a variable to keep the reference of the last locked char
	t_char	*last_unlocked_ref = char_lst->next;

	//Test if we the second node of the list.
	get_last_lock(char_lst, &lock_result);
	ASSERT_PTRCMP(x_test, lock_result, last_unlocked_ref);

	//Alternate locked t_char adding and test, always move by one our last_char

	//Test 0
	last_unlocked_ref = char_lst->next;
	get_last_lock(char_lst, &lock_result);
	ASSERT_PTRCMP(x_test, lock_result, last_unlocked_ref);

	//Test 1
	last_unlocked_ref = char_lst->next;
	get_last_lock(char_lst, &lock_result);
	ASSERT_PTRCMP(x_test, lock_result, last_unlocked_ref);

	//Test 2
	last_unlocked_ref = char_lst->next;
	get_last_lock(char_lst, &lock_result);
	ASSERT_PTRCMP(x_test, lock_result, last_unlocked_ref);
}

/*
** search_prev_char_test -> search_prev_char
*/

void	search_prev_char_test(void)
{
	int		x_test = 0;

	// Initialize each variable useful for the test
	int		number_of_char; int test_performed = 0;
	t_char	*char_lst = NULL;
	t_char	*prev_ref = NULL;
	t_char *prev_result = NULL;
	char letter = 'a'; int lock = TRUE;

	//Create 2 locked element in the list
	push_end_char(&char_lst, letter, lock);
	push_end_char(&char_lst, letter, lock);

	//Check if get the first node with searching the second one
	search_prev_char(char_lst, &prev_result, char_lst->next);
	ASSERT_PTRCMP(x_test, prev_result, char_lst);

	//Insert 4 more node at the end to check
	push_end_char(&char_lst, letter, lock);
	push_end_char(&char_lst, letter, lock);
	push_end_char(&char_lst, letter, lock);
	push_end_char(&char_lst, letter, lock);
	number_of_char = 6; 

	//Check if still get the first node with searching the second one
	search_prev_char(char_lst, &prev_result, char_lst->next);
	ASSERT_PTRCMP(x_test, prev_result, char_lst);

	//Move one by one in char_lst and check if we always get the good result
	prev_ref = char_lst;
	while (test_performed++ < number_of_char - 2)
	{
		prev_ref = prev_ref->next;
		search_prev_char(char_lst, &prev_result, prev_ref->next);
		ASSERT_PTRCMP(x_test, prev_result, prev_ref);
	}
}







