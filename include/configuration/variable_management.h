#ifndef VARIABLE_MANAGEMENT_H
# define VARIABLE_MANAGEMENT_H

void	setup_variables_elements(char **environ);
void	update_var(char *variable, char *value, char *type, t_bool only_env);

#endif
