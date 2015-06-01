#include "ft_sh1.h"


int		get_env_size(char ***envpptr)
{
	int i;

	i = 0;
	while ((*envpptr)[i])
		i++;

	return (i);
}

void		unset_env(char ***envpptr, char *var)
{
	int size;
	char **newenv;
	int i;
	int j;

	i = 0;
	j = 0;
	size = get_env_size(envpptr);
	newenv = malloc(sizeof(char*) * size + 1);
	while((*envpptr)[i])
	{
		if (ft_strcmp(ft_strsub((*envpptr)[i], 0, ft_strlen(var)), var))
			newenv[j++] = ft_strdup((*envpptr)[i]);
		i++;
	}
	newenv[j] = NULL;
	*envpptr = newenv;
}

char		*get_env(char *var, char **envp)
{
	int	i;
	char	**envvar;

	if (var)
	{
		i = 0;
		while (envp[i] != NULL)
		{
			if (!ft_strcmp(ft_strsub(envp[i], 0, ft_strlen(var)), var))
			{
				return ft_strsub(envp[i], ft_strlen(var) + 1, ft_strlen(envp[i]) - ft_strlen(var) - 1);
			}
			i++;
		}
	}
	return NULL;
}

void		show_env(char **envp)
{
	int i;

	i = 0;
	while(envp[i])
	{
		ft_putstr(envp[i]);
		ft_putstr("\n");
		i++;
	}
}

void		set_env(char ***envpptr, char *var, char *value)
{
	int i;
	char **newenv;

	i = 0;
	if (get_env(var, *envpptr))
		while ((*envpptr)[i])
		{
			if (!ft_strcmp(ft_strsub((*envpptr)[i], 0, ft_strlen(var)), var))
			{
				(*envpptr)[i] = ft_strjoin(var, "=");
				(*envpptr)[i] = ft_strjoin((*envpptr)[i], value);
				ft_putstr("done\n");
				return ;
			}
			i++;
		}
	else
	{
		newenv = malloc ((get_env_size(envpptr) + 2) * sizeof(char *));
		while((*envpptr)[i])
		{
			newenv[i] = ft_strdup((*envpptr)[i]);
			i++;
		}
		newenv[i] = ft_strjoin(var, "=");
		newenv[i] = ft_strjoin(newenv[i], value);
		newenv[i + 1] = NULL;
		*envpptr = newenv;
	}
}
