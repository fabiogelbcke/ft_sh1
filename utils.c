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
	char **split;

	i = 0;
	j = 0;
	if (!var)
	{
		ft_putstr("unsetenv: Too few arguments.\n");
		return ;
	}
	if (!get_env(var, *envpptr))
		return ;
	size = get_env_size(envpptr);
	newenv = malloc(sizeof(char*) * size + 1);
	while((*envpptr)[i])
	{
		split = ft_strsplit((*envpptr)[i], '=');
		if (ft_strcmp(split[0], var))
			newenv[j++] = ft_strdup((*envpptr)[i]);
		i++;
		free(split);
		split = NULL;
	}
	newenv[j] = NULL;
	*envpptr = newenv;
}

char		*get_env(char *var, char **envp)
{
	int	i;
	char	**envvar;
	char	**split;

	if (var)
	{
		i = 0;
		while (envp[i] != NULL)
		{
			split = ft_strsplit(envp[i], '=');
			if (!ft_strcmp(split[0], var))
			{
				return split[1];
			}
			free(split);
			split = NULL;
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
	char **split;

	i = 0;
	if (get_env(var, *envpptr))
		while ((*envpptr)[i])
		{
			split = ft_strsplit((*envpptr)[i], '=');
			if (!ft_strcmp(split[0], var))
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
