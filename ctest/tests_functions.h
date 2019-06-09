#ifndef TESTS_FUNCTION_H
# define TESTS_FUNCTION_H

/*
** test_function.h:
**
** File used to add each prototype define in the tests
** folder, contain all test functions.
*/

// Tests for t_pylst
void	simple_chare_pylst(void);
void	simple_int_pylst(void);
void	multitype_pylst(void);
void	len_pylst_test(void);
void	index_pylst_test(void);
void	join_pylst_test(void);
void	slice_pylst_test(void);
void	del_portion_pylst_test(void);
void	del_negativ_portion_test(void);
void	del_after_pylst_test(void);
void	replace_negativ_pylst_test(void);
void	replace_pylst_test(void);

// Tests for hash table
void	hash_creation(void);
void	hash_single_insert(void);
void	hash_multiple_insert(void);
void	hash_multitype_insert(void);
void	hash_insert_single_alveol(void);
void	hash_single_delete(void);
void	hash_multiple_delete(void);
void	hash_alveol_deletion(void);

// Tests for t_line elements only
void	t_line_allocation(void);
void	t_line_lst_allocation(void);
void	t_line_longer_lst(void);
void	t_line_len(void);
void	t_line_update_test(void);
void	t_line_get_last_test(void);
void	t_line_extract_test_simple(void);

// Tests for t_char element only
void	t_char_allocation_test(void);
void	t_char_push_test(void);
void	t_char_push_harder_test(void);
void	t_char_length_test(void);
void	t_char_update_pos_test(void);

// Tests for t_cursor
void	t_cursor_alloc_test(void);

// Tests for t_char selection (char_selection.c)
void	search_prev_char_test(void);
void	get_last_lock_test(void);
void	get_unlocked_char_test(void);
void	get_last_char_test(void);

// Test of t_char insertion 
void	insert_char_test(void);
void	insert_string_test(void);
void	cursor_insert_first_line(void);
void	cursor_insert_second_line(void);
void	cursor_insert_third_line(void);

// Test for cursors dependent selection
void	get_cursor_line_test(void);
void	get_cursor_char_test(void);

// Tests for grammar
void		grammar_test(void);

#endif
