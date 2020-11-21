#include "get_next_line.h"

int	get_next_line(int fd, char **line)
{
	static gnl_s *res[5000];
	// printf("fd = %d\n", fd);

	if (!res[fd])
	{
		res[fd] = malloc(sizeof(gnl_s));
		res[fd]->str = NULL;
		res[fd]->fd = fd;
		res[fd]->flag = 1;
	}
	if (res[res[fd]->fd])
	{
		int i = res[fd]->fd;
		if (res[i]->flag == 0)
		{
			i++;
			res[i] = malloc(sizeof(gnl_s));
			res[i]->str = NULL;
			res[i]->fd = fd + 1;
			res[i]->flag = 1;
		}


		int ii = gnl_operation(fd, res[i], line);
		return ii;
	}

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
			*line = (char *)malloc(1);
			*line[0] = '\0';
			// printf(">>>>>>>>>1\n" );
			return 0;
		}
	}
	// else if (res->str && !res->str[0])
	// {

		// *line = (char *)malloc(1);
		// *line[0] = '\0';
		// printf(">>>>>>>>>4\n" );
		// return ft_strlen(res->str) == 0 ? 0 : 1;
	// }
	else
	{
		// if (!res->str[0])
		// {
		// 	printf("222\n" );
		// 				res->str++;
		// }

		return find_line(fd, res, 0, line);
	}

	return -1;
}

int	find_line(int fd, gnl_s *res, int index, char **l)
{
	res->break_i = find_end_line(res->str, index);
	if (res->break_i == -1 && res->read_r < BUFFER_SIZE && res->read_r > 0)
	{
		// printf("ft_strlen(*l) = %zu\n", ft_strlen(*l));
		// printf("ft_strlen(res->str) = %zu\n", ft_strlen(res->str));
		*l = malloc(ft_strlen(res->str) + 1);

		ft_strlcpy(*l, res->str, ft_strlen(res->str) +1);
		// *l = res->str;
		// *l[ft_strlen(res->str) + 1] = '\0';

		// res->str = res->str + ft_strlen(res->str);

		res->flag = 0;

		printf(">>>>>>>>>2\n");

		return 0;
	}
	else if (res->break_i == -1)
	{
		// printf(">>>>>>>>>22\n" );
		if ((res->str = strjoin_from(fd, res)))
			return find_line(fd, res, 0, l);
	}
	return update_res_line(res, l);
}

int	update_res_line(gnl_s *res, char **l)
{
	// printf(">>>>>>>>>33\n" );
	// printf("res.str = %s\n", res->str);
	*l = malloc(res->break_i + 1);
	if (l)
	{
		if (res->break_i == 0)
		{
			// printf(">>>>>>>>>3\n" );
			// printf("res->break_i = %d\n", res->break_i);
			*l = (char *)malloc(1);
			*l[0] = '\0';
			res->str = res->str + res->break_i + 1;
			return 0;
		}
		else if (ft_strlcpy(*l, res->str, res->break_i + 1) )
		{
			// printf(">>>>>>>>>4\n" );
			res->str = res->str + res->break_i + 1;
			return 1;
		}
		// free((void *)l);
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
