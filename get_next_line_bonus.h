#ifndef GET_NEXT_LINE_BONUS_H

# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>

typedef struct	gnl_t
{
	int			break_i;
	long 		read_r;
	char		*str;
	int			fd;
	int			flag;
}				gnl_s;

int				get_next_line(int fd, char **line);
int				find_end_line(char *str, int i);
char			*strjoin_fd(int fd, gnl_s *res);
size_t			ft_strlen(const char *s);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);

#endif