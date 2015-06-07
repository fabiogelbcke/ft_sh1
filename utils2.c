/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/07 18:49:42 by fschuber          #+#    #+#             */
/*   Updated: 2015/06/07 19:24:30 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

int is_builtin(char *str)
{
	if (!ft_strcmp(str, "cd")  || !ft_strcmp(str, "env"))
		return (1);
	if (!ft_strcmp(str, "setenv") || !ft_strcmp(str, "unsetenv"))
		return (1);
	if (!ft_strcmp(str, "printenv"))
		return (1);
	return (0);
}

int cancel_color(void)
{
	ft_putstr("\x1b[0m");
	return (0);
}
