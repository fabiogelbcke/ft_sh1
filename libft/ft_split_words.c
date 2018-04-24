/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_spaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/19 09:34:28 by fschuber          #+#    #+#             */
/*   Updated: 2017/03/02 15:55:15 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	numberofwords(char const *s)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	while (s[i])
	{
		if ((s[i] != ' ' && s[i] != '\t')
			&& (i == 0 || s[i - 1] == ' ' || s[i - 1] == '\t'))
			n++;
		i++;
	}
	return (n);
}

static int	getsize(int *i, const char *s, int size)
{
	while (s[*i] && (s[*i] == ' ' || s[*i] == '\t'))
		(*i)++;
	while (s[*i + size] != ' ' && s[*i + size] != '\t' && s[*i + size])
		size++;
	return (size);
}

char		**ft_split_spaces(char const *s)
{
	char	**table;
	int		i;
	int		k;
	int		size;

	i = 0;
	k = 0;
	if (!s)
		return (NULL);
	table = ft_memalloc(sizeof(char*) * (numberofwords(s) + 1));
	if (!table)
		return (NULL);
	while (k < numberofwords(s))
	{
		size = getsize(&i, s, 0);
		table[k] = (char*)malloc((size + 1) * sizeof(char));
		i--;
		size = 0;
		while (s[++i] != ' ' && s[i] != '\t' && s[i])
			table[k][size++] = s[i];
		table[k++][size] = '\0';
	}
	table[k] = NULL;
	return (table);
}
