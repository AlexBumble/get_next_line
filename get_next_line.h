#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
#include <stdio.h>

typedef struct	gnl_t
{
	int			break_i;
	int 		read_r;
	char		*str;
	int			fd;
	int flag;
}				gnl_s;

int				get_next_line(int fd, char **line);
int gnl_operation(int fd, gnl_s *res, char **line);
int find_line(int fd, gnl_s *res, int i, char **l);
int find_end_line(char *str, int i);
int update_res_line(gnl_s *res, char **l);
char	*strjoin_from(int fd, gnl_s *res);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

#endif
