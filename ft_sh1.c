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

void			custom_envp(char ***envpptr)
{
	char *str;
	str = malloc(sizeof(char) * 1024);

	set_env(envpptr, "PWD", getcwd(str, 1024));
	set_env(envpptr, "_", ft_strjoin(str, "/ft_minishell1"));
	set_env(envpptr, "PATH", "usr/local/bin/:usr/bin:/bin:/sbin");
	set_env(envpptr, "HOME", "/");
}

void			builtins(char **cmd, char ***envpptr)
{
	char *str;

	if (!ft_strcmp(cmd[0], "cd"))
		cd(cmd[1], *envpptr);
	else if (!ft_strcmp(cmd[0], "env"))
		show_env(*envpptr);
	else if (!ft_strcmp(cmd[0], "setenv"))
		if (cmd[3])
			ft_putstr("setenv: Too many arguments.\n");
		else if (!cmd[1])
			show_env(*envpptr);
		else if (!cmd[2])
			set_env(envpptr, cmd[1], "");
		else
			set_env(envpptr, cmd[1], cmd[2]);
	else if (!ft_strcmp(cmd[0], "printenv"))
	{
		if (cmd[2])
			ft_putstr("printenv: Too many arguments.\n");
		else if (cmd[1])
		{
			str = get_env(cmd[1], *envpptr);
			if (str)
			{
				ft_putstr(str);
				ft_putstr("\n");
			}
			ft_strdel(&str);
		}
		else
			show_env(*envpptr);
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
	if (envp[0] == NULL)
		custom_envp(&envp);
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
