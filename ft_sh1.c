#include "ft_sh1.h"

char			*get_entry()
{
    int			n;
    char		*str;
    int			size;
    
    n = 1;
    str = malloc(sizeof(char) * BUFF_SIZE);
    n = read(0, str, BUFF_SIZE);
    return str;
}

char			*execute(char **cmd, char **envp, char **dir)
{
	char **paths;
	int i;
	int j;
	char		*cwd;
	
	i = 0;
	j = 0;
	cwd = malloc(sizeof(char) * 1024);
	paths = ft_strsplit(get_env("PATH", envp), ':');
	while (paths[i])
		j = execve(ft_strjoin(ft_strjoin(paths[i++], "/"), cmd[0]), cmd, NULL);
	if (j == -1)
	{
		ft_putstr(cmd[0]);
		ft_putstr(": command not found\n");
	}
	return cwd;
}

void			builtins(char **cmd, char ***envpptr)
{
	if (!ft_strcmp(cmd[0], "cd"))
		cd(cmd[1], *envpptr);
	else if (!ft_strcmp(cmd[0], "env"))
		show_env(*envpptr);
	else if (!ft_strcmp(cmd[0], "setenv"))
		set_env(envpptr, cmd[1], cmd[2]);
	else if (!ft_strcmp(cmd[0], "printenv"))
	{
		ft_putstr(get_env(cmd[1], *envpptr));
		ft_putstr("\n");
	}
	else if (!ft_strcmp(cmd[0], "unsetenv"))
		unset_env(envpptr, cmd[1]);
}

int			main(int ac, char **av, char **envp)
{
    pid_t		pid;
    char		*entry;
    int			status;
    char		*dir;
    char		**cmd;

    entry = NULL;
    ft_putstr("$> ");
    while (1)
    {
	entry = get_entry();
	entry[ft_strlen(entry) - 1] = '\0';
	cmd = ft_strsplit(entry, ' ');
	if (!ft_strcmp(cmd[0], "exit"))
		return (0);
	pid = fork();
	if (pid >= 0)
	    if (pid > 0)
	    {
		    wait(&status);
		    if (status == 1024)
			    builtins(cmd, &envp);
		    ft_putstr("$> ");
	    }
	    else
		    if (!ft_strcmp(cmd[0], "cd") || !ft_strcmp(cmd[0], "env") || !ft_strcmp(cmd[0], "setenv") || !ft_strcmp(cmd[0], "unsetenv") || !ft_strcmp(cmd[0], "printenv"))
			    exit(4);
		    else if (entry && ft_strlen(entry) > 0)
		    {
			    dir = execute(cmd, envp, &dir);
			    exit(0);
		    }
		    else if (!entry)
			    exit(1);
		    else
			    exit(2);
	else
		exit(1);
    }
    return (0);
}
