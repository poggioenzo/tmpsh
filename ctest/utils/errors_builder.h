#ifndef ERRORS_BUILDER_H
# define ERRORS_BUILDER_H

#include <string.h>

#define STRUCT_MAKER(struct_name, type) \
	typedef struct {\
		int test;\
		type result;\
		type reference;}\
	struct_name;

#define FUNCTION_ERROR_MAKER2(fct_name, compare_fct, struct_name, type,\
		print_function)	\
	int 	fct_name(int test_number, type result, type ref_val, int action)	\
	{																			\
		static struct_name error_lst[100];										\
		static int	total_error;												\
																				\
		if (action == /*TEST_FUNCTION*/ 0)										\
		{																		\
			if (!compare_fct(result, ref_val))									\
			{																	\
				error_lst[total_error++] = (struct_name){.test = test_number,	\
				.result = result, .reference = ref_val};						\
				return (0);														\
			}																	\
			else																\
				return (1);														\
																				\
		}																		\
		else if (action == /*SHOW_ERROR*/1 && total_error)						\
		{																		\
			print_function(total_error, error_lst);								\
		}																		\
	}

#define PROTOTYPE_DISPLAY(func_name, type, test_struct) \
int 	func_name(int test_number, type result, type reference, int action);

#include "tmpsh.h"

STRUCT_MAKER(_t_char_type, t_char *);
PROTOTYPE_DISPLAY(t_char_error_fct, t_char *, _t_char_type)

STRUCT_MAKER(_t_line_type, t_line *);
PROTOTYPE_DISPLAY(t_line_error_fct, t_line *, _t_char_type)

STRUCT_MAKER(char_tests, char *);
PROTOTYPE_DISPLAY(_chare_error2, char *, char_test);

STRUCT_MAKER(_int_tests, int);
PROTOTYPE_DISPLAY(_int_error2, int, _int_tests);

STRUCT_MAKER(_ptr_tests, void *);
PROTOTYPE_DISPLAY(_ptr_error2, void *, _ptr_tests);
PROTOTYPE_DISPLAY(_ptr_diff_error, void *, _ptr_tests);

#endif
