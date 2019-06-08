#include "libft.h"
#include "test_runner.h"
#include "tmpsh.h"
#include "errors_builder.h"


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
			ft_printf("\n----------------------------\n");						\
			while (index < total_error)											\
			{																	\
				curr_error = error_lst[index++];								\
				ft_printf(printf_format, curr_error.test,						\
						curr_error.result, curr_error.reference);				\
			}																	\
			ft_printf("\n----------------------------");						\
		}																		\
	}


#define DISPLAY_FCT(fct_name) fct_name(0, 0, 0, SHOW_ERROR)

void		error_display()
{
	DISPLAY_FCT(_chare_error2);
	DISPLAY_FCT(_int_error2);
	DISPLAY_FCT(_ptr_error2);
	DISPLAY_FCT(t_char_error_fct);
	DISPLAY_FCT(t_line_error_fct);
	DISPLAY_FCT(_ptr_diff_error);	
	DISPLAY_FCT(t_pylst_error_fct);	
}
