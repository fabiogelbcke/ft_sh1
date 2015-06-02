#include "ft_sh1.h"

void			cd(char *path, char **envp)
{
	if (!path)
		if (get_env("HOME", envp))
			path = get_env("HOME", envp);
		else
		{
			ft_putstr("HOME variable not set\n");
			return ;
		}
	else if (path[0] == '~' && (!path[1] || path[1] == '/'))
		path = ft_strjoin(get_env("HOME", envp), &(path[1]));
	if (chdir(path) == -1)
		ft_putstr("No such file or directory\n");
}
