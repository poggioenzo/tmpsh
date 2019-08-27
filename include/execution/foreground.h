#ifndef FOREGROUND_H
# define FOREGROUND_H

void	set_foreground(pid_t pgid);
void	restore_tcattr(void);
int		get_tpgid(void);
void	init_tcsettings(void);

#endif
