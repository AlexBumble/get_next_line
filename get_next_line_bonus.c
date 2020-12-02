/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 19:21:04 by jbane             #+#    #+#             */
/*   Updated: 2020/12/02 19:21:06 by jbane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static	void	update_line(t_gnl *res, char **line, size_t size)
{
	char	*buf;
	size_t	tail_l;

	tail_l = ft_strlen(res->str) - (int)size + 1;
	buf = NULL;
	buf = malloc(tail_l);
	*line = NULL;
	*line = malloc((size == 0 ? tail_l : size));
	if (line && buf)
	{
		ft_strlcpy(*line, res->str, (size == 0 ? tail_l : size));
		if (tail_l > 0)
		{
			buf = res->str + size;
			ft_strlcpy(res->str, buf, tail_l + 1);
		}
	}
}

static	int		find_line(int fd, t_gnl *res, char **line)
{
	res->break_i = find_end_line(res->str, 0);
	if (res->break_i >= 0 || (res->read_r > 0 && res->read_r < BUFFER_SIZE))
	{
		update_line(res, line, res->break_i + 1);
		if (res->read_r > 0 && res->read_r < BUFFER_SIZE)
		{
			if (res->break_i == -1)
				return (0);
			res->break_i = find_end_line(res->str, 0);
			return (int)ft_strlen(res->str) >= res->break_i + 1 ? 1 : 0;
		}
		return (1);
	}
	else if (res->read_r > 0)
	{
		res->str = strjoin_fd(fd, res);
		if (res->str)
			return (find_line(fd, res, line));
	}
	else if (res->str && res->read_r == 0)
	{
		update_line(res, line, (ft_strlen(res->str) + 1));
		return (0);
	}
	return (-1);
}

static	int		gnl_operation(int fd, t_gnl *res, char **line)
{
	if (!res->str)
	{
		res->str = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (res->str)
		{
			res->read_r = read(fd, res->str, BUFFER_SIZE);
			if (res->read_r != -1)
			{
				res->str[res->read_r] = '\0';
				return (gnl_operation(fd, res, line));
			}
		}
		return (-1);
	}
	return (find_line(fd, res, line));
}

static	int		current_buf(t_gnl **arr, int fd)
{
	int		i;
	t_gnl	*buf;

	i = 0;
	buf = NULL;
	while (arr[i])
	{
		if (arr[i] && (arr[i]->flag == 1) && (arr[i]->fd == fd))
			break ;
		i++;
	}
	if (!arr[i])
	{
		buf = malloc(sizeof(t_gnl));
		if (buf)
		{
			buf->str = NULL;
			buf->flag = 1;
			buf->fd = fd;
			arr[i] = buf;
		}
	}
	return (i);
}

int				get_next_line(int fd, char **line)
{
	int				gnl_res;
	int				last_res_i;
	static t_gnl	*res[100];

	if (BUFFER_SIZE > 0 && line && fd < 99)
	{
		last_res_i = current_buf(res, fd);
		if (res[last_res_i])
		{
			gnl_res = gnl_operation(fd, res[last_res_i], line);
			if (gnl_res < 1)
			{
				free(res[last_res_i]->str);
				res[last_res_i]->str = NULL;
				free(res[last_res_i]);
				res[last_res_i] = NULL;
			}
			return (gnl_res);
		}
	}
	return (-1);
}
