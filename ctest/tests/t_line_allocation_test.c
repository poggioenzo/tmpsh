#include "tmpsh.h"
#include "t_line_allocation.h"
#include "test_runner.h"
#include "t_line_utils.h"

void	t_line_allocation(void)
{
	int		x_test = 0;
	t_line	*newline = NULL;
	int		position = 0;

	create_t_line(&newline, position);

	// Check if pointer have been properly allocated.
	ASSERT_TEST(x_test, newline != NULL);
	ASSERT_PTRCMP(x_test, newline->chars, NULL);
	ASSERT_PTRCMP(x_test, newline->next, NULL);
	ASSERT_INTCMP(x_test, newline->position, position);

	//Check if free set pointer to NULL (unable to check if really freed)
	free_t_line(&newline, 0);
	ASSERT_PTRCMP(x_test, newline, NULL);

	//Change position
	position = 101;
	create_t_line(&newline, position);
	// Repeat the test of the previous allocation allocation
	ASSERT_TEST(x_test, newline != NULL);
	ASSERT_PTRCMP(x_test, newline->chars, NULL);
	ASSERT_PTRCMP(x_test, newline->next, NULL);
	ASSERT_INTCMP(x_test, newline->position, position);

	//Check if free set pointer to NULL (unable to check if really freed)
	free_t_line(&newline, 0);
	ASSERT_PTRCMP(x_test, newline, NULL);
}

void		t_line_lst_allocation(void)
{
	int		x_test;

	t_line	*new_line = NULL;

	//Test if we can create a list directly with a NULL pointer and push_end
	push_end_line(&new_line);
	//Test if it have been well alocated.
	ASSERT_PTROPE(x_test, new_line != NULL, new_line, NULL);
	ASSERT_INTCMP(x_test, new_line->position, 0);
	ASSERT_PTRCMP(x_test, new_line->next, NULL);
	ASSERT_PTRCMP(x_test, new_line->chars, NULL);

	//Save the current list head to check if we keep the right element
	t_line	*list_head = new_line;

	//Add a new line at the end of the list
	push_end_line(&new_line);
	
	//Save if we still have the good head
	ASSERT_PTRCMP(x_test, new_line, list_head);
	ASSERT_INTCMP(x_test, new_line->position, 0);
	ASSERT_PTROPE(x_test, new_line->next != NULL, new_line->next, NULL);
	ASSERT_PTRCMP(x_test, new_line->chars, NULL);

	//Check the next node
	t_line *next_node = new_line->next;

	// Check if the pointer exist, if his position is 1 and
	// if all of his attributes have been set to NULL.
	ASSERT_PTROPE(x_test, next_node != NULL, next_node, NULL);
	ASSERT_INTCMP(x_test, next_node->position, 1);
	ASSERT_PTRCMP(x_test, next_node->next, NULL);
	ASSERT_PTRCMP(x_test, next_node->chars, NULL);
}

void		t_line_longer_lst(void)
{
	int		x_test = 0;

	//Create  5 element.
	t_line		*line_lst = NULL;
	push_end_line(&line_lst);
	push_end_line(&line_lst);
	push_end_line(&line_lst);
	push_end_line(&line_lst);
	push_end_line(&line_lst);

	// Try to check the position of each node.
	t_line	*tmp_node = line_lst;
	int		index = 0;
	while (index < 5)
	{
		ASSERT_INTCMP(x_test, tmp_node->position, index);
		tmp_node = tmp_node->next;
		index++;
	}
	ASSERT_PTRCMP(x_test, tmp_node, NULL);
}

// Check if we can len function behave properly
// This function should never be launched with a NULL t_line.
void		t_line_len(void)
{
	int		x_test = 0;

	// Create element one by one and check the list len
	t_line		*line_lst = NULL;

	push_end_line(&line_lst);
	ASSERT_INTCMP(x_test, line_lst_len(line_lst), 1);
	push_end_line(&line_lst);
	ASSERT_INTCMP(x_test, line_lst_len(line_lst), 2);
	push_end_line(&line_lst);
	ASSERT_INTCMP(x_test, line_lst_len(line_lst), 3);
	push_end_line(&line_lst);
	ASSERT_INTCMP(x_test, line_lst_len(line_lst), 4);
	push_end_line(&line_lst);
	ASSERT_INTCMP(x_test, line_lst_len(line_lst), 5);
	push_end_line(&line_lst);
	ASSERT_INTCMP(x_test, line_lst_len(line_lst), 6);

	//Check from different position
	ASSERT_INTCMP(x_test, line_lst_len(line_lst->next), 6);
	ASSERT_INTCMP(x_test, line_lst_len(line_lst->next->next), 6);
	ASSERT_INTCMP(x_test, line_lst_len(line_lst->next->next->next), 6);
}

//Check if we can update each position of a t_line properly
void		t_line_update_test(void)
{
	int		x_test = 0;
	int		total_node = 15;

	// Insert mutliple elements
	t_line *line_lst = NULL;
	int		tmp_index = 0;
	while (tmp_index++ < total_node)
		push_end_line(&line_lst);

	// Trouble the current position by incrementing each of them
	t_line	*tmp_node = line_lst;
	tmp_index = 0;
	while (tmp_node)
	{
		tmp_node->position *= tmp_index++;
		tmp_node = tmp_node->next;
	}

	// Update each position and check if we retrieve the right order
	// Check also if we have the same number of elements
	update_line_lst(line_lst);
	tmp_index = 0;
	while (tmp_index < total_node)
	{
		ASSERT_INTCMP(x_test, line_lst->position, tmp_index++);
		line_lst = line_lst->next;
	}
}

void		t_line_get_last_test(void)
{
	int		x_test = 0;

	// Create a single line and check if it his the last line
	t_line	*line_lst = NULL;
	push_end_line(&line_lst);
	ASSERT_PTRCMP(x_test, get_last_line(line_lst), line_lst);

	// Create a new node and check if it's the last node
	push_end_line(&line_lst);
	ASSERT_PTRCMP(x_test, get_last_line(line_lst), line_lst->next);

	// Create a third node and check if it's the last node
	push_end_line(&line_lst);
	ASSERT_PTRCMP(x_test, get_last_line(line_lst), line_lst->next->next);
}


// Test if a simple deletion work properly
void		t_line_extract_test_simple(void)
{
	int		x_test = 0;

	// create 2 t_line and delete the last one
	t_line	*line_lst = NULL;
	push_end_line(&line_lst);
	push_end_line(&line_lst);
	extract_line(line_lst, line_lst->next);

	// Check if the next of the first element is NULL
	ASSERT_PTRCMP(x_test, line_lst->next, NULL);

	// Try to delete himself and access to some date
	// delete must be avoided
	extract_line(line_lst, line_lst);
	ASSERT_INTCMP(x_test, line_lst->position, 0);

	//Add two more element, to have 3 node in the list,
	//and delete the second one
	push_end_line(&line_lst);
	push_end_line(&line_lst);
	t_line	*last_node = line_lst->next->next;
	extract_line(line_lst, line_lst->next);

	// Test if the third node which is save by last_node variable
	// is in the second position
	ASSERT_PTRCMP(x_test, line_lst->next, last_node);
	ASSERT_INTCMP(x_test, line_lst->next->position, 2); //No position update
}
