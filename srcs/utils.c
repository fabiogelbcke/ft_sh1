/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/07 18:19:13 by fschuber          #+#    #+#             */
/*   Updated: 2018/04/23 13:02:54 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

int			get_env_size(char ***envpptr)
{
	int		i;

	i = 0;
	while ((*envpptr)[i])
		i++;
	return (i);
}

void		unset_env(char ***envpptr, char *var)
{
	char	**newenv;
	int		i;
	int		j;
	char	**split;
	char	*tmp;

	i = -1;
	j = 0;
	if (!var)
	{
		ft_putstr("unsetenv: Too few arguments.\n");
		return ;
	}
	if (!(tmp = get_env(var, *envpptr)))
		return ;
	free(tmp);
	newenv = malloc(sizeof(char*) * (get_env_size(envpptr) + 1));
	while ((*envpptr)[++i])
	{
		split = ft_strsplit((*envpptr)[i], '=');
		if (ft_strcmp(split[0], var))
			newenv[j++] = ft_strdup((*envpptr)[i]);
		ft_free_strarr(split);
		split = NULL;
	}
	newenv[j] = NULL;
	ft_free_strarr(*envpptr);
	*envpptr = newenv;
}

char		*get_env(char *var, char **envp)
{
	int		i;
	char	**split;
	char	*tmp;

	if (var)
	{
		i = 0;
		while (envp[i] != NULL)
		{
			split = ft_strsplit(envp[i], '=');
			if (!ft_strcmp(split[0], var))
			{
				tmp = ft_strdup(split[1]);
				ft_free_strarr(split);
				return (tmp);
			}
			ft_free_strarr(split);
			i++;
		}
	}
	return (NULL);
}

void		show_env(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		ft_putstr(envp[i]);
		ft_putstr("\n");
		i++;
	}
}

void		set_env(char ***envpptr, char *var, char *value)
{
	int		i;
	char	**newenv;
	char	**split;
	char	*tmp;

	i = -1;
	if ((tmp = get_env(var, *envpptr)))
	{
		free(tmp);
		while ((*envpptr)[++i])
		{
			split = ft_strsplit((*envpptr)[i], '=');
			if (!ft_strcmp(split[0], var))
			{
				free((*envpptr)[i]);
				(*envpptr)[i] = ft_strappend_free(ft_strdup(var), ft_strdup("="));
				(*envpptr)[i] = ft_strappend_free((*envpptr)[i], ft_strdup(value));
				ft_free_strarr(split);
				return ;
			}
			ft_free_strarr(split);
		}
	}
	else
	{
		newenv = (char**)malloc((get_env_size(envpptr) + 2) * sizeof(char *));
		while ((*envpptr)[++i])
			newenv[i] = ft_strdup((*envpptr)[i]);
		newenv[i] = ft_strappend_free(ft_strdup(var), ft_strdup("="));
		newenv[i] = ft_strappend_free(newenv[i], ft_strdup(value));
		newenv[i + 1] = NULL;
		ft_free_strarr(*envpptr);
		*envpptr = newenv;
	}
}
