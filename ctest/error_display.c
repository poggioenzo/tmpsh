#include "libft.h"
#include "test_runner.h"

#define STRUCT_MAKER(struct_name, type) \
	typedef struct {\
		int test;\
		type result;\
		type reference;}\
	struct_name;

#define FUNCTION_ERROR_MAKER(fct_name, struct_name, type, printf_format)		\
	STRUCT_MAKER(struct_name, type)												\
	void	fct_name(int test_number, type result, type ref_val, int action)	\
	{																			\
		static struct_name error_lst[100];										\
		static int	total_error;												\
																				\
		if (action == STORE_ERROR)												\
		{																		\
			error_lst[total_error++] = (struct_name){.test = test_number,		\
				.result = result, .reference = ref_val};						\
		}																		\
		else if (action == SHOW_ERROR && total_error)							\
		{																		\
			int index = 0;														\
			struct_name	curr_error;												\
																				\
			ft_printf("\n----------------------------");						\
			while (index < total_error)											\
			{																	\
				curr_error = error_lst[index++];								\
				ft_printf(printf_format, curr_error.test,						\
						curr_error.result, curr_error.reference);				\
			}																	\
			ft_printf("\n----------------------------");						\
		}																		\
	}

/*
** chare_error : Store error for any char * assertion
*/

FUNCTION_ERROR_MAKER(chare_error, t_chareerror, char *, "test %d : result : '%s' | ref : '%s' \n")

/*
** int_error : Store error for any int assertion.
*/

FUNCTION_ERROR_MAKER(int_error, t_interror, int, "test %d : result : '%d' | ref : '%d' \n")

/*
** ptr_error : Store error for any void * assertion.
*/

FUNCTION_ERROR_MAKER(ptr_error, t_ptrerror, void *, "test %d : result : '%p' | ref : '%p' \n")

#define DISPLAY_FCT(fct_name) fct_name(0, 0, 0, SHOW_ERROR)

void		error_display()
{
	DISPLAY_FCT(chare_error);
	DISPLAY_FCT(int_error);
	DISPLAY_FCT(ptr_error);
}
