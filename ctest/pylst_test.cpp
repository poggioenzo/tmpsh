#include "libft.h"
#include "test_runner.h"

/*
** simple_pylst:
**
** Test really basic test on the pylst.
*/

void	simple_pylst(void)
{
	t_pylst	*pylst = NULL;
	char	*str = "test";

	// Check if a single node with a char * is created correctly
	push_pylst(&pylst, str, sizeof(char) * ft_strlen(str) + 1, _chare);
	ASSERT_STRCMP((char *)pylst->value, str);

	// Check if we can add a node to our pylst
	char	*str2 = "abc";
	push_pylst(&pylst, str2, sizeof(char) * ft_strlen(str2) + 1, _chare);
	ASSERT_STRCMP((char *)pylst->value, str);
	ASSERT_STRCMP((char *)pylst->next->value, str2);

	// Append a third node
	char	*str3 = "it's the final string for this test";
	push_pylst(&pylst, str3, sizeof(char) * ft_strlen(str3) + 1, _chare);
	ASSERT_STRCMP((char *)pylst->value, str);
	ASSERT_STRCMP((char *)pylst->next->value, str2);
	ASSERT_STRCMP((char *)pylst->next->next->value, str2);
	exit(0);
}
