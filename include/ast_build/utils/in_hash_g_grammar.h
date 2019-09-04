/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   determine_bytes.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: simrossi <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/27 15:04:52 by simrossi     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/27 15:04:55 by simrossi    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef IN_HASH_G_GRAMMAR_H
# define IN_HASH_G_GRAMMAR_H

t_bool in_grammar(char *tag, char *key);
t_bool in_reverse(char *tag, char *key);
t_bool in_opening_tags(char *tag, char *key);
t_bool in_dquotes_opening_tags(char *tag, char *key);

#endif
