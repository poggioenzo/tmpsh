#include "test_runner.h"
#include "t_char_allocation.h"
#include "t_char_utils.h"

#define TRUE	1
#define FALSE	0

/*
** t_char_allocation_test:
**
** Test for function t_char_allocation
*/

void	t_char_allocation_test(void)
{
	int		x_test = 0;

	//Create a single char with different attribute
	t_char	*char_elem = NULL;
	char letter = 'a'; int position = 45; int lock = TRUE;
	create_char(&char_elem, letter, position, lock);

	//Test if each attribute have been set properly
	ASSERT_TEST(x_test, char_elem != NULL);
	ASSERT_INTCMP(x_test, char_elem->letter, letter);
	ASSERT_INTCMP(x_test, char_elem->lock, lock);
	ASSERT_INTCMP(x_test, char_elem->position, position);
	ASSERT_PTRCMP(x_test, char_elem->next, NULL);

	//Create a second element
	t_char	*char_elem2 = NULL;
	char letter2 = 'z'; int position2 = 0; int lock2 = FALSE;
	create_char(&char_elem2, letter2, position2, lock2);

	//Test if each attribute have been set properly
	ASSERT_TEST(x_test, char_elem2 != NULL);
	ASSERT_INTCMP(x_test, char_elem2->letter, letter2);
	ASSERT_INTCMP(x_test, char_elem2->lock, lock2);
	ASSERT_INTCMP(x_test, char_elem2->position, position2);
	ASSERT_PTRCMP(x_test, char_elem2->next, NULL);
}

/*
** t_char_push_test:
**
** Test for the function push_end_char
*/

void	t_char_push_test(void)
{
	int		x_test = 0;

	//Test from a creation from a NULL pointer
	t_char	*char_lst = NULL;
	char letter = 'f'; int lock = TRUE;
	push_end_char(&char_lst, letter, lock);

	//Test if the t_char have been properly created with the right attributes
	ASSERT_TEST(x_test, char_lst != NULL);
	ASSERT_INTCMP(x_test, char_lst->letter, letter);
	ASSERT_INTCMP(x_test, char_lst->position, 0); // Node at the first pos, aka 0
	ASSERT_INTCMP(x_test, char_lst->lock, lock);
	ASSERT_PTRCMP(x_test, char_lst->next, NULL);

	//Push a second element with different attributes
	int	letter2 = 'u'; int lock2 = FALSE;
	t_char *first_node = char_lst; // To check if we still get the right pointer
	push_end_char(&char_lst, letter2, lock2);

	//Test if we are at the top of the chained list and if we keep our attributes
	ASSERT_PTRCMP(x_test, char_lst, first_node);
	ASSERT_INTCMP(x_test, char_lst->letter, letter);
	ASSERT_INTCMP(x_test, char_lst->position, 0); // Node at the first pos, aka 0
	ASSERT_INTCMP(x_test, char_lst->lock, lock);

	//Test the content of the second attribute
	ASSERT_TEST(x_test, char_lst->next != NULL);
	ASSERT_INTCMP(x_test, char_lst->next->position, 1);
	ASSERT_INTCMP(x_test, char_lst->next->letter, letter2);
	ASSERT_INTCMP(x_test, char_lst->next->lock, lock2);
}

/*
** t_char_push_harder_test:
**
** continue test on push_end_char but with harder test
*/

void	t_char_push_harder_test(void)
{
	int		x_test = 0;

	// Create 3 char node;
	t_char	*char_lst = NULL;
	char letter = 'a'; int lock = TRUE;
	push_end_char(&char_lst, letter, lock);
	push_end_char(&char_lst, letter, lock);
	push_end_char(&char_lst, letter, lock);

	//Check if each node have been create properly and with the right position
	//Will create a segfault if one of them have been created
	ASSERT_INTCMP(x_test, char_lst->position, 0);
	ASSERT_INTCMP(x_test, char_lst->next->position, 1);
	ASSERT_INTCMP(x_test, char_lst->next->next->position, 2);

	//Get last node to perform test after
	t_char	*last_node = char_lst->next->next;
	
	//Create a node from the second t_char element (char_lst->next)
	char letter2 = 'X'; int lock2 = FALSE;
	push_end_char(&char_lst->next, letter2, lock2);

	//Check if the new node is at the last position
	last_node = last_node->next;
	ASSERT_INTCMP(x_test, last_node->position, 3);
	ASSERT_INTCMP(x_test, last_node->letter, letter2);
	ASSERT_INTCMP(x_test, last_node->lock, lock2);
	ASSERT_PTRCMP(x_test, last_node->next, NULL);
}

/*
** t_char_length_test:
**
** Tests for functions char_lst_len and char_lock_len.
*/

void	t_char_length_test(void)
{
	int		x_test = 0;

	//Test with a NULL chained list if both function return 0
	t_char	*char_lst = NULL;
	ASSERT_INTCMP(x_test, char_lst_len(char_lst), 0);
	ASSERT_INTCMP(x_test, char_lock_len(char_lst), 0);

	//Add a single locked char
	push_end_char(&char_lst, 'a', TRUE);
	ASSERT_INTCMP(x_test, char_lst_len(char_lst), 1);
	ASSERT_INTCMP(x_test, char_lock_len(char_lst), 1);

	//Add multiple locked 3 locked char, list size : 4
	push_end_char(&char_lst, 'a', TRUE);
	push_end_char(&char_lst, 'a', TRUE);
	push_end_char(&char_lst, 'a', TRUE);

	//Test if the size is correctly found for both function
	ASSERT_INTCMP(x_test, char_lst_len(char_lst), 4);
	ASSERT_INTCMP(x_test, char_lock_len(char_lst), 4);

	//Add 3 unlocked char at the end of the list. List size: 7, locked part : 4
	push_end_char(&char_lst, 'a', FALSE);
	push_end_char(&char_lst, 'a', FALSE);
	push_end_char(&char_lst, 'a', FALSE);
	// Test if we have a difference between the length functions
	ASSERT_INTCMP(x_test, char_lst_len(char_lst), 7);
	ASSERT_INTCMP(x_test, char_lock_len(char_lst), 4);
}

/*
** t_char_update_pos_test:
**
** Test for the function update_position
*/

void	t_char_update_pos_test(void)
{
	int		x_test = 0;

	//Create a single char with a random position, and update it to see
	//if we get 0
	t_char *char_lst = NULL;
	create_char(&char_lst, 'a', 5555, FALSE);

	//Update his position and perform the check
	update_position(char_lst);
	ASSERT_INTCMP(x_test, char_lst->position, 0);

	// Add 4 element in our list to get 5 node, and disturb to position for
	// each one.
	push_end_char(&char_lst, 'a', FALSE);
	push_end_char(&char_lst, 'a', FALSE);
	push_end_char(&char_lst, 'a', FALSE);
	push_end_char(&char_lst, 'a', FALSE);

	//Make shit with their 5 positions
	char_lst->position = 152;
	char_lst->next->position = 7897;
	char_lst->next->next->position = -879;
	char_lst->next->next->next->position = 746;
	char_lst->next->next->next->next->position = 1;

	//Update their position and check if their are well updated
	update_position(char_lst);
	int index = 0;
	while (index < 5)
	{
		ASSERT_INTCMP(x_test, char_lst->position, index);
		char_lst = char_lst->next;
		index++;
	}
}
