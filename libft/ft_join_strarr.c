/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/19 09:10:07 by fschuber          #+#    #+#             */
/*   Updated: 2017/03/06 12:34:42 by nhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count(char **strarr)
{
	int i;
	int j;
	int	size;

	i = 0;
	size = 0;
	while (strarr[i])
	{
		j = 0;
		while (strarr[i][j])
			j++;
		size += j + 1;
		i++;
	}
	return (size);
}

char		*ft_join_strarr(char **strarr, char separator)
{
	int		i;
	int		j;
	char	*joined;
	int		size;

	size = count(strarr);
	if (!(joined = (char *)malloc(sizeof(char) * size + 1)))
		return (NULL);
	size = 0;
	i = 0;
	while (strarr[i])
	{
		j = 0;
		while (strarr[i][j])
			joined[size++] = strarr[i][j++];
		if (strarr[i + 1] && ft_strlen(strarr[i + 1]) > 0)
			joined[size++] = separator;
		i++;
	}
	joined[size] = '\0';
	return (joined);
}
