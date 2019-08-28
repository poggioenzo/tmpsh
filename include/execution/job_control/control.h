#ifndef CONTROL_H
# define CONTROL_H

void				wait_zombie(void);
void				relaunch(int index);
enum e_waitstate	analyse_job_status(t_pylst *job_list, int mode);

#endif
