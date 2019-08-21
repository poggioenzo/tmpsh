#ifndef CD_CANON_H
# define CD_CANON_H

void		retrieve_prev(char *absfile, char *curr_file, char **prev_file);
void		remove_double_slash(char *path);
void		remove_dot(char *absolute, char *position);
void		reset_previous_dir(char *abspath, char **curr_file);
int			next_fileis(char *relpath, char *expected_name);

void		canonicalize(char *path);

#endif
