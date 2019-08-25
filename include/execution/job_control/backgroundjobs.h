#ifndef BACKGROUNDJOBS_H
# define BACKGROUNDJOBS_H

void				init_backgroundjobs(void);
void				add_job(t_pylst **job_branches);
enum e_waitstate	is_running(int index);
void				remove_bg(int index);
void				clear(void);

#endif
