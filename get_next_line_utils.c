/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbane <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 19:21:19 by jbane             #+#    #+#             */
/*   Updated: 2020/12/02 19:21:21 by jbane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*res;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return ((char *)s2);
	else if (!s2)
		return ((char *)s1);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	res = NULL;
	res = malloc(len_s1 + len_s2 + 1);
	if (res != NULL)
	{
		ft_strlcpy(res, s1, len_s1 + 1);
		ft_strlcpy(res + len_s1, s2, len_s2 + 1);
	}
	return (res);
}

int				find_end_line(char *str, int index)
{
	if (str[index] && str[index] == '\n')
		return (index);
	else if (str[index] && str[index] != '\n')
		return (find_end_line(str, index + 1));
	else
		return (-1);
}

size_t			ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (!dst || !src)
		return (0);
	if (dstsize > 0)
	{
		while (i < (dstsize - 1) && src[i] != '\0')
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	while (src[i] != '\0')
		i++;
	return (i);
}

char			*strjoin_fd(int fd, t_gnl *res)
{
	char	*buf;
	char	*str;

	str = NULL;
	buf = NULL;
	buf = malloc(BUFFER_SIZE + 1);
	if (buf)
	{
		res->read_r = read(fd, buf, BUFFER_SIZE);
		if (res->read_r >= 0)
		{
			buf[res->read_r] = '\0';
			str = ft_strjoin(res->str, buf);
		}
	}
	return (str);
}
