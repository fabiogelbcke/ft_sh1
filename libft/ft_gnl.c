/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpousse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/14 19:54:02 by lpousse           #+#    #+#             */
/*   Updated: 2017/03/02 22:11:10 by nhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_gnl.h"

static t_stock	*new_fd(t_stock *stock, int fd, int i)
{
	char	**new_str_stock;
	int		*new_fd_tab;

	if (fd < 0)
		return ((t_stock *)malloc(sizeof(t_stock)));
	new_str_stock = (char **)malloc(sizeof(char *) * (stock->len + 1));
	new_fd_tab = (int *)malloc(sizeof(int) * (stock->len + 1));
	if (new_str_stock == NULL || new_fd_tab == NULL)
		return (NULL);
	while (i < stock->len)
	{
		new_str_stock[i] = (stock->str_stock)[i];
		new_fd_tab[i] = (stock->fd_tab)[i];
		i++;
	}
	new_fd_tab[i] = fd;
	new_str_stock[i] = ft_strnew(0);
	(stock->len)++;
	if (stock->len != 1)
		free(stock->str_stock);
	if (stock->len != 1)
		free(stock->fd_tab);
	stock->str_stock = new_str_stock;
	stock->fd_tab = new_fd_tab;
	return (stock);
}

static int		stock_search(t_stock **stock, char **str, int fd)
{
	int				i;

	if (*stock == NULL)
	{
		if ((*stock = new_fd(*stock, -1, 0)) == NULL)
			return (-1);
		(*stock)->len = 0;
		if (new_fd(*stock, fd, 0) == NULL)
			return (-1);
	}
	i = 0;
	while (i < (*stock)->len)
	{
		if (fd == ((*stock)->fd_tab)[i])
		{
			*str = ((*stock)->str_stock)[i];
			return (0);
		}
		i++;
	}
	if (new_fd(*stock, fd, 0) == NULL)
		return (-1);
	*str = ((*stock)->str_stock)[i];
	return (0);
}

static char		*buf_stock(char *str, char *buf, int rd)
{
	char	*tmp;
	int		len;
	int		i;

	tmp = str;
	len = ft_strlen(tmp);
	if ((str = ft_strnew(len + rd)) == NULL)
		return (NULL);
	ft_strcpy(str, tmp);
	ft_strdel(&tmp);
	i = 0;
	while (i < rd)
	{
		str[len + i] = buf[i];
		i++;
	}
	return (str);
}

static int		gnl_end(t_stock *stock, char *str, char **line, int fd)
{
	char	*end;
	int		i;

	if (fd < 0)
	{
		if ((*line = ft_strdup(str)) == NULL)
			return (-1);
		return (0);
	}
	end = ft_strchr(str, '\n');
	*end = '\0';
	if ((*line = ft_strdup(str)) == NULL)
		return (-1);
	ft_strcpy(str, end + 1);
	i = 0;
	while ((stock->fd_tab)[i] != fd)
		i++;
	(stock->str_stock)[i] = str;
	return (1);
}

int				ft_gnl(int const fd, char **line)
{
	static t_stock	*stock = NULL;
	char			*str;
	char			*buf;
	char			*end;
	int				rd;

	if (fd < 0 || line == NULL || stock_search(&stock, &str, fd) < 0)
		return (-1);
	end = ft_strchr(str, '\n');
	buf = (char *)malloc(sizeof(char) * BUFF_SIZE);
	while (end == NULL && (rd = read(fd, buf, BUFF_SIZE)) > 0)
	{
		if ((str = buf_stock(str, buf, rd)) == NULL)
		{
			free(buf);
			return (-1);
		}
		end = ft_strchr(str, '\n');
	}
	free(buf);
	if (end != NULL)
		return (gnl_end(stock, str, line, fd));
	if (rd == 0)
		return (gnl_end(stock, str, line, -1));
	return (-1);
}
