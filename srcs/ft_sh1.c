/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/07 18:44:12 by fschuber          #+#    #+#             */
/*   Updated: 2018/04/26 20:28:29 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

void				execute(char **entries, char **cmd, char **envp)
{
	char			**paths;
	int				i;
	int				j;
	char			*tmp;

	if (is_builtin(cmd[0]))
		exit(4);
	if (*entries && ft_strlen(*entries) > 0)
	{
		i = 0;
		j = -1;
		tmp = get_env("PATH", envp);
		paths = ft_strsplit(tmp, ':');
		free(tmp);
		while (paths && paths[i])
			j = run_command(paths[i++], cmd, envp);
		ft_free_strarr(paths);
		if (j == -1 && execve(cmd[0], cmd, envp) != -1)
		{
			ft_putstr(cmd[0]);
			ft_putstr(": command not found\n");
		}
	}
	exit(2);
}

void				custom_envp_color(int ac, char **av,
									char *env_one, char ***envpptr)
{
	char			*str;

	if (env_one == NULL)
	{
		str = malloc(sizeof(char) * 1024);
		set_env(envpptr, "PWD", getcwd(str, 1024));
		set_env(envpptr, "_", ft_strjoin(str, "/ft_minishell1"));
		set_env(envpptr, "PATH", "usr/local/bin/:usr/bin:/bin:/sbin");
		set_env(envpptr, "HOME", "/");
		set_env(envpptr, "TERM", "xterm");
		free(str);
	}
	color_me(ac, av);
}

void				builtins(char **cmd, char ***envpptr)
{
	if (!ft_strcmp(cmd[0], "cd"))
		cd(cmd[1], envpptr);
	else if (!ft_strcmp(cmd[0], "env"))
		show_env(*envpptr);
	else if (!ft_strcmp(cmd[0], "setenv"))
		if (ft_strarr_len(cmd) != 3)
			ft_putstr("setenv: Must provide 2 arguments.\n");
		else if (!cmd[1])
			show_env(*envpptr);
		else if (!cmd[2])
			set_env(envpptr, cmd[1], "");
		else
			set_env(envpptr, cmd[1], cmd[2]);
	else if (!ft_strcmp(cmd[0], "printenv"))
		if (cmd[1] != NULL && cmd[2] != NULL)
			ft_putstr("printenv: Too many arguments.\n");
		else if (cmd[1] && get_env(cmd[1], *envpptr))
			ft_putstr(ft_strjoin(get_env(cmd[1], *envpptr), "\n"));
		else
			show_env(*envpptr);
	else if (!ft_strcmp(cmd[0], "unsetenv"))
		unset_env(envpptr, cmd[1]);
}

char				**copy_env(char **envp)
{
	char			**newenv;
	int				i;

	if (!envp)
		return (NULL);
	newenv = (char**)malloc((get_env_size(&envp) + 1) * sizeof(char *));
	i = 0;
	while (envp[i])
	{
		newenv[i] = ft_strdup(envp[i]);
		i++;
	}
	newenv[i] = NULL;
	return (newenv);
}

int					main(int ac, char **av, char **envp)
{
	char			**cmd;
	char			**entries;
	int				i;

	envp = copy_env(envp);
	custom_envp_color(ac, av, envp[0], &envp);
	while ((entries = NULL))
	{
		if (!entries || (!*(entries)))
			ft_putstr("$> ");
		entries = get_entry();
		i = -1;
		while (entries[++i])
		{
			cmd = ft_split_spaces(entries[i]);
			if (!cmd || !cmd[0])
				break ;
			if (!ft_strcmp(cmd[0], "exit"))
				return (cancel_color_free_shit(envp, cmd, entries));
			handle_process(cmd, &envp, entries);
			ft_free_strarr(cmd);
		}
		ft_free_strarr(entries);
	}
	return (0);
}
