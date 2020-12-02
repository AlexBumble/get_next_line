/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 19:20:54 by jbane             #+#    #+#             */
/*   Updated: 2020/12/02 19:20:57 by jbane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

typedef struct	s_gnl
{
	int			break_i;
	long		read_r;
	char		*str;
	int			fd;
	int			flag;
}				t_gnl;

int				get_next_line(int fd, char **line);
int				find_end_line(char *str, int i);
char			*strjoin_fd(int fd, s_gnl *res);
size_t			ft_strlen(const char *s);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);

#endif
