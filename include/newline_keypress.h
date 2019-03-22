#ifndef NEWLINE_KEYPRESS_H
# define NEWLINE_KEYPRESS_H

# include "tmpsh.h"

int		newline_check(t_line *shell_repr, t_cursor *cursor);

#define		CMDSUBST	0b00001
#define		BRACEPARAM	0b00010
#define		CURSH		0b00011
#define		SUBSH		0b00100
#define		DQUOTE		0b00101
#define		QUOTE		0b00110
#define		CMDAND		0b10111
#define		CMDOR		0b11000
#define		PIPE		0b11001
#define		SEPARATOR	0b10000

#define		NBRE_OPERAND	0b1001

#define		CMDSUBST_STR	"cmdsubst"
#define		BRACEPARAM_STR	"braceparam"
#define		CURSH_STR		"cursh"
#define		SUBSH_STR		"subsh"
#define		DQUOTE_STR		"dquote"
#define		QUOTE_STR		"quote"
#define		CMDAND_STR		"cmdand"
#define		CMDOR_STR		"cmdor"
#define		PIPE_STR		"pipe"

#endif
