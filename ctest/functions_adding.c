#include "test_runner.h"
#define ADD_TEST(test_name)	g_tests[__COUNTER__] = (test_store){.name = #test_name, .test = test_name}

/*
** fill_tests_functions:
**
** Add each test function to the list of test.
** Each function must be added with the ADD_TEST macro:
** 
** example:
** ADD_TEST(my_new_test);
*/

static void	fill_tests_functions(void)
{

	/* Hash table tests */
	ADD_TEST(hash_creation);
	ADD_TEST(hash_single_insert);
	ADD_TEST(hash_multiple_insert);
	ADD_TEST(hash_insert_single_alveol);
	ADD_TEST(hash_multitype_insert);
	ADD_TEST(hash_single_delete);
	ADD_TEST(hash_multiple_delete);
	ADD_TEST(hash_alveol_deletion);

	/* t_line tests*/
	ADD_TEST(t_line_allocation);
	ADD_TEST(t_line_lst_allocation);
	ADD_TEST(t_line_longer_lst);
	ADD_TEST(t_line_len);
	ADD_TEST(t_line_update_test);
	ADD_TEST(t_line_get_last_test);
	ADD_TEST(t_line_extract_test_simple);

	/* t_char tests */
	ADD_TEST(t_char_allocation_test);
	ADD_TEST(t_char_push_test);
	ADD_TEST(t_char_push_harder_test);
	ADD_TEST(t_char_length_test);
	ADD_TEST(t_char_update_pos_test);

	/* tmpsh tests */
	ADD_TEST(t_cursor_alloc_test);

	ADD_TEST(search_prev_char_test);
	ADD_TEST(get_last_lock_test);
	ADD_TEST(get_unlocked_char_test);
	ADD_TEST(get_last_char_test);

	ADD_TEST(insert_char_test);
	ADD_TEST(insert_string_test);
	ADD_TEST(cursor_insert_first_line);
	ADD_TEST(cursor_insert_second_line);
	ADD_TEST(cursor_insert_third_line);

	ADD_TEST(get_cursor_line_test);
	ADD_TEST(get_cursor_char_test);

	/* Grammar tests */
	ADD_TEST(grammar_test);

	/* pylst tests */
	ADD_TEST(simple_chare_pylst);
	ADD_TEST(simple_int_pylst);
	ADD_TEST(multitype_pylst);
	ADD_TEST(len_pylst_test);
	ADD_TEST(index_pylst_test);
	ADD_TEST(join_pylst_test);
	ADD_TEST(slice_pylst_test);
	/* ADD_TEST(replace_negativ_pylst_test); */
	ADD_TEST(replace_pylst_test);
	ADD_TEST(del_portion_pylst_test);
	ADD_TEST(del_negativ_portion_test);
	ADD_TEST(del_after_pylst_test);
	ADD_TEST(update_pylst_test);


}

/*
** function_init:
**
** Store in the first time the number of tests using __COUNTER__ macro.
** Allocate after the g_test variable according to the number of tests.
*/
void	function_init(void)
{
	total_tests = __COUNTER__;
	g_tests = (test_store *)malloc(sizeof(test_store) * total_tests);
	fill_tests_functions();
}

