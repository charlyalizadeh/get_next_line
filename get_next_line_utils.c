/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charly </var/spool/mail/charly>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 21:05:52 by charly            #+#    #+#             */
/*   Updated: 2024/01/10 15:10:41 by charly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_strconcat(char **s1, const char *s2)
{
	char	*res;
	size_t	s1len;
	size_t	s2len;
	size_t	i;

	if (!*s2)
		return ;
	s1len = ft_strlen(*s1);
	s2len = ft_strlen(s2);
	res = malloc(s1len + s2len + 1);
	i = 0;
	while ((*s1)[i])
	{
		res[i] = (*s1)[i];
		i++;
	}
	while (s2[i - s1len])
	{
		res[i] = s2[i - s1len];
		i++;
	}
	free(*s1);
	res[s1len + s2len] = '\0';
	*s1 = res;
}

char	*ft_strchr(const char *s, int c)
{
	while ((unsigned char)*s != (unsigned char)c && *s)
		s++;
	if (!*s && c != 0)
		return (NULL);
	return ((char *)s);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

char	*ft_strdup(const char *s)
{
	size_t	slen;
	char	*res;

	slen = ft_strlen(s);
	res = malloc(slen + 1);
	ft_memcpy(res, s, slen + 1);
	return (res);
}
