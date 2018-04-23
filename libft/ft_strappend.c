/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/19 09:10:07 by fschuber          #+#    #+#             */
/*   Updated: 2014/11/28 19:47:54 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strappend_free(char *str1, char *str2)
{
	char	*newstr;

	if (!str1 || !str2)
		return (NULL);
	newstr = ft_strjoin(str1, str2);
	free(str1);
	free(str2);
	return (newstr);
}
