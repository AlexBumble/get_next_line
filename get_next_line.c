#include "get_next_line.h"

int	get_next_line(int fd, char **line)
{
	static gnl_s *res;

	if (!res)
	{
		res = malloc(sizeof(gnl_s));
		res->str = NULL;
	}
	if (res)
		return gnl_operation(fd, res, line);
	return -1;
}

int	gnl_operation(int fd, gnl_s *res, char **line)
{
	if (!res->str)
	{
		res->str = malloc(BUFFER_SIZE + 1);
		res->read_r = read(fd, res->str, BUFFER_SIZE);
		if (res->str && res->read_r > 0)
		{
			res->str[res->read_r] = '\0';
			return gnl_operation(fd, res, line);
		}
		else if (res->read_r == 0)
		{
			*line = "";
			return 0;
		}
	}
	else if (res->str && !res->str[0])
	{
		*line = "";
		return ft_strlen(res->str) == 0 ? 0 : 1;
	}
	else
		return find_line(fd, res, 0, line);
	return -1;
}

int	find_line(int fd, gnl_s *res, int index, char **l)
{
	res->break_i = find_end_line(res->str, index);
	if (res->break_i == -1 && res->read_r < BUFFER_SIZE && res->read_r > 0)
	{
		*l = res->str;
		return 0;
	}
	else if (res->break_i == -1)
	{
		if ((res->str = strjoin_from(fd, res)))
			return find_line(fd, res, BUFFER_SIZE + res->read_r - 1, l);
	}
	return update_res_line(res, l);
}

int	update_res_line(gnl_s *res, char **l)
{
	*l = malloc(res->break_i + 1);
	if (l)
	{
		if (res->break_i == 0)
		{
			*l = "";
			res->str = res->str + res->break_i + 1;
			return 0;
		}
		else if (ft_strlcpy(*l, res->str, res->break_i + 1) )
		{
			res->str = res->str + res->break_i + 1;
			return 1;
		}
		free((void *)l);
	}
	return -1;
}

int	find_end_line(char *str, int index)
{
	if (str[index] && str[index] == '\n')
		return index;
	else if (str[index] && str[index] != '\n')
		return find_end_line(str, index + 1);
	else
		return -1;
}