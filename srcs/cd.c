/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 17:43:06 by fschuber          #+#    #+#             */
/*   Updated: 2018/04/26 17:43:40 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

void		cd(char *path, char ***envpptr)
{
	char	*tmp;

	if (!path)
		if ((tmp = get_env("HOME", *envpptr)))
		{
			free(tmp);
			path = get_env("HOME", *envpptr);
		}
		else
		{
			ft_putstr("HOME variable not set\n");
			return ;
		}
	else if (path[0] == '~' && (!path[1] || path[1] == '/'))
	{
		tmp = get_env("HOME", *envpptr);
		path = ft_strjoin(tmp, &(path[1]));
		free(tmp);
	}
	else
		path = ft_strdup(path);
	if (chdir(path) == -1)
		ft_putstr("No such file or directory\n");
	free(path);
}
