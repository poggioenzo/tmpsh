#ifndef JOBS_MANAGEMENT_H
# define JOBS_MANAGEMENT_H

void				add_job(t_pylst **job_branches);
void				remove_bg(int index);
t_job				*get_job(int job_id);
void				wait_zombie(void);

#endif
