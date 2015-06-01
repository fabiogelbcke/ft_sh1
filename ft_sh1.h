#ifndef FT_SH1_H
# define FT_SH1_H

# define BUFF_SIZE 1024
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include "libft/Includes/libft.h"
# include <stdio.h>
# include <sys/types.h>
# include <errno.h>

void	env(void);
char	*get_env(char *var, char **envp);
void	cd(char *path, char **envp);
void	show_env(char **envp);
void	set_env(char ***envpptr, char *var, char *value);
void	unset_env(char ***envpptr, char *var);

#endif
