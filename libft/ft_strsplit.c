/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/19 09:34:28 by fschuber          #+#    #+#             */
/*   Updated: 2014/12/16 20:42:00 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "Includes/libft.h"

int	numberofwords(char const *s, char c)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			n++;
		i++;
	}
	return (n);
}

int	getsize(int *i, const char *s, char c, int size)
{
	while (s [*i] && s[*i] == c)
		(*i)++;
	while (s[*i + size] && s[*i + size] != c)
		size++;
	return (size);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**table;
	int		i;
	int		k;
	int		size;

	i = 0;
	k = 0;
	if (!s || !c)
		return (NULL);
	table = (char **)malloc(sizeof(char*) * (numberofwords(s, c) + 1));
	if (!table)
		return (NULL);
	while (k < numberofwords(s, c))
	{
		size = 0;
		size = getsize(&i, s, c, size);
		table[k] = (char*)malloc((size + 1) * sizeof(char));
		if (!table[k])
			return (NULL);
		i--;
		size = 0;
		while (s[++i] != c && s[i])
			table[k][size++] = s[i];
		table[k++][size] = '\0';
	}
	table[k] = NULL;
	return (table);
}
