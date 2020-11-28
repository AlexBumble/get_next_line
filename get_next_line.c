#include "get_next_line.h"

static	void	update_line(gnl_s *res, char **line, size_t size)
{
	char	*buf;
	size_t	tail_l;

	tail_l = ft_strlen(res->str) - (int)size + 1;
	buf = malloc(tail_l);
	*line = malloc(size);
	if (line && buf)
	{
		ft_strlcpy(*line, res->str, (size == 0 ? tail_l : size));
		buf = res->str + size;
		ft_strlcpy(res->str, buf, tail_l);
	}
}

static	int		find_line(int fd, gnl_s *res, char **line)
{
	res->break_i = find_end_line(res->str, 0);
	if (res->break_i >= 0 || (res->read_r > 0 && res->read_r < 42))
	{
		update_line(res, line, res->break_i + 1);
		if (res->read_r > 0 && res->read_r < 42)
		{
			if (res->break_i == -1)
				return 0;
			res->break_i = find_end_line(res->str, 0);
			return (int)ft_strlen(res->str) >= res->break_i + 1 ? 1 : 0;
		}
		return 1;
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

static	int		gnl_operation(int fd, gnl_s *res, char **line)
{
	if (!res->str)
	{
		res->str = (char *)malloc(sizeof(char) * (42 + 1));
		if (res->str)
		{
			res->read_r = read(fd, res->str, 42);
			res->str[res->read_r] = '\0';
			return (gnl_operation(fd, res, line));
		}
		return -1;
	}
	return (find_line(fd, res, line));
}

static	void	new_gnl_s(int index, gnl_s **new)
{
	gnl_s	*buf;
	buf = malloc(sizeof(gnl_s));
	if (buf)
	{
		buf->str = NULL;
		buf->gnl_i = index;
		buf->flag = 1;
		*new = buf;
	}
}

static	int		last_gnl_s(gnl_s **arr, int index)
{
	if (arr[index] && (arr[index]->flag == 1))
		return index;
	if (arr[index])
		return last_gnl_s(arr, index + 1);
	return (index);
}

int				get_next_line(int fd, char **line)
{
	int				gnl_res;
	int				last_res_i;
	static gnl_s	*res[512];


	last_res_i = last_gnl_s(res, 0);
	if (!res[last_res_i])
	{
		new_gnl_s(0, &res[last_res_i]);
	}
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
		return gnl_res;
	}
	return (-1);
}