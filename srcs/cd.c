/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/07 18:17:25 by fschuber          #+#    #+#             */
/*   Updated: 2018/04/23 13:24:20 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

void			cd(char *path, char ***envpptr)
{
	if (!path)
		if (get_env("HOME", *envpptr))
			path = get_env("HOME", *envpptr);
		else
		{
			ft_putstr("HOME variable not set\n");
			return ;
		}
	else if (path[0] == '~' && (!path[1] || path[1] == '/'))
		path = ft_strjoin(get_env("HOME", *envpptr), &(path[1]));
	//else if (ft_strcmp(path, "-") == 0)
	//	path = get_env("PWD", *envpptr);
	if (chdir(path) == -1)
	{
		ft_putstr("No such file or directory\n");
		return ;
	}
	//set_env(envpptr, "OLDPWD", get_env("PWD", *envpptr));
	//set_env(envpptr, "PWD", path);
}
