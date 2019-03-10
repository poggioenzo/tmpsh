/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   is_verif.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/27 15:05:07 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/31 14:44:02 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "printf.h"

int		is_specifier(int c)
{
	return (ft_incharset(c, "sSpdiouxXcCF%r"));
}

int		is_flag(int c)
{
	return (ft_incharset(c, "0 #-+"));
}
