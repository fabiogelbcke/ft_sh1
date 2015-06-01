#include "ft_sh1.h"

void			cd(char *path, char **envp)
{
	if (!path)
		path = get_env("HOME", envp);
	if (chdir(path) == -1)
		ft_putstr(strerror(errno));
}
