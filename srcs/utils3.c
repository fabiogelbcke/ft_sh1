/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 20:13:35 by fschuber          #+#    #+#             */
/*   Updated: 2018/04/26 20:28:32 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

int			cancel_color(char **envp, char **cmd, char **entries)
{
	ft_putstr("\x1b[0m");
	ft_free_strarr(cmd);
	ft_free_strarr(envp);
	ft_free_strarr(entries);
	return (0);
}

int			run_command(char *path, char **cmd, char **envp)
{
	char	*tmp;
	int		j;

	tmp = ft_strappend_free(ft_strjoin(path, "/"),
							ft_strdup(cmd[0]));
	j = execve(tmp, cmd, envp);
	free(tmp);
	return (j);
}
