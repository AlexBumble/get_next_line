#include "get_next_line.h"

char	*ft_strjoin(char const *s1, char const *s2)
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
	res = malloc(len_s1 + len_s2 + 1);
	if (res != NULL)
	{
		ft_strlcpy(res, s1, len_s1 + 1);
		ft_strlcpy(res + len_s1, s2, len_s2 + 1);
	}
	return (res);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	c_chr;

	i = 0;
	c_chr = (char)c;
	while (s[i])
	{
		if (s[i] == c_chr)
			return ((char *)s + i);
		i++;
	}
	if (c_chr == '\0' && s[i] == '\0')
		return ((char *)s + i);
	return (NULL);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
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

char	*strjoin_from(int fd, gnl_s *res)
{
	char	*buf;
	char	*str;

	str = NULL;
	buf = malloc(BUFFER_SIZE + 1);
	if (buf && (res->read_r = read(fd, buf, BUFFER_SIZE)))
	{
		buf[res->read_r] = '\0';
		str = ft_strjoin(res->str, buf);
	}
	if (buf)
		free((void *)buf);
	return str;
}
