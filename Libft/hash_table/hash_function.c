/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   hash_function.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/26 19:48:52 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/26 19:48:54 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include "hash_table.h"

/*
** hash_functions:
**
** Hashing function to generate a number in range [0; size[
*/

int			hash_function(const char *string, int seed, int size)
{
	unsigned long long		hash;
	unsigned int			tmp_seed;

	hash = 0;
	while (*string)
	{
		tmp_seed = seed * *string * 5 - seed * size;
		hash += seed * size * tmp_seed + ft_pow(seed, *string * 2 % 7);
		hash %= size;
		string++;
	}
	return (hash);
}
