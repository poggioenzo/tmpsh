#ifndef BACKGROUND_UTILS_H
# define BACKGROUND_UTILS_H

int			bg_fg_base(char **argv, char *caller, \
		void (*function)(t_job *job));
int			is_job_id(char *argument_name);

#endif
