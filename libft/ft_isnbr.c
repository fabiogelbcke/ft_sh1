/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnbr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/18 04:46:28 by fschuber          #+#    #+#             */
/*   Updated: 2014/11/28 19:26:26 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isnbr(char *str)
{
	while (*str)
	{
		if (*str < 48 || *str > 57)
			return (0);
		else
			str++;
	}
	return (1);
}