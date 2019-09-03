#ifndef FILE_RIGHTS_H
# define FILE_RIGHTS_H

char	*check_rights(char *filename, int opts, t_bool free, \
		t_bool print_error);

# define	R	0b0001
# define	W	0b0010
# define	X	0b0100
# define	F	0b1000


#endif
