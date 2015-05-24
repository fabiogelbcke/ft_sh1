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

int			main(int ac, char **av)
{
    pid_t		pid;
    char		*entry;
    int			status;

    entry = NULL;
    ft_putstr("$>");
    while (!entry || ft_strcmp(entry, "exit") != 0)
    {
	entry = get_entry();
	pid = fork();
	if (pid >= 0)
	    if (pid > 0)
	    {
//		wait(&pid);
		ft_putstr("$>");
	    }
	    else
	    {
		if (entry)
		{
		    ft_putstr(entry);
		}
		else
		    ft_putstr("nao");
	    }
	else
	{
	    exit(1);
	}
    }
    return (0);
}
