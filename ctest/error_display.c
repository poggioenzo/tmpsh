#include "libft.h"
#include "test_runner.h"

/*
** chare_error : Store error for any char * assertion
*/

typedef struct
{
	int		test;
	char	*result;
	char	*reference;
}	t_chareerror;

void	chare_error(int test_number, char *result, char *ref_val, int action)
{
	static t_chareerror	error_lst[100];
	static int		total_error;

	if (action == STORE_ERROR)
	{
		error_lst[total_error++] = (t_chareerror){.test = test_number, \
			.result = result, .reference = ref_val};
	}
	else if (action == SHOW_ERROR && total_error)
	{
		int		index = 0;
		t_chareerror		curr_error;

		ft_printf("\n----------------------------");
		while (index < total_error)
		{
			curr_error = error_lst[index++];
			ft_printf("test %d : result '%s' | ref : '%s'\n", curr_error.test, \
					curr_error.result, curr_error.reference);
		}
		ft_printf("\n----------------------------");
	}
}

/*
** int_error : Store error for any int assertion.
*/

typedef struct
{
	int		test;
	char	result;
	char	reference;
}	t_charerror;

void		int_error(int test_number, char result, char ref_val, int action)
{
	static t_charerror	error_lst[100];
	static int		total_error;

	if (action == STORE_ERROR)
	{
		error_lst[total_error++] = (t_charerror){.test = test_number, \
			.result = result, .reference = ref_val};
	}
	else if (action == SHOW_ERROR && total_error)
	{
		int		index = 0;
		t_charerror		curr_error;

		ft_printf("\n----------------------------");
		while (index < total_error)
		{
			ft_printf("\n");
			curr_error = error_lst[index++];
			ft_printf("test %d : result '%d' | ref : '%d'", curr_error.test, \
					curr_error.result, curr_error.reference);
		}
		ft_printf("\n----------------------------");
	}
}

/*
** ptr_error : Store error for any void * assertion.
*/

typedef struct
{
	int		test;
	void	*result;
	void	*reference;
}	t_ptrerror;

void		ptr_error(int test_number, void *result, void *ref_val, int action)
{
	static t_ptrerror	error_lst[100];
	static int		total_error;

	if (action == STORE_ERROR)
	{
		error_lst[total_error++] = (t_ptrerror){.test = test_number, \
			.result = result, .reference = ref_val};
	}
	else if (action == SHOW_ERROR && total_error)
	{
		int		index = 0;
		t_ptrerror		curr_error;

		ft_printf("\n----------------------------");
		while (index < total_error)
		{
			ft_printf("\n");
			curr_error = error_lst[index++];
			ft_printf("test %d : result '%p' | ref : '%p'", curr_error.test, \
					curr_error.result, curr_error.reference);
		}
		ft_printf("\n----------------------------");
	}
}
void		error_display()
{
	chare_error(0, 0, 0, SHOW_ERROR);
	int_error(0, 0, 0, SHOW_ERROR);
	ptr_error(0, 0, 0, SHOW_ERROR);
}
