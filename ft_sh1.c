#include "ft_sh1.h"

extern char **environ;

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

void			cd(char *path)
{
    if(chdir(path) == -1)
	ft_putstr(strerror(errno));
	
}

void			execute(char **cmd)
{
    char **paths;
    int i;
    int j;
    char		cwd[1024];
	
    i = 0;
    j = 0;
    if (!ft_strcmp(cmd[0], "cd"))
    {
	cd(cmd[1]);
	getcwd(cwd, 1024);
	printf("\n %s \n", cwd);
    }
    else
    {
	paths = ft_strsplit(getenv("PATH"), ':');
	while (paths[i])
	    j = execve(ft_strjoin(ft_strjoin(paths[i++], "/"), cmd[0]), cmd, NULL);
	if (j == -1)
	{
	    ft_putstr(cmd[0]);
	    ft_putstr(": command not found\n");
	}
    }
}

int			main(int ac, char **av)
{
    pid_t		pid;
    char		*entry;
    int			status;
    int i = 0;

    entry = NULL;
    ft_putstr("$> ");
    while (!entry || ft_strcmp(entry, "exit\n") != 0)
    {
	entry = get_entry();
	entry[ft_strlen(entry) - 1] = '\0';
	pid = fork();
	if (pid >= 0)
	    if (pid > 0)
	    {
		wait(&status);
		ft_putstr("$> ");
	    }
	    else
	    {
		if (entry && ft_strlen(entry) > 0)
		{
		    execute(ft_strsplit(entry, ' '));
		    exit(0);
		}
		else if (!entry)
		{
		    ft_putstr("Error retrieving command\n");
		    exit(1);
		}
		else
		    exit(2);
	    }
	else
	    exit(1);
    }
    return (0);
}
